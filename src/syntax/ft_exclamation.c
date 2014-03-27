/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exclamation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 14:25:21 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/28 14:25:22 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <unistd.h>

static char		*ft_get_exclamationbis(t_cmd *tmp, t_cmd *line, int i, int j)
{
	char	*start;
	char	*end;
	char	*result;

	if (tmp)
	{
		line->origin[i - 1] = '\0';
		start = ft_strdup(line->origin);
		end = ft_strdup(&line->origin[j + 1]);
		line->origin[i - 1] = '!';
		ft_free(line->origin);
		result = ft_strjoin(start, tmp->origin);
		result = ft_strjoin(result, end);
		ft_free(end);
		ft_putendl(result);
	}
	else
	{
		ft_putstr_fd("42sh: event not found: ", 2);
		ft_putstr_fd(BLUE, 2);
		write(2, &line->origin[i], j - i + 1);
		ft_putendl_fd(END, 2);
		return (NULL);
	}
	return (result);
}

char			*ft_get_exclamation(t_cmd *line)
{
	int		i;
	int		j;
	t_cmd	*tmp;

	i = 0;
	while (line->origin[i] && line->origin[i] != '!')
		i++;
	if (i == (int)ft_strlen(line->origin))
		return (line->origin);
	tmp = line->prev;
	i++;
	j = i;
	while (line->origin[++j] != '\0' && line->origin[j] != ' '
			&& line->origin[j] != ';' && line->origin[j] != '<'
			&& line->origin[j] != '>' && line->origin[j] != '|')
		;
	j--;
	while (ft_strncmp(&line->origin[i], tmp->origin, j - i + 1) != 0)
	{
		tmp = tmp->prev;
		if (!tmp)
			break ;
	}
	return (ft_get_exclamationbis(tmp, line, i, j));
}
