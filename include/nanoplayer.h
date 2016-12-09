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
# define TRUE 1
# define FALSE 0
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>

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

t_stopcond	stop;
t_timemutex time_count;
t_chanmutex	channel;

void		exit_arguments_error();
void		exit_file_error(char *fct);
void		exit_FMOD_error(FMOD_RESULT *res);
void		exit_instance_error();
void		exit_memory_error();
void		exit_proc_error();
void		exit_thread_error();
void		*FMOD_error_log(FMOD_RESULT *res);

int			exist(char *path);
char		*get_line(FILE *stream);
int			is_dir(char *path);
int			is_file(char *path);
int			seek_char(char c, FILE *stream);

void		clear_list(t_list **head);
t_list		*create_list(char **tab);
void		delete_cell(t_list **cell);
void		insert_cell(t_list **head, char *path);

FMOD_SOUND	*create_sound(char* path, FMOD_SYSTEM *sys);
FMOD_SYSTEM	*create_system();
void		free_tab_operations(t_operation	***tab);
t_operation	**init_tab_operations();

void		music_next();
void		music_open();
void		music_pause();
void		music_prev();
void		music_stop();
void		music_unpause();
void		music_volume();
void		play_sound(FMOD_SOUND *snd, FMOD_SYSTEM *sys);
void		read_list(t_list *list);

void		*count(void *arg);
void		free_list_path(char ***list);
char		**get_dir_content(char *path);
pid_t		get_pid();
void		init_handler(void);
void		send_operation(pid_t pid, char op, char *arg2);
void		wait_time(unsigned int lenght);
void		write_pid(void);

void		create_new_instance(char *path);

#endif /* NANOPLAYER_H */

