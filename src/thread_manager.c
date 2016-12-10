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

pthread_t	*new_thread()
{
	++threads.size;
	if (!(threads.tab = realloc(threads.tab, threads.size)))
		exit_memory_error();
	return (&threads.tab[threads.size - 1]);
}

void		wait_threads()
{
	int	i = -1;
	
	while(++i < threads.size)
		pthread_join(threads.tab[i], NULL);
}

void		*count(void *arg)
{
	FMOD_BOOL		playing = TRUE;
	FMOD_BOOL		paused = FALSE;

	(void)arg;
	time_count.val++;
	while (playing && !paused)
	{
		pthread_mutex_lock(&time_count.mut_time);
		if (playing && !paused && time_count.val)
			time_count.val--;
		pthread_mutex_unlock(&time_count.mut_time);
		pthread_mutex_lock(&channel.mut);
		FMOD_Channel_IsPlaying(channel.val, &playing);
		FMOD_Channel_GetPaused(channel.val, &paused);
		pthread_mutex_unlock(&channel.mut);
		if (playing && !paused && time_count.val)
			sleep(1);
	}
	pthread_cond_broadcast(&stop.cond_stop);
	pthread_exit(NULL);
}

void		wait_time(unsigned int val)
{
	pthread_t	count_thread;

	time_count.val = val;
	if(pthread_create(&count_thread, NULL, count, NULL) == -1)
		exit_thread_error();
	while (time_count.val)
	{
		pthread_mutex_lock(&stop.mut_stop);
		pthread_cond_wait(&stop.cond_stop, &stop.mut_stop);
		pthread_mutex_unlock(&stop.mut_stop);
	}
	int null = 0;
	(void)null;
}