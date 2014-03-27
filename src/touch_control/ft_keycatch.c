/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keycatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:27:12 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:27:12 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"

int		ft_key_up_or_down(char *buf)
{
	if (buf)
	{
		if (buf[0] == 0x1B && buf[1] == 0x5B && buf[2] == 0x41 && !buf[3])
		{
			ft_current_id(-1);
			return (1);
		}
		else if (buf[0] == 0x1B && buf[1] == 0x5B && buf[2] == 0x42 && !buf[3])
		{
			ft_current_id(1);
			return (1);
		}
	}
	return (0);
}

int		ft_key_left_or_rigth(char *buf)
{
	if (buf)
	{
		if (buf[0] == 0x1B && buf[1] == 0x5B && buf[2] == 0x44 && !buf[3])
			return (-1);
		else if (buf[0] == 0x1B && buf[1] == 0x5B && buf[2] == 0x43 && !buf[3])
			return (1);
	}
	return (0);
}
