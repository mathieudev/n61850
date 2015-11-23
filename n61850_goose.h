#pragma once
#ifndef N61850_GOOSE_H
#define N61850_GOOSE_H

/**
 * \file n61850_goose.h
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
#include "mms_value.h"
#include "goose_publisher.h"
#include "goose_subscriber.h"
#include <signal.h>
#include <inttypes.h>

extern void subscribe();
extern void publish();
extern void dos();

#endif
