/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 17:22:28 by erobert           #+#    #+#             */
/*   Updated: 2014/02/19 12:27:55 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../header.h"
#include "../libft.h"

static void		ft_launch_bis(int do_fork, t_seq *seq, char **environ)
{
	pid_t		father;
	char		*tmp;

	tmp = ft_strdup(seq->cmd);
	tmp = ft_strjoin(tmp, " ");
	tmp = ft_strjoin(tmp, seq->args);
	seq->exec_tab = ft_strsplit(tmp, ' ');
	ft_free(tmp);
	if (!do_fork)
	{
		execve(seq->path, seq->exec_tab, environ);
		_exit(0);
	}
	if ((father = fork()) == 0)
	{
		execve(seq->path, seq->exec_tab, environ);
		_exit(0);
	}
	else
		waitpid(0, NULL, 0);
}

void			ft_launch(int do_fork, t_seq *seq, char **environ)
{
	if (seq->cmd == NULL)
	{
		ft_putstr_fd("42sh: command not found or permission denied: ", 2);
		ft_putstr_fd(RED, 2);
		ft_putstr_fd(seq->file, 2);
		ft_putendl_fd(END, 2);
		return ;
	}
	if (ft_gotredirection(seq, seq->args))
	{
		ft_redirection(seq);
		return ;
	}
	if (seq->path == NULL)
	{
		seq->func(seq);
		return ;
	}
	ft_launch_bis(do_fork, seq, environ);
}
