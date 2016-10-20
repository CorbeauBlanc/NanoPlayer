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

#define _POSIX_SOURCE
#include <sys/stat.h>
#include "nanoplayer.h"

char	get_operation(char c)
{
	char	tab[2][7] = {{'u','p','n','b','s','o','v'},
						{'0','1','2','3','4','5','6'}};
	int		i = -1;
	
	while(tab[0][++i] != c);
	return (tab[1][i]);
}

int		main(int argc, char **argv)
{
	struct	stat file_stats;
	char	op;

	if (argc < 2)
	{
		fprintf(stderr, "NanoPlayer : Not enough arguments");
		exit(EXIT_FAILURE);
	}
	if (argv[1][0] == '-')
	{
		op = get_operation(argv[1][1]);
		send_operation(get_pid(), op, argc > 2 ? argv[2] : NULL);
	}
	else
	{
		if (stat(argv[1], &file_stats) < 0)
		exit_file_error("stat");
		if (S_ISREG(file_stats.st_mode))
		{
			write_pid();
			init_handler();
			FMOD_SYSTEM *system = create_system();
			FMOD_SOUND *sound = create_sound(argv[1], system);

			play_sound(sound, system);

			FMOD_System_Close(system);
			FMOD_System_Release(system);
		}
		remove("/tmp/nanoplayer");
	}
	exit(EXIT_SUCCESS);
}

