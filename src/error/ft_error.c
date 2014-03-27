/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:24:04 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:24:04 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header.h"
#include "../libft.h"

void	ft_error_malloc(void *value, char *msg)
{
	if (!value)
	{
		ft_putstr_fd("Error with malloc in ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
		do_exit(NULL);
		_exit(0);
	}
	return ;
}
