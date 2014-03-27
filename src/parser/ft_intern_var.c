/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intern_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdezier <hdezier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 12:51:33 by hdezier           #+#    #+#             */
/*   Updated: 2014/02/17 12:51:33 by hdezier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <stdlib.h>

static char		*ft_search_data_var(char *s)
{
	t_list	*tmp;

	if (!ft_add_data(NULL, NULL))
	{
		ft_free(s);
		return (ft_strdup(""));
	}
	tmp = ft_add_data(NULL, NULL)[ft_hash(s)];
	while (tmp && ft_strcmp(s, tmp->key))
		tmp = tmp->next;
	ft_free(s);
	if (tmp)
		return (tmp->data);
	else
		return (ft_strdup(""));
}

char			*ft_get_var(char *s)
{
	int		size;
	char	*result;

	size = 0;
	if (CHAR_END(*s))
		return (ft_strdup("$"));
	while (!CHAR_END(s[size]))
		size++;
	result = (char *)ft_malloc((size + 1) * sizeof(char));
	result[size] = '\0';
	while (--size >= 0)
		result[size] = s[size];
	return (ft_search_data_var(result));
}
