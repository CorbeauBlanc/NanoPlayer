/*
 * Copyright (C) 2016 shiro
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "fmod.h"

void	exit_FMOD_error(FMOD_RESULT *res)
{
	fprintf(stderr, "nanoplayer : FMOD : [%d]\n", *res);
	exit(EXIT_FAILURE);
}

void	exit_proc_error()
{
	perror("nanoplayer : fork ");
	exit(EXIT_FAILURE);
}

void	exit_file_error(char *fct)
{
	fprintf(stderr, "nanoplayer : %s ", fct);
	perror("");
	exit(EXIT_FAILURE);
}

void	exit_memory_error()
{
	perror("nanoplayer : malloc ");
	exit(EXIT_FAILURE);
}

void	exit_thread_error()
{
	perror("nanoplayer : pthread_create ");
	exit(EXIT_FAILURE);
}

void	exit_instance_error()
{
	fprintf(stderr, "Error : no instance currently running");
	exit(EXIT_FAILURE);	
}