/*
 * media_list_player.c - libvlc smoke test
 *
 * $Id$
 */

/**********************************************************************
 *  Copyright (C) 2007 Rémi Denis-Courmont.                           *
 *  This program is free software; you can redistribute and/or modify *
 *  it under the terms of the GNU General Public License as published *
 *  by the Free Software Foundation; version 2 of the license, or (at *
 *  your option) any later version.                                   *
 *                                                                    *
 *  This program is distributed in the hope that it will be useful,   *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of    *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.              *
 *  See the GNU General Public License for more details.              *
 *                                                                    *
 *  You should have received a copy of the GNU General Public License *
 *  along with this program; if not, you can get it from:             *
 *  http://www.gnu.org/copyleft/gpl.html                              *
 **********************************************************************/

#include "test.h"

static void media_list_add_file_path(libvlc_instance_t *vlc, libvlc_media_list_t *ml, const char * file_path)
{
    libvlc_media_t *md = libvlc_media_new (vlc, file_path, &ex);
    catch ();

    libvlc_media_list_add_media (ml, md, &ex);
    catch ();

    libvlc_media_release (md);
}

static void test_media_list_player_next(const char** argv, int argc)
{
    libvlc_instance_t *vlc;
    libvlc_media_t *md;
    libvlc_media_list_t *ml;
    libvlc_media_list_player_t *mlp;
    
    const char * file = test_default_sample;
    
    log ("Testing media player next()\n");
    
    libvlc_exception_init (&ex);
    vlc = libvlc_new (argc, argv, &ex);
    catch ();
    
    md = libvlc_media_new (vlc, file, &ex);
    catch ();
    
    ml = libvlc_media_list_new (vlc, &ex);
    catch ();
    
    mlp = libvlc_media_list_player_new (vlc, &ex);
    catch ();

    libvlc_media_list_add_media (ml, md, &ex);
    catch ();

    // Add three media
    media_list_add_file_path (vlc, ml, file);
    media_list_add_file_path (vlc, ml, file);
    media_list_add_file_path (vlc, ml, file);

    libvlc_media_list_player_set_media_list (mlp, ml, &ex);
    
    libvlc_media_list_player_play_item (mlp, md, &ex);
    catch ();

    libvlc_media_release (md);

    usleep(500000);
    
    libvlc_media_list_player_next (mlp, &ex);
    catch ();

    libvlc_media_list_player_pause (mlp, &ex);
    catch();

    usleep(500000);
    
    libvlc_media_list_player_next (mlp, &ex);
    catch ();
    
    libvlc_media_list_player_stop (mlp, &ex);
    catch ();

    usleep(500000);
    
    libvlc_media_list_player_next (mlp, &ex);
    catch ();
        
    libvlc_media_list_player_release (mlp);
    catch ();
    
    libvlc_release (vlc);
    catch ();
}

static void test_media_list_player_pause_stop(const char** argv, int argc)
{
    libvlc_instance_t *vlc;
    libvlc_media_t *md;
    libvlc_media_list_t *ml;
    libvlc_media_list_player_t *mlp;

    const char * file = test_default_sample;

    log ("Testing play and pause of %s using the media list.\n", file);

    libvlc_exception_init (&ex);
    vlc = libvlc_new (argc, argv, &ex);
    catch ();

    md = libvlc_media_new (vlc, file, &ex);
    catch ();

    ml = libvlc_media_list_new (vlc, &ex);
    catch ();

    mlp = libvlc_media_list_player_new (vlc, &ex);

    libvlc_media_list_add_media( ml, md, &ex );
    catch ();

    libvlc_media_list_player_set_media_list( mlp, ml, &ex );

    libvlc_media_list_player_play_item( mlp, md, &ex );
    catch ();

    libvlc_media_list_player_pause (mlp, &ex);
    catch();

    libvlc_media_list_player_stop (mlp, &ex);
    catch ();

    libvlc_media_release (md);

    libvlc_media_list_player_release (mlp);
    catch ();

    libvlc_release (vlc);
    catch ();
}

static void test_media_list_player_play_item_at_index(const char** argv, int argc)
{
    libvlc_instance_t *vlc;
    libvlc_media_t *md;
    libvlc_media_list_t *ml;
    libvlc_media_list_player_t *mlp;

    const char * file = test_default_sample;

    log ("Testing play_item_at_index of %s using the media list.\n", file);

    libvlc_exception_init (&ex);
    vlc = libvlc_new (argc, argv, &ex);
    catch ();

    md = libvlc_media_new (vlc, file, &ex);
    catch ();

    ml = libvlc_media_list_new (vlc, &ex);
    catch ();

    mlp = libvlc_media_list_player_new (vlc, &ex);

    libvlc_media_list_add_media( ml, md, &ex );
    catch ();

    libvlc_media_list_player_set_media_list( mlp, ml, &ex );

    libvlc_media_list_player_play_item_at_index( mlp, 0, &ex );
    catch ();

    libvlc_media_list_player_stop (mlp, &ex);
    catch ();

    libvlc_media_release (md);
    catch ();

    libvlc_media_list_player_release (mlp);
    catch ();

    libvlc_release (vlc);
    catch ();
}


int main (void)
{
    test_init();

    test_media_list_player_pause_stop (test_defaults_args, test_defaults_nargs);
    test_media_list_player_play_item_at_index (test_defaults_args, test_defaults_nargs);
    if(0) // Core hangs here, because it doesn't support callback removal from callbacks (variable)
        test_media_list_player_next (test_defaults_args, test_defaults_nargs);

    return 0;
}
