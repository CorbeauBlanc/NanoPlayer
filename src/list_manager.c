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

static char	*strndup(const char *s1, long len)
{
	long	i;
	char	*str;

	if (!s1)
		return (NULL);
	if (!(str = (char*)malloc(len + 1)))
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}


void		insert_cell(t_list **head, char *path)
{
	t_list	*cell;
	
	if (!(cell = (t_list*)malloc(sizeof(t_list))))
		exit_memory_error();
	cell->path = strndup(path, strlen(path));
	if (head && !*head)
	{
		cell->next = NULL;
		cell->prev = NULL;
		*head = cell;
	}
	else if (head)
	{
		cell->next = (*head)->next;
		(*head)->next = cell;
		cell->prev = (*head);
		if (cell->next)
			cell->next->prev = cell;
	}
}

void		delete_cell(t_list **cell)
{
	if (cell && *cell)
	{
		if ((*cell)->prev)
			(*cell)->prev->next = (*cell)->next;
		if ((*cell)->next)
			(*cell)->next->prev = (*cell)->prev;
		free(*cell);
		*cell = NULL;
	}
}

void		clear_list(t_list **head)
{
	t_list	**tmp;
	
	while (*head)
	{
		tmp = head;
		*head = (*head)->next;
		delete_cell(tmp);
	}
}

t_list	*create_list(char **tab)
{
	int		i = -1;
	t_list	*head = NULL;
	t_list	**tmp = &head;
	
	while (tab && tab[++i])
	{
		insert_cell(tmp, tab[i]);
		if ((*tmp)->next)
			tmp = &((*tmp)->next);
	}
	return (head);
}