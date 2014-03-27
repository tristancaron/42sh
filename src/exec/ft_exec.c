/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:24:14 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/19 12:00:03 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../header.h"
#include "../libft.h"

static int	ft_cmd_null(t_seq *seq)
{
	ft_putstr_fd("42sh: command not found or permission denied: ", 2);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(seq->file, 2);
	ft_putendl_fd(END, 2);
	if (seq->extra && !ft_strcmp(seq->extra, "&&"))
		return (1);
	return (0);
}

void		ft_exec(t_seq *seq)
{
	ft_restore();
	while (seq && seq->next)
	{
		if (seq->extra && !ft_strcmp(seq->extra, "|"))
		{
			ft_pipe(seq);
			while (seq->extra && !ft_strcmp(seq->extra, "|"))
			{
				if (!seq || !seq->next)
					return ;
				seq = seq->next;
			}
		}
		else if (seq->cmd == NULL && ft_cmd_null(seq))
			return ;
		else if (seq->cmd != NULL)
		{
			ft_launch(1, seq, ft_cpy_env(0));
			if (seq->extra && !ft_strcmp(seq->extra, "||"))
				return ;
		}
		seq = seq->next;
	}
	ft_non_canonical();
}
