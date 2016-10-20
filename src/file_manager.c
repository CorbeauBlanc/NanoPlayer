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