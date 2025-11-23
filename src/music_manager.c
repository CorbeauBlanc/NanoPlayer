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

#include "nanoplayer.h"

static t_song		current;
static t_sysmutex	main_system;

FMOD_SYSTEM	*create_system()
{
	FMOD_SYSTEM *system;
	FMOD_RESULT res;

	if ((res = FMOD_System_Create(&system, FMOD_VERSION)) != FMOD_OK)
		exit_FMOD_error(&res);
	if ((res = FMOD_System_Init(system, 10, FMOD_INIT_NORMAL, NULL)) != FMOD_OK)
		exit_FMOD_error(&res);
	return (system);
}

FMOD_SOUND	*create_sound(char* path, FMOD_SYSTEM *sys)
{
	FMOD_RESULT	res;
	FMOD_SOUND	*snd;
	if ((res = FMOD_System_CreateSound(sys, path,FMOD_2D | FMOD_CREATESTREAM,
										NULL, &snd)) != FMOD_OK)
		return ((FMOD_SOUND*)FMOD_error_log(&res));
	return (snd);
}

void		play_sound(FMOD_SOUND *snd, FMOD_SYSTEM *sys)
{
	FMOD_RESULT		res;
	unsigned int	lenght;
	FMOD_Sound_GetLength(snd, &lenght, FMOD_TIMEUNIT_MS);
	lenght = (unsigned int)(lenght / 1000);
	pthread_mutex_lock(&channel.mut);
	if ((res = FMOD_System_PlaySound(sys, snd, NULL, 0, &channel.val))
		 != FMOD_OK)
		exit_FMOD_error(&res);
	pthread_mutex_unlock(&channel.mut);
	wait_time(lenght);
}

void		stop_sound()
{
	if (!exist("/tmp/nanoplayer"))
		exit_instance_error();
	pthread_mutex_lock(&channel.mut);
	FMOD_Channel_Stop(channel.val);
	pthread_mutex_unlock(&channel.mut);
	pthread_mutex_lock(&time_count.mut_time);
	time_count.val = 0;
	pthread_mutex_unlock(&time_count.mut_time);
}

void		read_list(t_list *list)
{
	FMOD_SOUND *sound;
	t_list *tmp, *song;
	
	song = list;
	pthread_mutex_lock(&main_system.mut);
	if (!(main_system.sys = create_system()))
		exit_FMOD_error(NULL);
	pthread_mutex_lock(&current.mut);
	current.status = PLAY;
	pthread_mutex_unlock(&current.mut);
	do
	{
		pthread_mutex_lock(&current.mut);
		if (current.status == PLAY  && song)
		{
			if ((sound = create_sound(song->path, main_system.sys)))
			{
				pthread_mutex_unlock(&current.mut);
				play_sound(sound, main_system.sys);
				FMOD_Sound_Release(sound);
				pthread_mutex_lock(&current.mut);
				if (current.status != PREV)
					song = song->next;
			}
			else
			{
				tmp = song;
				if (song == list)
					list = song->next;
				song = song->next;
				delete_cell(&tmp);
			}
		}
		if (current.status == PREV)
		{
			if (song->prev)
				song = song->prev;
			current.status = PLAY;
		}
		pthread_mutex_unlock(&current.mut);
	}
	while (song && current.status != STOP);
	clear_list(&list);
	FMOD_System_Close(main_system.sys);
	FMOD_System_Release(main_system.sys);
	pthread_mutex_unlock(&main_system.mut);
}

void		music_pause()
{
	if (!exist("/tmp/nanoplayer"))
		exit_instance_error();
	pthread_mutex_lock(&channel.mut);
	FMOD_Channel_SetPaused(channel.val, TRUE);
	pthread_mutex_unlock(&channel.mut);
}

void		music_unpause()
{
	if (!exist("/tmp/nanoplayer"))
		exit_instance_error();
	pthread_mutex_lock(&channel.mut);
	FMOD_Channel_SetPaused(channel.val, FALSE);
	pthread_mutex_unlock(&channel.mut);
	count(NULL);
}
void		music_next()
{
	stop_sound();
	pthread_mutex_lock(&current.mut);
	current.status = PLAY;
	pthread_mutex_unlock(&current.mut);
}
void		music_prev()
{
	stop_sound();
	pthread_mutex_lock(&current.mut);
	current.status = PREV;
	pthread_mutex_unlock(&current.mut);
}
void		music_stop()
{
	stop_sound();
	pthread_mutex_lock(&current.mut);
	current.status = STOP;
	pthread_mutex_unlock(&current.mut);
}
void		music_open()
{
	char	*path;
	FILE	*f_nanoplayer;
	
	music_stop();
	if (!(f_nanoplayer = fopen("/tmp/nanoplayer", "r")))
		exit_file_error("fopen");
	seek_char('\n', f_nanoplayer);
	seek_char('\n', f_nanoplayer);
	path = get_line(f_nanoplayer);
	create_new_instance(path);
}
void		music_volume()
{
	FILE	*f_nanoplayer;
	float	amount;
	char	*line;
	
	if (!exist("/tmp/nanoplayer"))
		exit_instance_error();
	if (!(f_nanoplayer = fopen("/tmp/nanoplayer", "r")))
		exit_file_error("fopen");
	seek_char('\n', f_nanoplayer);
	seek_char('\n', f_nanoplayer);
	pthread_mutex_lock(&channel.mut);
	FMOD_Channel_GetVolume(channel.val, &amount);
	line = get_line(f_nanoplayer);
	amount += ((float)atoi(line) / 10);
	if (amount > 0)
		FMOD_Channel_SetVolume(channel.val, amount);
	pthread_mutex_unlock(&channel.mut);
	fclose(f_nanoplayer);
	free(line);
}

t_operation	*create_operation(t_action action, void (*function)(void))
{
	t_operation	*tmp;
	if (!(tmp = (t_operation*)malloc(sizeof(t_operation))))
		exit_memory_error();
	tmp->action = action;
	tmp->function = function;
	return (tmp);
}

t_operation	**init_tab_operations()
{
	t_operation	**tab;
	
	if (!(tab = (t_operation**)malloc(sizeof(*tab) * 7)))
		exit_memory_error();
	tab[0] = create_operation(PAUSE, music_pause);
	tab[1] = create_operation(PLAY, music_unpause);
	tab[2] = create_operation(NEXT, music_next);
	tab[3] = create_operation(PREV, music_prev);
	tab[4] = create_operation(STOP, music_stop);
	tab[5] = create_operation(OPEN, music_open);
	tab[6] = create_operation(VOL, music_volume);
	return (tab);
}

void		free_tab_operations(t_operation	***tab)
{
	int	i = -1;
	
	while (++i < 6)
		free((*tab)[i]);
	free(*tab);
}
