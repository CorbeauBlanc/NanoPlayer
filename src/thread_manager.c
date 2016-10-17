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
#include "nanoplayer.h"

t_stopcond	stop;

void		*count_time(void *arg)
{
	t_timemutex *time = arg;
	int			flag = 0;
	
	while (!flag)
	{
		pthread_mutex_lock(&time->mut_time);
		if (time->val)
			time->val--;
		pthread_mutex_unlock(&time->mut_time);
		sleep(1);
		flag = (time->val == 0);
	}
	pthread_cond_signal(&stop.cond_stop);
	pthread_exit(NULL);
}

void		wait_time(unsigned int val)
{
	pthread_t	count_thread;
	t_timemutex time;
	
	time.val = val;
	pthread_create(&count_thread, NULL, count_time, &time);
	pthread_mutex_lock(&stop.mut_stop);
	pthread_cond_wait(&stop.cond_stop, &stop.mut_stop);
	pthread_mutex_unlock(&stop.mut_stop);
}