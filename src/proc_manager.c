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
#include "nanoplayer.h"

void	write_pid()
{
	FILE	*f_nanoplayer;

	if ((f_nanoplayer = fopen("/tmp/nanoplayer", "w+")) == NULL)
		exit_file_error("fopen");
	fprintf(f_nanoplayer, "%d\n", (int)getpid());
	fclose(f_nanoplayer);
}

pid_t	get_pid()
{
	FILE	*f_nanoplayer;
	pid_t	pid = 0;
	int		c;

	if ((f_nanoplayer = fopen("/tmp/nanoplayer", "r")) == NULL)
		exit_file_error("fopen");
	while ((c = fgetc(f_nanoplayer)) != '\n' && c != EOF)
		pid = 10 * pid + (c - '0');
	if (c == EOF)
		exit_file_error("fgetc");
	fclose(f_nanoplayer);
	return (pid);
}

void	*sig_manager(void *arg)
{
	FILE			*f_nanoplayer;
	int				buf, i = -1;
	unsigned int	op;
	t_operation		**tab;

	(void)arg;
	if ((f_nanoplayer = fopen("/tmp/nanoplayer", "r")) == NULL)
		exit_file_error("fopen");
	if (!seek_char('\n', f_nanoplayer))
		exit_file_error("fgetc");
	buf = fgetc(f_nanoplayer);
	if (buf == EOF)
		exit_file_error("fgetc");
	fclose(f_nanoplayer);
	op = buf - '0';
	tab = init_tab_operations();
	while (++i != 8 && tab[i]->action != op);
	if (i != 8 && tab[i]->action == op)
		tab[i]->function();
	else
		exit(EXIT_FAILURE);
	free_tab_operations(&tab);
	pthread_exit(NULL);
}

void	sig_handler(int sig)
{
	pthread_t	*manager;
	
	(void)sig;
	if (!(manager = malloc(sizeof(pthread_t))))
		exit_memory_error();
	if (pthread_create(manager, NULL, sig_manager, NULL) == -1)
		exit_thread_error();
}

void	kill_handler(int sig)
{
	(void)sig;
	remove("/tmp/nanoplayer");
	exit(EXIT_FAILURE);
}

void	init_handler()
{
	t_sigaction *init, *kill;
	if (!(init = (t_sigaction*)malloc(sizeof(t_sigaction))))
		exit_memory_error();
	init->sa_handler = &sig_handler;
	init->sa_flags = 0;
	sigemptyset(&init->sa_mask);
	sigaction(SIGUSR1, init, NULL);
	
	if (!(kill = (t_sigaction*)malloc(sizeof(t_sigaction))))
		exit_memory_error();
	kill->sa_handler = &kill_handler;
	kill->sa_flags = 0;
	sigemptyset(&kill->sa_mask);
	sigaction(SIGKILL, kill, NULL);
}

void	send_operation(pid_t pid, char op, char *arg2)
{
	FILE	*f_nanoplayer;

	if ((f_nanoplayer = fopen("/tmp/nanoplayer", "r+")) == NULL)
		exit_file_error("fopen");
	if (!seek_char('\n', f_nanoplayer))
		exit_file_error("fgetc");
	fputc(op, f_nanoplayer);
	if (arg2 != NULL)
	{
		fputc('\n', f_nanoplayer);
		fputs(arg2, f_nanoplayer);
		fputc('\n', f_nanoplayer);
	}
	fclose(f_nanoplayer);
	kill(pid, SIGUSR1);
}