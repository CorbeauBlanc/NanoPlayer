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
#include <fcntl.h>

#include "fmod.h"
#include "nanoplayer.h"

void	putnbr_fd(int n, int fd)
{
	long	l;
	char	c;

	l = (long)n;
	if (n < 0)
	{
		write(fd, "-", 1);
		l = -l;
	}
	if (n > 9 || n < -9)
		putnbr_fd((int)(l / 10), fd);
	c = '0' + (l % 10);
	write(fd, &c, 1);
}


void	exit_FMOD_error(FMOD_RESULT *res)
{
	fprintf(stderr, "nanoplayer : FMOD : [%d]\n", *res);
	remove("/tmp/nanoplayer");
	exit(EXIT_FAILURE);
}

void	exit_proc_error()
{
	perror("nanoplayer : fork ");
	remove("/tmp/nanoplayer");
	exit(EXIT_FAILURE);
}

void	exit_file_error(char *fct)
{
	fprintf(stderr, "nanoplayer : %s : ", fct);
	perror("");
	remove("/tmp/nanoplayer");
	exit(EXIT_FAILURE);
}

void	exit_memory_error()
{
	perror("nanoplayer : malloc ");
	remove("/tmp/nanoplayer");
	exit(EXIT_FAILURE);
}

void	exit_thread_error()
{
	perror("nanoplayer : pthread_create ");
	remove("/tmp/nanoplayer");
	exit(EXIT_FAILURE);
}

void	exit_instance_error()
{
	fprintf(stderr, "Error : no instance currently running");
	remove("/tmp/nanoplayer");
	exit(EXIT_FAILURE);	
}

void	exit_arguments_error()
{
	fprintf(stderr, "nanoplayer : Not enough arguments");
	remove("/tmp/nanoplayer");
	exit(EXIT_FAILURE);
}

void	*FMOD_error_log(FMOD_RESULT *res)
{
	int		fd;
	mode_t	md;

	md = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	if (!(fd = open("~/.np_log", O_CREAT | O_WRONLY | O_APPEND, md)))
		exit_file_error("open");
	write(fd, "nanoplayer : FMOD : ", 20);
	putnbr_fd(*res, fd);
	close(fd);
	return (NULL);
}