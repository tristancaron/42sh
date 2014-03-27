/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 17:25:09 by erobert           #+#    #+#             */
/*   Updated: 2014/02/18 17:49:25 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../header.h"
#include "../libft.h"

static void	ft_father(int *pfd_1, t_seq *seq)
{
	pid_t	father;
	int		pfd_2[2];

	close(pfd_1[1]);
	dup2(pfd_1[0], 0);
	close(pfd_1[0]);
	if (seq->extra == NULL || seq->extra[0] == ';')
	{
		ft_launch(0, seq, ft_cpy_env(0));
		_exit(0);
	}
	if (pipe(pfd_2) == -1)
		return ;
	father = fork();
	if (!father)
	{
		close(pfd_2[0]);
		dup2(pfd_2[1], 1);
		close(pfd_2[1]);
		ft_free(seq->extra);
		ft_launch(0, seq, ft_cpy_env(0));
		_exit(0);
	}
	else
		ft_father(pfd_2, seq->next);
}

void		ft_pipe(t_seq *seq)
{
	pid_t	father;
	int		pfd[2];

	father = fork();
	if (father)
		wait(0);
	else
	{
		if (pipe(pfd) == -1)
			return ;
		father = fork();
		if (!father)
		{
			close(pfd[0]);
			dup2(pfd[1], 1);
			close(pfd[1]);
			ft_free(seq->extra);
			ft_launch(0, seq, ft_cpy_env(0));
			_exit(0);
		}
		else
			ft_father(pfd, seq->next);
	}
}
