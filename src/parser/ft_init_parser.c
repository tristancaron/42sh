/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 13:03:58 by tcaron            #+#    #+#             */
/*   Updated: 2014/03/26 13:03:58 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"

void		ft_init_op(char *token, int *i, char *op[9][3])
{
	*op[0] = ft_strdup("<");
	*op[1] = ft_strdup("<<");
	*op[2] = ft_strdup(">");
	*op[3] = ft_strdup(">>");
	*op[4] = ft_strdup("|");
	*op[5] = ft_strdup("||");
	*op[6] = ft_strdup("&");
	*op[7] = ft_strdup("&&");
	*op[8] = ft_strdup(";");
	*op[9] = NULL;
	*i = -1;
	while (++(*i) < 9 && ft_strncmp(token, *op[*i], 2) != 0)
		;
}

void		ft_free_op(char *op[9][3])
{
	ft_free(*op[0]);
	ft_free(*op[1]);
	ft_free(*op[2]);
	ft_free(*op[3]);
	ft_free(*op[4]);
	ft_free(*op[5]);
	ft_free(*op[6]);
	ft_free(*op[7]);
	ft_free(*op[8]);
}
