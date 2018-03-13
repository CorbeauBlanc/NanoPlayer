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


#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#ifndef __APPLE__
//# define _POSIX_SOURCE
# define _GNU_SOURCE
#endif

#include "nanoplayer.h"

typedef struct	dirent	t_dirent;

int		seek_char(char c, FILE *stream)
{
	int		i = 0;
	char	buf;
	while((buf = fgetc(stream)) != c && buf != EOF)
		i++;
	return (i);
}

char	*get_line(FILE *stream)
{
	char	*line;
	char	buf;
	int		i = -1;

	if (!(line = (char*)malloc(1)))
		exit_memory_error();
	while ((buf = fgetc(stream)) != '\n' && buf != EOF)
	{
		line[++i] = buf;
		if (!(line = realloc(line, i + 2)))
			exit_memory_error();
	}
	line[i + 1] = '\0';
	return (line);
}

int		exist(char *path)
{
	struct	stat file_stats;

	return (stat(path, &file_stats) == 0);
}

int		is_file(char *path)
{
	struct	stat file_stats;

	if (stat(path, &file_stats) < 0)
		exit_file_error("stat");
	return (S_ISREG(file_stats.st_mode));
}

int		is_dir(char *path)
{
	struct	stat file_stats;

	if (stat(path, &file_stats) < 0)
		exit_file_error("stat");
	return (S_ISDIR(file_stats.st_mode));
}

int		file_selector(const t_dirent *entry)
{
	return (entry->d_type == DT_REG);
}

void	free_list_entries(t_dirent ***list, int nb)
{
	int i = -1;

	while (++i < nb)
		free((*list)[i]);
	free(*list);
}

void	free_list_path(char ***list)
{
	char	**tmp = *list;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(*list);
}

char	**get_dir_content(char *path)
{
	t_dirent	**list_entries;
	char		**list_path;
	int			nbr_entries, i, len;

	nbr_entries = scandir(path, &list_entries, file_selector, alphasort);
	if (nbr_entries < 0)
		exit_file_error("scandir");
	if (!(list_path = (char**)malloc((nbr_entries + 1) * sizeof(char*))))
		exit_memory_error();
	i = -1;
	while(++i < nbr_entries)
	{
		len = strlen(path) + strlen(list_entries[i]->d_name);
		if (!(list_path[i] = (char*)malloc(len + 2)))
			exit_memory_error();
		strncpy(list_path[i], path, len);
		if (path[strlen(path) - 1] != '/')
			list_path[i][strlen(path)] = '/';
		strncat(list_path[i], list_entries[i]->d_name, len);
	}
	list_path[i] = NULL;
	free_list_entries(&list_entries, nbr_entries);
	return (list_path);
}
