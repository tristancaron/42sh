/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor_motion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:23:35 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:23:35 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include "../header.h"
#include "../libft.h"

void			ft_place_cursor(t_input *final)
{
	struct winsize	ws;
	int				part;
	int				modulo;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("ft_insert_char\n", 2);
	if (final->cursor_pos <= ws.ws_col - ft_prompt_len(0))
	{
		tputs(tgoto(tgetstr("ch", NULL), 0,
					final->cursor_pos + ft_prompt_len(0) - 1),
					1, ft_putchar_term);
	}
	else
	{
		part = (ws.ws_col - ft_prompt_len(0) - 1);
		modulo = (final->cursor_pos - 2) % part;
		part = modulo + ft_prompt_len(0) + 1;
		tputs(tgoto(tgetstr("ch", NULL), 0, part), 1, ft_putchar_term);
	}
}

static void		ft_rigth_motion(t_input *final)
{
	if (final->cursor_pos == final->cursor_max)
		return ;
	final->cursor_pos += 1;
	return ;
}

static void		ft_left_motion(t_input *final)
{
	if (final->cursor_pos == 1)
		return ;
	final->cursor_pos -= 1;
}

char			*ft_check_key_lr(t_input *final, int value)
{
	if (value == 1)
		ft_rigth_motion(final);
	else if (value == -1)
		ft_left_motion(final);
	return (final->result);
}
