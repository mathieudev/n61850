#pragma once
#ifndef N61850_MMS_H
#define N61850_MMS_H

/**
 * \file n61850_mms.h
 * \brief MMS oriented methods
 * \author Devaud Mathieu, Marty Kilian
 * \version 0.1
 * \date 21 January 2015
 *
 * 
 *
 */


/*
 *
 *  This is the most simple example. It illustrates how to create an MmsConnection
 *  object and connect to a MMS server.
 *
 *  Copyright 2013 Michael Zillgith
 *
 *	This file is part of libIEC61850.
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

#include "mms_client_connection.h"
#include "iec61850_client.h"
#include "hal.h"
#include "hal_thread.h"


#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>


extern void set_mms_connection();
extern void discover_mms();
extern void scan_server();
extern void set_data_attribute();
extern void read_data_attribute();
extern void file();

#define MAX_BUFFER_SIZE 2000000

#endif
