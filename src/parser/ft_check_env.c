/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 13:57:50 by tcaron            #+#    #+#             */
/*   Updated: 2014/03/27 13:57:51 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"

void	ft_lib_env(char **t1, t_seq *tmp, char **environ)
{
	ft_free_split(t1);
	ft_clean_seq(tmp);
	ft_free(environ);
}

void	ft_build_env(t_seq *seq)
{
	char	*tmp_args;
	char	**environ;
	char	**tab;
	t_seq	*tmp;
	int		index[2];

	tab = ft_strsplit(seq->args, ' ');
	index[0] = 0;
	while (ft_strstr(tab[index[0] + 1], "="))
		(index[0])++;
	if (index[0] > 0 && (index[1] = -1))
	{
		if ((environ = (char **)ft_malloc(sizeof(char *) * (index[0] + 1))))
		{
			while (++(index[1]) < index[0])
				environ[index[1]] = tab[index[1] + 1];
			environ[index[1]] = NULL;
		}
	}
	else
		environ = NULL;
	tmp_args = ft_strstr(seq->args, tab[index[0] + 1]);
	tmp = ft_lexer(tmp_args);
	ft_launch(1, tmp, environ);
	ft_lib_env(tab, tmp, environ);
}
