/*
 * producer_pixbuf.h -- raster image loader based upon gdk-pixbuf
 * Copyright (C) 2003-2004 Ushodaya Enterprises Limited
 * Author: Dan Dennedy <dan@dennedy.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef _PRODUCER_PIXBUF_H_
#define _PRODUCER_PIXBUF_H_

#include <framework/mlt_producer.h>

typedef struct producer_pixbuf_s *producer_pixbuf;

struct producer_pixbuf_s
{
	struct mlt_producer_s parent;
	char *filename;
	int counter;
	int width;
	int height;
	uint8_t *image;
	uint8_t *alpha;
	int is_pal;
};

extern mlt_producer producer_pixbuf_init( const char *filename );

#endif
