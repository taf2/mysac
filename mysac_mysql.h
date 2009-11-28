/*
 * Copyright (c) 2009 Todd Fisher
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License.
 *
 * Header to include mysql.h
 *
 */

/** @file */ 

#ifndef __MYSAC_MYSQL_H__
#define __MYSAC_MYSQL_H__

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_MYSQL_H
#include <mysql.h>
#include <errmsg.h>
#include <my_global.h>
#include <m_string.h>
#elif HAVE_MYSQL_MYSQL_H
#include <mysql/mysql.h>
#include <mysql/errmsg.h>
#include <mysql/my_global.h>
#include <mysql/m_string.h>
#else
#error "missing mysql headers"
#endif

#endif
