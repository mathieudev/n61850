/**
 * \file n61850_global.c
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
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "n61850_global.h"
//---------------------------------------------------------------------------------
/*
 * Instance from each of defined structure
 */
//---------------------------------------------------------------------------------
// Init of the Structure of command argument (parameter)
const struct Command command[] = {
		{"-f", function},
		{"-i", set_ip_dest},
		{"-p", set_port},
		{"-l", set_list_file},
		{"-g", set_get_file},
		{"-d", set_delete_file},
		{"-n", set_file_name},
		{"-v", set_value},
		{"-t", set_data_type},
		{"-a", set_data_attribute_reference},
		{"-fc", set_functional_constraint},
		{"-di", set_description_id},
		{"-si", set_data_set_id},
		{"-ai", set_appid},
		{"", NULL}
};
const struct Command *p_command = command;

// Init of the Structure of action argument (-m)
const struct Action action[] = {
		{"connect", set_connection},
		{"discover", discover},
		{"scan", scan_server}, 
		{"publish", publish_function},
		{"file", file_function},
		{"set", set_data_attribute},
		{"read", read_data_attribute},
		{"subscribe", subscribe_function},
		{"dos", dos_function},
		{"", NULL}
};
const struct Action *p_action = action;

// Init of the Structure of connection caracteristic
struct Connection connection = {
		DEFAULT_PORT,
		DEFAULT_IP
};
struct Connection *p_connection = &connection;

// Init of the Structure of parameter caracteristic
struct Parameter parameter = {
		NULL,
		NO_DATA_TYPE,
		0,
		0,
		NULL,
		NULL,
		NULL,
		DEFAULT_APPID
};
struct Parameter *p_parameter = &parameter;

// Init of the mode
int mode = NO_MODE;
int function_file = NO_FUNCTION_FILE;
