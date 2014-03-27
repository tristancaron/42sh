/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gotredirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erobert <erobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/15 14:12:06 by erobert           #+#    #+#             */
/*   Updated: 2014/02/18 16:29:07 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "../header.h"
#include "../libft.h"

static void	ft_open_infile(t_seq *cmd, char *str, int two)
{
	if (cmd->fd[0] > 0)
		close(cmd->fd[0]);
	if (two)
	{
		cmd->two[0] = 1;
		cmd->fd[0] = 1;
		cmd->file = ft_strjoin(str, "\n");
	}
	else
	{
		cmd->two[0] = 0;
		cmd->fd[0] = open(str, O_RDONLY);
	}
}

static void	ft_open_outfile(t_seq *cmd, char *str, int two)
{
	if (cmd->fd[1] > 0)
		close(cmd->fd[1]);
	if (two)
	{
		cmd->two[1] = 1;
		cmd->fd[1] = open(str, O_CREAT | O_APPEND | O_WRONLY, 0664);
	}
	else
	{
		cmd->two[1] = 0;
		cmd->fd[1] = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	}
}

static void	ft_open_redirection(char c, t_seq *cmd, char *str, int two)
{
	char	**tab;

	tab = ft_strsplit(str, ' ');
	if (c == '<')
		ft_open_infile(cmd, tab[0], two);
	else
		ft_open_outfile(cmd, tab[0], two);
	while (*str == ' ' || *str == '\t')
		str++;
	while (*str && *str != ' ' && *str != '\t' && *str != '<' && *str != '>')
	{
		*str = ' ';
		str++;
	}
	ft_free_split(tab);
}

static int	ft_getfd(char c, t_seq *cmd, char *str)
{
	while (*str)
	{
		if (*str == c)
		{
			*str = ' ';
			if (*++str == c)
			{
				*str = ' ';
				ft_open_redirection(c, cmd, ++str, 1);
			}
			else
				ft_open_redirection(c, cmd, str, 0);
		}
		str++;
	}
	if (cmd->fd[0] || cmd->fd[1])
		return (1);
	return (0);
}

int			ft_gotredirection(t_seq *cmd, char *str)
{
	cmd->fd[0] = 0;
	cmd->two[0] = 0;
	cmd->fd[1] = 0;
	cmd->two[1] = 0;
	return (ft_getfd('<', cmd, str) + ft_getfd('>', cmd, str));
}
