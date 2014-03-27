/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 15:09:37 by tcaron            #+#    #+#             */
/*   Updated: 2014/03/21 15:09:37 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"

int		ft_key1(char *input, t_input *final, t_cmd *line)
{
	int	value;

	if (ft_key_up_or_down(input))
	{
		ft_check_key_ud(final, line);
		ft_strclr(input);
		return (1);
	}
	else if ((value = ft_key_left_or_rigth(input)))
	{
		ft_check_key_lr(final, value);
		ft_strclr(input);
		return (1);
	}
	return (0);
}
