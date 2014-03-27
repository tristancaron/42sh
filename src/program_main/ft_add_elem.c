/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_elem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:26:10 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:26:11 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header.h"
#include "../libft.h"

void	ft_add_elem(t_cmd *line)
{
	t_cmd	*elem;

	elem = (t_cmd *)ft_malloc(sizeof(t_cmd));
	if (elem)
	{
		elem->origin = NULL;
		elem->id = ft_get_id(0);
		elem->next = NULL;
		elem->prev = line;
		line->next = elem;
	}
	return ;
}
