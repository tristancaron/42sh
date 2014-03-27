/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:22:36 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:22:36 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

void		unset_env(t_seq *seq)
{
	int		i;
	char	**environ;

	i = 0;
	environ = ft_cpy_env(0);
	while (environ[i])
	{
		if (ft_strncmp(environ[i], seq->args, ft_strlen(seq->args)) == 0)
		{
			ft_strclr(environ[i]);
			environ[i] = environ[i + 1];
			i++;
			while (environ[i])
			{
				environ[i] = environ[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	return ;
}

void		set_env(t_seq *seq)
{
	int		i;
	int		check;
	char	**environ;

	i = 0;
	check = 0;
	environ = ft_cpy_env(0);
	while (seq->args[i])
	{
		if (seq->args[i] == '=')
			check++;
		i++;
	}
	if (check)
	{
		while (environ[i])
			i++;
		environ[i] = seq->args;
		environ[i + 1] = 0;
	}
	return ;
}

void		ft_env(t_seq *seq)
{
	char	**environ;
	int		i;

	if (ft_strncmp(seq->args, "-i", 2) == 0)
	{
		ft_build_env(seq);
		return ;
	}
	i = 0;
	environ = ft_cpy_env(0);
	while (environ[i])
	{
		ft_putstr(environ[i]);
		ft_putstr("\n");
		i++;
	}
}

void		do_exit(t_seq *seq)
{
	if (seq != NULL)
	{
		ft_restore();
		ft_cleaner(NULL, NULL, 1);
		_exit(0);
	}
	else
	{
		ft_restore();
		_exit(0);
	}
}

t_handler	ft_isfunc(char *cmd)
{
	int				i;
	t_builtin_cmd	builtins[10];

	i = 0;
	ft_init_builtin(builtins);
	while (builtins[i].name != NULL)
	{
		if (ft_strcmp(cmd, builtins[i].name) == 0)
		{
			ft_free_builtin(builtins);
			return (builtins[i].handler);
		}
		i++;
	}
	ft_free_builtin(builtins);
	return (NULL);
}
