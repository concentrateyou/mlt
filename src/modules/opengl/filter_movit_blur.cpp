/*
 * filter_movit_blur.cpp
 * Copyright (C) 2013 Dan Dennedy <dan@dennedy.org>
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

#include <framework/mlt.h>
#include <string.h>
#include <assert.h>

#include "filter_glsl_manager.h"
#include <movit/blur_effect.h>

static int get_image( mlt_frame frame, uint8_t **image, mlt_image_format *format, int *width, int *height, int writable )
{
	mlt_filter filter = (mlt_filter) mlt_frame_pop_service( frame );
	mlt_properties properties = MLT_FILTER_PROPERTIES( filter );
	GlslManager::get_instance()->lock_service( frame );
	Effect* effect = GlslManager::get_effect( filter, frame );
	if ( effect ) {
		double radius = mlt_properties_anim_get_double( properties, "radius",
			mlt_filter_get_position( filter, frame ),
			mlt_filter_get_length2( filter, frame ) );
		bool ok = effect->set_float( "radius", radius );
		assert(ok);
	}
	GlslManager::get_instance()->unlock_service( frame );
	*format = mlt_image_glsl;
	return mlt_frame_get_image( frame, image, format, width, height, writable );
}

static mlt_frame process( mlt_filter filter, mlt_frame frame )
{
	if ( !mlt_frame_is_test_card( frame ) ) {
		Effect* effect = GlslManager::get_effect( filter, frame );
		if ( !effect ) {
			effect = GlslManager::add_effect( filter, frame, new BlurEffect() );
			assert(effect);
		}
	}
	mlt_frame_push_service( frame, filter );
	mlt_frame_push_get_image( frame, get_image );
	return frame;
}

extern "C" {

mlt_filter filter_movit_blur_init( mlt_profile profile, mlt_service_type type, const char *id, char *arg )
{
	mlt_filter filter = NULL;
	GlslManager* glsl = GlslManager::get_instance();

	if ( glsl && ( filter = mlt_filter_new() ) ) {
		mlt_properties properties = MLT_FILTER_PROPERTIES( filter );
		mlt_properties_set_double( properties, "radius", 3 );
		filter->process = process;
	}
	return filter;
}

}
