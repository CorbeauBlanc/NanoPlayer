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

t_chanmutex	channel;

FMOD_SYSTEM	*create_system()
{
	FMOD_SYSTEM *system;
	FMOD_RESULT res;

	if ((res = FMOD_System_Create(&system)) != FMOD_OK)
		exit_FMOD_error(res);
	if ((res = FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL)) != FMOD_OK)
		exit_FMOD_error(res);

	return (system);
}

FMOD_SOUND	*create_sound(char* path, FMOD_SYSTEM *sys)
{
	FMOD_RESULT	res;
	FMOD_SOUND	*snd;
	if ((res = FMOD_System_CreateSound(sys, path,FMOD_2D | FMOD_CREATESTREAM,
										NULL, &snd)) != FMOD_OK)
		exit_FMOD_error(res);
	
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
		exit_FMOD_error(res);
	pthread_mutex_unlock(&channel.mut);
	wait_time(lenght);
	FMOD_Sound_Release(snd);
}

void		music_pause() {}
void		music_unpause() {}
void		music_next() {}
void		music_prev() {}
void		music_stop() {}
void		music_open() {}
void		music_volume_up() {}
void		music_volume_down() {}

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
	
	if (!(tab = (t_operation**)malloc(sizeof(*tab) * 8)))
		exit_memory_error();
	tab[0] = create_operation(PAUSE, music_pause);
	tab[1] = create_operation(PLAY, music_unpause);
	tab[2] = create_operation(NEXT, music_next);
	tab[3] = create_operation(PREV, music_prev);
	tab[4] = create_operation(STOP, music_stop);
	tab[5] = create_operation(OPEN, music_open);
	tab[6] = create_operation(VOLUP, music_volume_up);
	tab[7] = create_operation(VOLDOWN, music_volume_down);
	return (tab);
}