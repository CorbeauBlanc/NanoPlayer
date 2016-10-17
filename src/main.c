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


#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include "fmod.h"
#include "nanoplayer.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;
	
//	FMOD_SYSTEM *system = create_system();
//	FMOD_SOUND *sound = create_sound("/home/shiro/Bureau/fmod_test.mp3", system);
//
//	play_sound(sound, system);
//
//	FMOD_System_Close(system);
//	FMOD_System_Release(system);
	
	pid_t pid = fork();
	if (pid == 0)
	{
		init_handler();
		while(1);
	}
	else
	{
		printf("|\nV\n");
		sleep(3);
		kill(pid, SIGUSR1);
		wait(NULL);
	}
	exit(EXIT_SUCCESS);
}

