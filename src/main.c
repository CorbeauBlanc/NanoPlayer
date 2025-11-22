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

t_stopcond	stop;
t_timemutex time_count;
t_chanmutex	channel;
t_threads	threads;

static char	get_operation(char *c)
{
	char	tab_char[2][8] = {{'u','p','n','b','s','o','v', 'h'}, {'0','1','2','3','4','5','6', 0}};
	char	*tab_str[2][8] = {{"play","pause","next","previous","stop","open","volume", "help"}, {"0","1","2","3","4","5","6", ""}};
	char	ret;
	int		i = -1;

	if (*c == '-')
	{
		while(++i < 7 && strcmp(tab_str[0][i], c + 1));
		ret = i < 7 ? *tab_str[1][i] : 0;
	}
	else
	{
		while(++i < 7 && tab_char[0][i] != *c);
		ret = i < 7 ? tab_char[1][i] : 0;
	}
	return (ret);
}

void		create_new_instance(char *path)
{
	t_list	*list = NULL;

	if (is_dir(path))
		list = create_list(get_dir_content(path));
	else if (is_file(path))
		insert_cell(&list, path);
	else
		exit(EXIT_FAILURE);
	if (!list)
	{
		fprintf(stderr,
			"NanoPlayer : The directory is empty or the file is corrupted");
		remove("/tmp/nanoplayer");
		exit(EXIT_FAILURE);
	}
	init_handler();
	write_pid();
	read_list(list);
}

int			main(int argc, char **argv)
{
	char	op;

	if (argc < 2)
		exit_arguments_error();
	if (argv[1][0] == '-')
	{
		if (!(op = get_operation(argv[1] + 1)))
			exit_usage_error();
		send_operation(get_pid(), op, argc > 2 ? argv[2] : NULL);
	}
	else
	{
		threads.size = 0;
		if (exist("/tmp/nanoplayer"))
		{
			fprintf(stderr, "Error : an instance is already running\n");
			fprintf(stderr, "Use -o|--open <path> to open a new file or directory\n");
			exit(EXIT_FAILURE);
		}
		create_new_instance(argv[1]);
		wait_threads();
		remove("/tmp/nanoplayer");
	}

	exit(EXIT_SUCCESS);
}
