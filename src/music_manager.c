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

#include <stdlib.h>
#include <unistd.h>
#include "fmod.h"
#include "nanoplayer.h"

void		wait(unsigned int lenght)
{
	sleep(lenght);
}

FMOD_SYSTEM	*create_system()
{
	FMOD_SYSTEM *system;
	FMOD_RESULT res;

	if ((res = FMOD_System_Create(&system)) != FMOD_OK)
		exit_error(res);
	if ((res = FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL)) != FMOD_OK)
		exit_error(res);

	return (system);
}

FMOD_SOUND	*create_sound(char* path, FMOD_SYSTEM *sys)
{
	FMOD_RESULT	res;
	FMOD_SOUND	*snd;
	if ((res = FMOD_System_CreateSound(sys, path,FMOD_2D | FMOD_CREATESTREAM,
										NULL, &snd)) != FMOD_OK)
		exit_error(res);
	
	return (snd);
}

void		play_sound(FMOD_SOUND *snd, FMOD_SYSTEM *sys)
{
	FMOD_RESULT		res;
	unsigned int	lenght;
	FMOD_Sound_GetLength(snd, &lenght, FMOD_TIMEUNIT_MS);
	lenght = (unsigned int)(lenght / 1000);
	if ((res = FMOD_System_PlaySound(sys, snd, NULL, 0, NULL)) != FMOD_OK)
		exit_error(res);
	wait(lenght);
	FMOD_Sound_Release(snd);
}