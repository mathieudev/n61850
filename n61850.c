/**
 * \file n61850.c
 * \brief Handle the input from the user
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

//---------------------------------------------------------------------------------
/*
 * Include part
 */
//---------------------------------------------------------------------------------
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "n61850_global.h"

//---------------------------------------------------------------------------------
/**
 * \fn void set_connection()
 * \brief Method who open the connection from the MMS client to a MMS server
 */
//---------------------------------------------------------------------------------
void set_connection(){
	if(mode == 1)
		set_mms_connection();
	else if(mode == 2)
		printf("Error, cannot do a connection in GOOSE mode\n");
	else
		printf("Error, no mode selected (-f)\n");
	return;
}

//---------------------------------------------------------------------------------
/**
 * \fn void discover()
 * \brief Method who open the connection from the MMS client to a MMS server
 */
//---------------------------------------------------------------------------------
void discover(){
	discover_mms();
	return;
}

//---------------------------------------------------------------------------------
/**
 * \fn void publish_function()
 * \brief Method who check the mode goose for publish
 */
//---------------------------------------------------------------------------------
void publish_function(){
	if(mode == 2)
		publish();
	else if(mode == 1)
		printf("Error, cannot be publisher in MMS mode\n");
	else
		printf("Error, no mode selected (-f)\n");
	return;
}

//---------------------------------------------------------------------------------
/**
 * \fn void subscribe_function()
 * \brief Method who check the mode goose for subscribe
 */
//---------------------------------------------------------------------------------
void subscribe_function(){
	if(mode == 2)
		subscribe();
	else if(mode == 1)
		printf("Error, cannot be subscriber in MMS mode\n");
	else
		printf("Error, no mode selected (-f)\n");
	return;
}
//---------------------------------------------------------------------------------
/**
 * \fn void dos_function()
 * \brief Method who check the mode goose for subscribe
 */
//---------------------------------------------------------------------------------
void dos_function(){
	if(mode == 2)
		dos();
	else if(mode == 1)
		printf("Error, cannot be subscriber in MMS mode\n");
	else
		printf("Error, no mode selected (-f)\n");
	return;
}


//---------------------------------------------------------------------------------
/**
 * \fn void file_function()
 * \brief Method who check the mode mms for file function
 */
//---------------------------------------------------------------------------------
void file_function(){
	if(mode == 1)
		file();
	else if(mode == 2)
		printf("Error, cannot process file in GOOSE mode\n");
	else
		printf("Error, no mode selected (-f)\n");
	return;
}

//---------------------------------------------------------------------------------
/**
 * \fn int launch_action (int argc, char* argv[])
 * \brief Method who search the action argument from the list of the argument passed
 */
//---------------------------------------------------------------------------------
int launch_action (int argc, char* argv[]){
	int i;
	int flag_action_ok = 0;
	for(i = 1; i < argc && flag_action_ok == 0; i++) {
		flag_action_ok = 0;
		p_action = action;
		while ((p_action->act != NULL) && (strcmp (argv[i], p_action->act_string) != 0)) {
			// if action string tested is NOT in list of action
			p_action++;
		}
		if (p_action->act != NULL){
			// if command string tested is in list of command
			p_action->act ();
			flag_action_ok = 1;		
		}
	}
	if (flag_action_ok==0){
		printf("Error, the argument after -m is not recognized\n");
		return -1;
	}
	else{
		return 0;
	}
}


//---------------------------------------------------------------------------------
/**
 * \fn void set_data_attribute_reference (char* argv[], int index_function)
 * \brief Method who set the data_attribute_reference (set and read)
 */
//---------------------------------------------------------------------------------
void set_data_attribute_reference (char* argv[], int index_function){
	printf("data_attribute_reference = %s\n",argv[index_function+1]);
	p_parameter->data_attribute_reference = argv[index_function+1];
	
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_data_type (char* argv[], int index_function)
 * \brief Method who set the data_type (set)
 */
//---------------------------------------------------------------------------------
void set_data_type (char* argv[], int index_function){
	printf("data_type = %s\n",argv[index_function+1]);
	p_parameter->data_type = atoi(argv[index_function+1]);
	
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_appid (char* argv[], int index_function)
 * \brief Method who set the appid (set)
 */
//---------------------------------------------------------------------------------
void set_appid (char* argv[], int index_function){
	printf("appid = %s\n",argv[index_function+1]);
	p_parameter->appid = (uint8_t)atoi(argv[index_function+1]);
	
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_functional_constraint (char* argv[], int index_function)
 * \brief Method who set the functional constraint (read)
 */
//---------------------------------------------------------------------------------
void set_functional_constraint (char* argv[], int index_function){
	printf("functional_constraint = %s\n",argv[index_function+1]);
	p_parameter->functional_constraint = atoi(argv[index_function+1]);
	
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_data_set_id (char* argv[], int index_function)
 * \brief Method who set the data_set_id
 */
//---------------------------------------------------------------------------------
void set_data_set_id (char* argv[], int index_function){
	printf("data_set_id = %s\n",argv[index_function+1]);
	p_parameter->data_set_id = argv[index_function+1];
	
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_description_id (char* argv[], int index_function)
 * \brief Method who set the description_id
 */
//---------------------------------------------------------------------------------
void set_description_id (char* argv[], int index_function){
	printf("description_id = %s\n",argv[index_function+1]);
	p_parameter->description_id = argv[index_function+1];
	
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_value (char* argv[], int index_function)
 * \brief Method who set the value
 */
//---------------------------------------------------------------------------------
void set_value (char* argv[], int index_function){
	printf("value = %s\n",argv[index_function+1]);
	p_parameter->value = argv[index_function+1];
	
}


//---------------------------------------------------------------------------------
/**
 * \fn void set_port (char* argv[], int index_function)
 * \brief Method who set the port number of the next action
 */
//---------------------------------------------------------------------------------
void set_port (char* argv[], int index_function){
	printf("port = %s\n",argv[index_function+1]);
	p_connection->port = atoi(argv[index_function+1]);
	
}


//---------------------------------------------------------------------------------
/**
 * \fn void set_file_name (char* argv[], int index_function)
 * \brief Method who set the filename of the target of the next action
 */
//---------------------------------------------------------------------------------
void set_file_name (char* argv[], int index_function){
	printf("filename = %s\n",argv[index_function+1]);
	p_parameter->file_name = argv[index_function+1];
	
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_ip_dest (char* argv[], int index_function)
 * \brief Method who set the destination ip address of the next action
 */
//---------------------------------------------------------------------------------
void set_ip_dest (char* argv[], int index_function){
	printf("ip destination = %s\n",argv[index_function+1]);
	p_connection->ip = argv[index_function+1];
	
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_list_file (char* argv[], int index_function)
 * \brief Method who put the LIST_FILE mode of the next action
 */
//---------------------------------------------------------------------------------
void set_list_file (char* argv[], int index_function){
	printf("mode file = list_file\n");
	function_file = LIST_FILE;
	
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_get_file (char* argv[], int index_function)
 * \brief Method who put the GET_FILE mode of the next action
 */
//---------------------------------------------------------------------------------
void set_get_file (char* argv[], int index_function){
	printf("mode file = get_file\n");
	function_file = GET_FILE;
	
}

//---------------------------------------------------------------------------------
/**
 * \fn void set_delete_file (char* argv[], int index_function)
 * \brief Method who put the DELETE_FILE mode of the next action
 */
//---------------------------------------------------------------------------------
void set_delete_file (char* argv[], int index_function){
	printf("mode file = delete_file\n");
	function_file = DELETE_FILE;
	
}

//---------------------------------------------------------------------------------
/**
 * \fn int function (char* argv[], int index_function)
 * \brief Method who set the mode of the next action (MMS or GOOSE)
 * 
 */
//---------------------------------------------------------------------------------
void function (char* argv[], int index_function){
	printf("mode = %s\n",argv[index_function +1]);
	if(strcmp(argv[index_function +1], "mms")==0){
		mode = MODE_MMS;		
	}
	else if(strcmp(argv[index_function +1], "goose")==0){
		mode = MODE_GOOSE;		
	}
	else {
		printf("Error, the argument after -f is not recognized\n");		
	}
}

//---------------------------------------------------------------------------------
/**
 * \fn int tokenize (int i, int argc, char *argv[])
 * \brief Method who parse and process each argument except actions arguments
 * \return -1 if no action passed as parameter
 */
//---------------------------------------------------------------------------------
int tokenize (int i, int argc, char *argv[]){
	
	int flag_launch_ok = 0;
	//------- parse argument for configuration
	for(; i < argc; i++) {
		p_command = command;
		while ((p_command->cmd != NULL) && (strcmp (argv[i], p_command->cmd_string) != 0)) {
			// if command string tested is NOT in list of command
			p_command++;
		}
		if (p_command->cmd != NULL){
			// if command string tested is in list of command
			p_command->cmd (&argv[0], i);		
		}
	}
	//------- parse argument for launch action
	
	for(i = 1; i < argc && flag_launch_ok == 0; i++) {
		if ((strcmp (argv[i], "-m") == 0)) {
			// if argument -m is detected 
			launch_action(argc, &argv[0]);
			flag_launch_ok = 1;
		}
	}
	if(flag_launch_ok ==0){
		printf("no action passed as parameter (-m)\n");
		return -1;
	}
	else {
        	return 0;
	}
}


//---------------------------------------------------------------------------------
/**
 * \fn int main(int argc, char *argv[])
 * \brief Main method who launch the n61850 tool
 * \return End of the programm
 */
//---------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
	int i = 1;
	tokenize(i, argc, &argv[0]);
    return (0);
}


