/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 13:40:23 by erobert           #+#    #+#             */
/*   Updated: 2014/02/18 17:49:54 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../header.h"
#include "../libft.h"

static void	ft_twoin(t_seq *cmd, int *pfd)
{
	char	buf[1024];
	char	*str;
	int		i;

	str = malloc(sizeof(*str) * 1);
	str[0] = '\0';
	while (1)
	{
		write(2, "> ", 2);
		i = read(0, buf, 1023);
		buf[i] = '\0';
		if (ft_strcmp(buf, cmd->file))
			str = ft_strjoin(str, buf);
		else
		{
			ft_putstr_fd(str, pfd[1]);
			return ;
		}
	}
}

static void	ft_redirin(t_seq *cmd)
{
	int		pfd[2];

	if (cmd->two[0])
	{
		if (pipe(pfd) == -1)
			return ;
		ft_twoin(cmd, pfd);
		dup2(pfd[0], 0);
		close(pfd[0]);
		close(pfd[1]);
	}
	else
	{
		dup2(cmd->fd[0], 0);
		close(cmd->fd[0]);
	}
}

void		ft_redirection(t_seq *cmd)
{
	pid_t	father;

	father = fork();
	if (father > 0)
		wait(0);
	else if (!father)
	{
		if (cmd->fd[0])
			ft_redirin(cmd);
		if (cmd->fd[1])
		{
			dup2(cmd->fd[1], 1);
			close(cmd->fd[1]);
		}
		ft_launch(0, cmd, ft_cpy_env(0));
		_exit(0);
	}
}
