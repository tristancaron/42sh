/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 15:18:01 by tcaron            #+#    #+#             */
/*   Updated: 2014/03/21 15:18:01 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <glob.h>
#include <stdio.h>

static void		get_glob(char **s)
{
	glob_t	globbuf;
	int		i;

	glob(*s, GLOB_TILDE, NULL, &globbuf);
	ft_free(*s);
	*s = ft_strdup(globbuf.gl_pathv[0]);
	ft_free(globbuf.gl_pathv[0]);
	i = 0;
	while (globbuf.gl_pathv[++i])
	{
		*s = ft_strjoin(*s, " ");
		*s = ft_strjoin(*s, globbuf.gl_pathv[i]);
		ft_free(globbuf.gl_pathv[i]);
	}
	ft_free(globbuf.gl_pathv);
}

void			check_glob(char **buffer)
{
	int		i;
	char	**split;

	i = -1;
	split = ft_strsplit(*buffer, ' ');
	while (split[++i])
	{
		if (ft_strstr(split[i], "*") || ft_strstr(split[i], "?"))
			get_glob(&split[i]);
	}
	i = 0;
	ft_free(*buffer);
	*buffer = ft_strdup(split[0]);
	ft_free(split[0]);
	while (split[++i])
	{
		*buffer = ft_strjoin(*buffer, " ");
		*buffer = ft_strjoin(*buffer, split[i]);
		ft_free(split[i]);
	}
	ft_free(split);
	return ;
}
