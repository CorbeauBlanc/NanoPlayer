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

#define _POSIX_SOURCE
#include "nanoplayer.h"

void	write_pid()
{
	FILE	*f_nanoplayer;

	if ((f_nanoplayer = fopen("/tmp/nanoplayer", "w+")) == NULL)
		exit_file_error("fopen");
	fprintf(f_nanoplayer, "%d\n", (int)getpid());
	fclose(f_nanoplayer);
}

void	*sig_manager(void *arg)
{
	
}

void	sig_handler(int sig)
{
	(void)sig;
	printf("test\n");
	exit(EXIT_SUCCESS);
}

void	init_handler()
{
	t_sigaction *init;
	if (!(init = (t_sigaction*)malloc(sizeof(t_sigaction))))
		exit_memory_error();
	init->sa_handler = &sig_handler;
	init->sa_flags = 0;
	sigemptyset(&init->sa_mask);
	sigaction(SIGUSR1, init, NULL);
}