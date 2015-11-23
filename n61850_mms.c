/**
 * \file n61850_mms.c
 * \brief MMS oriented methods
 * \author Devaud Mathieu, Marty Kilian
 * \version 0.1
 * \date 21 January 2015
 *
 * 
 *
 */
 
/*
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
#include "n61850_global.h"
#include <unistd.h>

static uint8_t downloadBuffer[MAX_BUFFER_SIZE];
static int bufferPosition = 0;

//---------------------------------------------------------------------------------

/** 
 * \fn void set_mms_connection()
 * \brief Method who open the connection from the MMS client to a MMS server
 * 
 */
//---------------------------------------------------------------------------------
void set_mms_connection() {
	MmsConnection con = MmsConnection_create();
	MmsError mmsError;
	printf("Trying to connect to ip = %s & port = %d \n",p_connection->ip, p_connection->port);
	if (MmsConnection_connect(con, &mmsError, p_connection->ip, p_connection->port)) {
		
                Thread_sleep(1000);
	    	printf("Connection succeeded\n");
	    	MmsConnection_abort(con, &mmsError);
	    	printf("Deconnecting ...\n");
	}
	else{
	    printf("Connect to server failed!\n");
	}
	MmsConnection_destroy(con);
	return;
}

//---------------------------------------------------------------------------------
/** 
 * \fn void discover_mms()
 * \brief Method who scan the network and find each ip with port 102 open
 * 
 */
//---------------------------------------------------------------------------------
void discover_mms() {
    	int fd;
    	struct ifreq ifr;    
    	char iface[] = "eth0";    
    	fd = socket(AF_INET, SOCK_DGRAM, 0);
    	//Type of address to retrieve - IPv4 IP address
    	ifr.ifr_addr.sa_family = AF_INET;
    	//Copy the interface name in the ifreq structure
    	strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);
    	//get the ip address
    	ioctl(fd, SIOCGIFADDR, &ifr);
    	//display ip
    	printf("IP address of %s - %s\n" , iface , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
     	//get the netmask ip
   		ioctl(fd, SIOCGIFNETMASK, &ifr);
		//display netmask
    	printf("Netmask of %s - %s\n" , iface , inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr) );
		int netmask_cidr;
      	int ipbytes[4];
      	netmask_cidr=0;
      	sscanf(inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr), "%d.%d.%d.%d", &ipbytes[0], &ipbytes[1], &ipbytes[2], &ipbytes[3]);
	int i;
	
      	for (i=0; i<4; i++){
          switch(ipbytes[i]){
              case 0x80:
                  netmask_cidr+=1;
                  break;
              case 0xC0:
                  netmask_cidr+=2;
                  break;
              case 0xE0:
                  netmask_cidr+=3;
                  break;
              case 0xF0:
                  netmask_cidr+=4;
                  break;
              case 0xF8:
                  netmask_cidr+=5;
                  break;
              case 0xFC:
                  netmask_cidr+=6;
                  break;
              case 0xFE:
                  netmask_cidr+=7;
                  break;
              case 0xFF:
                  netmask_cidr+=8;
                  break;
              default:
                  break;
          }
     	}
	char nmap_string[1000];
	char str[1000];
	sprintf(str,"/%d",netmask_cidr);
	printf("netmask is %s \n",str);
	ioctl(fd, SIOCGIFADDR, &ifr);
	sprintf(nmap_string,"sudo nmap -sS -p 102 %s%s --open",inet_ntoa(( (struct sockaddr_in *)&ifr.ifr_addr )->sin_addr),str);   
	printf("%s \n",nmap_string);
	system(nmap_string);
    	close(fd);

	return;
}
//---------------------------------------------------------------------------------
/**
 * \fn void scan_server()
 * \brief Method who scan a MMS server and extract local variables
 */
//---------------------------------------------------------------------------------
void scan_server() {
    /* Create a new MmsConnection instance. */
	MmsConnection con = MmsConnection_create();
	MmsError mmsError;
    /* Connect to an MMS server. This will open a new TCP connection and send a MMS initiate request. */
	printf("Trying to connect to ip = %s & port = %d \n",p_connection->ip, p_connection->port);
	if (MmsConnection_connect(con, &mmsError, p_connection->ip, p_connection->port)) {
		// add application code here
        	Thread_sleep(1000);      
        	/*************************************************************************/
        	/* Domain present on server */
        	printf("Domains present on server:\n--------------------------\n");
	    	LinkedList nameList = MmsConnection_getDomainNames(con, &mmsError);
	    	LinkedList_printStringList(nameList);
	    	printf("\n");
	    	LinkedList element = nameList;        
       		while ((element = LinkedList_getNext(element)) != NULL) {
		    printf("\nNamed variables in domain: %s\n-------------------------------------------------\n", (char*) element->data);
		    LinkedList variableList = MmsConnection_getDomainVariableNames(con, &mmsError, (char*) element->data);
		    LinkedList_printStringList(variableList);
		    LinkedList_destroy(variableList);
		    printf("\nNamed variable lists (data sets) in domain: %s\n", (char*) element->data);
		    LinkedList dataSetList = MmsConnection_getDomainVariableListNames(con, &mmsError, (char*) element->data);
		    LinkedList_printStringList(dataSetList);
		    LinkedList_destroy(dataSetList);
		}
		LinkedList_destroy(nameList); 
		/*************************************************************************/
		/* Abort the connexion */
			    
		printf("Deconnecting ...\n");
		/* Uses the MMS/ACSE abort service to close the connection to the server. */
		MmsConnection_abort(con, &mmsError);	    		    
	}
	else
	    	printf("Connect to server failed!\n");

    	/* Destroy an MmsConnection instance and release all resources. */  
	MmsConnection_destroy(con);	    	
	return;
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_data_attribute()
 * \brief Method to control a device by setting a value to a device
 */
//---------------------------------------------------------------------------------
void set_data_attribute() {
	printf("########### Not functionnal ###########\n");	

	/* Connection the server */
	IedClientError error;	
	IedConnection con = IedConnection_create();
    
	printf("Trying to connect to ip = %s & port = %d \n",p_connection->ip, p_connection->port);
	
	IedConnection_connect(con, &error, p_connection->ip, p_connection->port);
	
	
	
	if (error == IED_ERROR_OK) {
	    /* Connection successful */
	    
	    MmsValue* value;
	    
        /* Control the type of the value and create a new MmsValue */
        if (p_parameter->data_type == DATA_TYPE_BOOLEAN) {
            value = MmsValue_newBoolean(p_parameter->value);
        }
        else if (p_parameter->data_type == DATA_TYPE_INTEGER) {
            //ctlVal = MmsValue_newInt32(p_parameter->value);
          	value = MmsValue_newInteger((int)p_parameter->value);
        } 
        else if (p_parameter->data_type == DATA_TYPE_STRING) {
        	value = MmsValue_newMmsString(p_parameter->value);
        }
        else {
        	value = NULL;
        }
     
        printf("Writing ...\n");
        IedConnection_writeObject(con, &error, p_parameter->data_attribute_reference, DC, value);
     
        if (error != IED_ERROR_OK) {
            printf("Failed to write !\n");
        }
	    MmsValue_delete(value);
	}
	
	else {
	    /* Connection unsuccessful */
	    printf("Connect to server failed!\n");
	}   

    /* Destroy the connection */  
	IedConnection_destroy(con);	    	
	return;	   
	
#if 0	
	/* Connection the server */
	MmsConnection con = MmsConnection_create();
	MmsError mmsError;
	ControlObjectClient control;
    
	printf("trying to connect to ip = %s & port = %d \n",p_connection->ip, p_connection->port);
	
	if (MmsConnection_connect(con, &mmsError, p_connection->ip, p_connection->port)) {
	    /* Connection successful */
	    
	    printf("Connected\n");
	    
	    //control = ControlObjectClient_create("simpleIOGenericIO/GGIO1.SPCSO2", con);
	    control = ControlObjectClient_create(p_parameter->data_attribute_reference, con);

        printf("Control created\n");

        if (ControlObjectClient_select(control)) {
        
            MmsValue* ctlVal;
            /* Control the type of the value and create a new MmsValue */
            if (p_parameter->data_type == DATA_TYPE_BOOLEAN) {
                ctlVal = MmsValue_newBoolean(p_parameter->value);
            }
            else if (p_parameter->data_type == DATA_TYPE_INTEGER) {
                //ctlVal = MmsValue_newInt32(p_parameter->value);
               	  ctlVal = MmsValue_newInteger(p_parameter->value);
            } 
            else if (p_parameter->data_type == DATA_TYPE_STRING) {
                ctlVal = MmsValue_newMmsString(p_parameter->value);
            }
            
            /* Modify the value */      
            if (ControlObjectClient_operate(control, ctlVal, 0 /* operate now */)) {
                printf("Setting value operated successfully\n");
            }
            else {
                printf("failed to operate \n");
            }

            MmsValue_delete(ctlVal);
        }
        else {
            printf("failed to select !\n");
        }

        ControlObjectClient_destroy(control);	
	
	}
	else {
	    /* Connection unsuccessful */
	    printf("Connect to server failed!\n");
	}	    	

    printf("Done\n");
    
    /* Destroy the connection */  
	MmsConnection_destroy(con);	    	
	return;
#endif
}
//---------------------------------------------------------------------------------
/**
 * \fn void read_data_attribute()
 * \brief Method to read a value
 */
//---------------------------------------------------------------------------------
void read_data_attribute() {
	
	/* Connection the server */
	IedClientError error;	
	IedConnection con = IedConnection_create();
	
	int flag = 1;
    
	printf("Trying to connect to ip = %s & port = %d \n",p_connection->ip, p_connection->port);
	
	IedConnection_connect(con, &error, p_connection->ip, p_connection->port);
	
	if (error == IED_ERROR_OK) {
	    /* Connection successful */
	    
	    MmsValue* value = 0;
	    
	    /* read value from server */ 
	    if (p_parameter->functional_constraint == READ_DC) {
	        printf("DC\n");
            value = IedConnection_readObject(con, &error, p_parameter->data_attribute_reference , DC);
        }
	    else if (p_parameter->functional_constraint == READ_MX) {
	        printf("MX\n");
            value = IedConnection_readObject(con, &error, p_parameter->data_attribute_reference , MX);
        }
        else if (p_parameter->functional_constraint == READ_EX) {
            printf("EX\n");
            value = IedConnection_readObject(con, &error, p_parameter->data_attribute_reference , EX);
        }
        else {
            printf("Invalid functional constraint\n");
            flag = 0;
        }
	    
        //MmsValue* value = IedConnection_readObject(con, &error, "IED_DIST_CTRL/CALH1.NamPlt.swRev", DC);
        //MmsValue* value = IedConnection_readObject(con, &error, "IED_DIST_CTRL/CALH1.Mod.ctlModel", CF);
        //sudo ./n61850 -i 192.168.0.2 -p 102 -m read -a IED_DIST_CTRL/CALH1.ErrBoard1.dataNs -fc 2

        /* Display value */
        if (flag) {
            char *val = MmsValue_toString(value);
            printf("Read value: %s\n", val);            
        }		    
	    else {
	        printf("Error while reading\n");
	    }	
	    MmsValue_delete(value);
	    /* Close connection */
	    IedConnection_close(con);    	
	
	}
	else {
	    /* Connection unsuccessful */
	    printf("Connect to server failed!\n");
	}   

    /* Destroy the connection */  
	IedConnection_destroy(con);	    	
	return;	
	
}

//---------------------------------------------------------------------------------
/**
 * \fn static bool downloadHandler(void* parameter, uint8_t* buffer, uint32_t bytesRead)
 * \brief Handle the download of a file
 * \return True if the file was too big
 */
//---------------------------------------------------------------------------------
static bool downloadHandler(void* parameter, uint8_t* buffer, uint32_t bytesRead){

	/* Create the file */
    FILE *file;
    file = fopen(p_parameter->file_name,"w");    

    printf("Received %i bytes\n", bytesRead);
    printf("Start of file --------------\n");
    uint8_t i = 0;
    for(i = 0; i < bytesRead ; i++) {
        printf("%c",buffer[i]);
        fprintf(file,"%c",buffer[i]); /*writes*/
    }
    fclose(file);
    printf("End of file ----------------\n");
    
    if (bufferPosition + bytesRead < MAX_BUFFER_SIZE) {
        memcpy(downloadBuffer + bufferPosition, buffer, bytesRead);
        return false;
    }
    else
        return true;
}

//---------------------------------------------------------------------------------
/**
 * \fn void file() 
 * \brief File listing, downloading or deleting
 */
 //---------------------------------------------------------------------------------
void file() {

    /* Connection */
    IedClientError error;

    IedConnection con = IedConnection_create();

    IedConnection_connect(con, &error, p_connection->ip, p_connection->port);

    if (error == IED_ERROR_OK) {

        /* Get the root directory */
        LinkedList rootDirectory = IedConnection_getFileDirectory(con, &error, NULL);

		/* Error retrieving file directory */
        if (error != IED_ERROR_OK) {
            printf("Error retrieving file directory\n");
			IedConnection_abort(con, &error);
        }
		/* file directory found */
		else {
		
		    /* Show different files in the server */
		    if (function_file == LIST_FILE) {		    
		        
			    LinkedList directoryEntry = LinkedList_getNext(rootDirectory);

			    while (directoryEntry != NULL) {

				    FileDirectoryEntry entry = (FileDirectoryEntry) directoryEntry->data;
				    printf("%s %i\n", FileDirectoryEntry_getFileName(entry), FileDirectoryEntry_getFileSize(entry));
				    directoryEntry = LinkedList_getNext(directoryEntry);
			    }		    
		    }			
			/* Download a file from the server */
			else if(function_file == GET_FILE){     
				IedConnection_getFile(con, &error, p_parameter->file_name, downloadHandler, NULL);// "IEDSERVER.BIN"
				if (error != IED_ERROR_OK)
					printf("Failed to get file!\n");
		    /* Delete file at server */
			}
			else if(function_file == DELETE_FILE){
				/* Delete file at server */
				IedConnection_deleteFile(con, &error, p_parameter->file_name);
				if (error != IED_ERROR_OK)
					printf("Failed to delete file! (code=%i)\n", error);
			}
			else
				printf("Error, no function file selected (-g, -d or -l)\n");
			
			/* Deconnect */
			IedConnection_abort(con, &error);
		
		}       
    }
    else {
        printf("Failed to connect to %s:%i\n",p_connection->ip, p_connection->port);
    }

    IedConnection_destroy(con);
    return;
}


