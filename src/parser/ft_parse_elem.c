/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_elem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:25:12 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:25:13 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header.h"
#include "../libft.h"

static t_parse		*ft_init_word(char *s)
{
	t_parse	*elem;

	elem = (t_parse *)ft_malloc(sizeof(t_parse));
	elem->word = ft_strdup(s);
	elem->next = NULL;
	return (elem);
}

t_parse				*ft_add_word(char *s, t_parse *final)
{
	t_parse	*elem;
	t_parse	*first;

	first = final;
	elem = ft_init_word(s);
	if (final)
	{
		while (final)
		{
			if (!final->next)
			{
				final->next = elem;
				return (first);
			}
			else
				final = final->next;
		}
	}
	return ((final = elem));
}
