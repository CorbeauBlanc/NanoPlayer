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

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include "nanoplayer.h"

void	wait_time(unsigned int lenght)
{
	sleep(lenght);
}

int		new_proc()
{
	pid_t	pid;
	FILE	*f_nanoplayer;
	
	if ((pid = fork()) == -1)
		exit_proc_error();
	else if (pid != 0)
	{
		if ((f_nanoplayer = fopen("/tmp/nanoplayer", "w+")) == NULL)
			exit_file_error("fopen");
		fprintf(f_nanoplayer, "%d", (int)pid);
		fclose(f_nanoplayer);
		return (0);
	}
	return (1);
}