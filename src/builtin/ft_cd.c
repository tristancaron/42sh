/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:22:17 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:22:17 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../header.h"
#include "../libft.h"

static void		ft_change_path(void)
{
	char	**env;
	char	*buf;
	int		i;
	int		j;

	i = -1;
	j = -1;
	env = ft_cpy_env(0);
	while (ft_strncmp(env[++i], "OLDPWD=", 7) != 0)
		;
	while (ft_strncmp(env[++j], "PWD=\0", 4) != 0)
		;
	if (env[i] && env[j])
		ft_strcpy(env[i] + 7, env[j] + 4);
	if (env[j])
	{
		buf = getcwd(NULL, 0);
		ft_strcpy(env[j] + 4, buf);
		ft_free(buf);
	}
}

static void		ft_case_bis(t_seq *seq)
{
	char	*tmp;
	char	*tmp2;

	if (seq->args && seq->args[0] == '~')
	{
		tmp = ft_get_env("HOME=");
		tmp2 = ft_strjoin(ft_strdup("/"), seq->args + 1);
		if (tmp)
		{
			ft_free(seq->args);
			seq->args = ft_strjoin(ft_strdup(tmp), tmp2);
			ft_free(tmp2);
		}
	}
}

static void		ft_case(t_seq *seq)
{
	char	*tmp;

	if (seq->args[0] == '\0')
	{
		tmp = ft_get_env("HOME=");
		if (tmp)
		{
			ft_free(seq->args);
			seq->args = ft_strdup(tmp);
		}
	}
	if (seq->args && seq->args[0] == '~')
		ft_case_bis(seq);
	if (seq->args && seq->args[0] == '-' && !seq->args[1])
	{
		tmp = ft_get_env("OLDPWD=");
		if (tmp)
		{
			ft_free(seq->args);
			seq->args = ft_strdup(tmp);
		}
	}
}

void			ft_cd(t_seq *seq)
{
	ft_case(seq);
	if (chdir(seq->args) == -1)
	{
		ft_putstr_fd("cd: no such directory or permission denied: ", 2);
		ft_putstr_fd(YELLOW, 2);
		ft_putstr_fd(seq->args, 2);
		ft_putendl_fd(END, 2);
	}
	else
		ft_change_path();
}
