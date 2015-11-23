
#pragma once
#ifndef N61850_GLOBAL_H
#define N61850_GLOBAL_H

/**
 * \file n61850_global.h
 * \brief Global structure of the programm
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

#include "n61850.h"
#include "n61850_mms.h"
#include "n61850_goose.h"


//---------------------------------------------------------------------------------
/*
 * Define part
 */
//---------------------------------------------------------------------------------
#define NO_MODE 0
#define MODE_MMS 1
#define MODE_GOOSE 2
#define DEFAULT_PORT 102
#define DEFAULT_IP "localhost"

#define DEFAULT_APPID 1000

#define NO_DATA_TYPE 0
#define DATA_TYPE_BOOLEAN 1
#define DATA_TYPE_INTEGER 2
#define DATA_TYPE_STRING 3

#define NO_FC      0
#define READ_DC    1
#define READ_MX    2
#define READ_EX    3

#define NO_FUNCTION_FILE 0
#define LIST_FILE 1
#define GET_FILE 2
#define DELETE_FILE 3



//---------------------------------------------------------------------------------
/*
 * List of the new type used by the n61850 tool
 */
//---------------------------------------------------------------------------------

/** \typedef int (*operation_t) (char* argv[], int index_function)  */
typedef void (*operation_t) (char* argv[], int index_function);
/** \typedef void (*action_t) () */
typedef void (*action_t) ();

//---------------------------------------------------------------------------------
/*
 * List of the structure used by the n61850 tool
 */
//---------------------------------------------------------------------------------

/**
 * \struct 	Command
 * Contain the link between the input  and the configuration methods in the 
 * programm. Check the configuration parameters before the application methods
 */
struct Command {    
    const char* cmd_string; /*!< input from the user */
    operation_t cmd;        /*!< command linked to the input */
};
extern const struct Command command[];
extern const struct Command *p_command;
//---------------------------------------------------------------------------------
/**
 * \struct Action
 * Contain the link between the string entered as parameter and the application 
 * methods in the programm. Check the application parameters after the 
 * configuration parameters.
 */
struct Action {
    const char* act_string; /*!< input from the user */
    action_t act;           /*!< command linked to the input */
};
extern const struct Action action[];
extern const struct Action *p_action;
//---------------------------------------------------------------------------------
/**
 * \struct Connection
 * \brief Connection informations
 *
 * This struct contain the information of 
 * the ip address and the port of the target
 */
struct Connection {
	int port;   /*!< port */
	char* ip;   /*!< ip address */
};
extern struct Connection connection;
extern struct Connection *p_connection;

//---------------------------------------------------------------------------------
/**
 * \struct Parameter
 * \brief Parameters of the functions
 *
 * This struct contain the paramaters of the functions
 */
struct Parameter {
	char* data_attribute_reference;     /*!< data attribute reference */
	int data_type;                      /*!< type of the data to send */
	int functional_constraint;          /*!< functional constraint */
	void* value;                        /*!< value of the data to send */
	char* file_name;                    /*!< name of the file */
	char* description_id;               /*!< description id of a GOOSE message */ 
	char* data_set_id;                  /*!< dataset id of a GOOSE message */
	uint16_t appid;	              	    /*!< application id of a GOOSE message */
};
extern struct Parameter parameter;
extern struct Parameter *p_parameter;

//---------------------------------------------------------------------------------
/*
 * List of the variable used by the n61850 tool
 */
//---------------------------------------------------------------------------------
extern int mode;
extern int function_file;


#endif
