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

#ifndef STRUCTURES_H
# define STRUCTURES_H
# include <pthread.h>
# include "fmod.h"

	typedef enum		e_action
{
	PLAY, PAUSE, NEXT, PREV, STOP, OPEN, VOL
}					t_action;

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

typedef struct		s_sysmutex
{
	FMOD_SYSTEM		*sys;
	pthread_mutex_t	mut;
}					t_sysmutex;

typedef struct		s_threads
{
	pthread_t		*tab;
	int				size;
}					t_threads;

typedef	struct		s_operation
{
	t_action		action;
	void			(*function)(void);
}					t_operation;

typedef struct		s_list
{
	char			*path;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

typedef struct		s_song
{
	pthread_mutex_t	mut;
	t_action		status;
}					t_song;

typedef struct		sigaction	t_sigaction;

#endif
