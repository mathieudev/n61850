#pragma once
#ifndef N61850_H
#define N61850_H

/**
 * \file n61850.h
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
 * Prototypes of each the method used in n61850.c
 */
//---------------------------------------------------------------------------------

/* Processing functions */
extern int launch_action (int argc, char* argv[]);
extern void function (char* argv[], int index_function);
extern int tokenize (int i, int argc, char *argv[]);

/* Connection functions */
extern void set_port (char* argv[], int index_function);
extern void set_ip_dest (char* argv[], int index_function);

extern void set_connection();

extern void discover();

/* Goose functions */
extern void dos_function();
extern void publish_function();
extern void subscribe_function();
extern void set_data_set_id (char* argv[], int index_function);
extern void set_description_id (char* argv[], int index_function);
extern void set_appid (char* argv[], int index_function);

/* File functions */
extern void file_function();
extern void set_file_name(char* argv[], int index_function);
extern void set_list_file (char* argv[], int index_function);
extern void set_delete_file(char* argv[], int index_function);
extern void set_get_file(char* argv[], int index_function);

/* Read and set functions */
extern void set_value (char* argv[], int index_function);
extern void set_data_attribute_reference (char* argv[], int index_function);
extern void set_data_type (char* argv[], int index_function);
extern void set_functional_constraint (char* argv[], int index_function);

#endif
