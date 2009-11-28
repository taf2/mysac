/*
 * Copyright (c) 2009 Thierry FOURNIER
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License.
 *
 */

#ifndef __MYSAC_NET_H__
#define __MYSAC_NET_H__

int mysac_socket_connect(char *socket_name);
int mysac_socket_connect_check(int fd);
ssize_t mysac_read(int fd, void *buf, size_t count, int *err);
ssize_t write(int fd, const void *buf, size_t len, int *err);

#endif
