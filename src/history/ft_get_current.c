/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_current.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:24:42 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:24:42 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header.h"
#include "../libft.h"

/*
** more = -1 | current - 1;
** more =  1 | current + 1;
** more =  0 | return current;
** more =  2 | set current to last id;
*/

int		ft_current_id(int more)
{
	static int	current = 0;

	if (more == 1)
		current += ((current + 1) <= ft_get_id(0)) ? 1 : 0;
	else if (more == -1)
		current -= ((current - 1) >= 0) ? 1 : 0;
	else if (more == 2)
		current = ft_get_id(0);
	return (current);
}

char	*ft_get_current_line(t_cmd *line)
{
	int	current;

	current = ft_current_id(0);
	while (line && line->id != current)
		line = line->prev;
	return (line->origin);
}

char	*ft_get_env(char *s)
{
	char	**environ;
	int		i;

	i = -1;
	environ = ft_cpy_env(0);
	if (!s)
		return (NULL);
	while (ft_strncmp(environ[++i], s, ft_strlen(s)) != 0)
		;
	if (environ[i])
		return (environ[i] + ft_strlen(s));
	else
		return (NULL);
}
