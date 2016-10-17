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

#ifndef NANOPLAYER_H
# define NANOPLAYER_H
# include "fmod.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <pthread.h>

typedef	struct		s_stopcond
{
	pthread_cond_t	cond_stop;
	pthread_mutex_t	mut_stop;
}					t_stopcond;

typedef	struct		s_timemutex
{
	unsigned int	val;
	pthread_mutex_t	mut_time;
}					t_timemutex;

typedef struct		s_chanmutex
{
	FMOD_CHANNEL	*val;
	pthread_mutex_t	mut;
}					t_chanmutex;

typedef struct		sigaction t_sigaction;

typedef enum		action
{
	PLAY, PAUSE, NEXT, PREV, STOP, OPEN, VOLUP, VOLDOWN
};

void		exit_FMOD_error(FMOD_RESULT res);
void		exit_proc_error();
void		exit_file_error(char *fct);
void		exit_memory_error();

void		wait_time(unsigned int lenght);
void		write_pid();
void		init_handler();

FMOD_SYSTEM	*create_system();
FMOD_SOUND	*create_sound(char* path, FMOD_SYSTEM *sys);
void		play_sound(FMOD_SOUND *snd, FMOD_SYSTEM *sys);

#endif /* NANOPLAYER_H */

