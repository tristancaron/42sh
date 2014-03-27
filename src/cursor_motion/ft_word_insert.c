/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:23:53 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:23:53 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "../header.h"
#include "../libft.h"
#include <fcntl.h>

static char		*ft_insert_char(t_input *final, char *input)
{
	struct winsize	ws;
	char			*begin;
	char			*insert;
	char			*end;
	char			*result;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("ft_insert_char\n", 2);
	begin = ft_strdup(final->result);
	insert = input;
	end = ft_strdup(&final->result[final->cursor_pos - 1]);
	begin[final->cursor_pos - 1] = '\0';
	result = ft_strjoin(begin, insert);
	result = ft_strjoin(result, end);
	final->cursor_max += ft_strlen(input);
	final->cursor_pos += ft_strlen(input);
	return (result);
}

static char		*ft_delete_char(t_input *final)
{
	char	*tmp;

	tmp = ft_strdup(final->result);
	tmp[final->cursor_pos - 2] = '\0';
	tmp = ft_strjoin(tmp, final->result + final->cursor_pos - 1);
	ft_free(final->result);
	final->result = ft_strdup(tmp);
	ft_free(tmp);
	final->cursor_pos -= 1;
	final->cursor_max -= 1;
	return (final->result);
}

void			ft_print_line2(t_input *final, int col)
{
	int		part;
	int		start;
	int		division;

	part = (col - ft_prompt_len(0) - 1);
	division = (final->cursor_pos - 1) / part;
	division -= (division != ((final->cursor_pos - 2) / part)) ? 1 : 0;
	start = part * division;
	if (start + part > final->cursor_max)
		ft_putstr(final->result + start);
	else
		write(1, final->result + start, part);
	tputs(tgetstr("rc", NULL), 1, ft_putchar_term);
	ft_putstr("\033[2D<");
}

void			ft_print_line(t_input *final)
{
	struct winsize	ws;

	if (ioctl(0, TIOCGWINSZ, &ws) == -1)
		ft_putstr_fd("ft_insert_char\n", 2);
	if (final->cursor_pos + ft_prompt_len(0) <= ws.ws_col)
	{
		if (final->cursor_max + ft_prompt_len(0) <= ws.ws_col)
			ft_putstr(final->result);
		else
			write(1, final->result, ws.ws_col - ft_prompt_len(0) - 1);
		tputs(tgetstr("rc", NULL), 1, ft_putchar_term);
		ft_putstr("\033[2D>");
	}
	else
		ft_print_line2(final, ws.ws_col);
}

char			*print_word(t_input *final, char *input)
{
	int	len;

	tputs(tgetstr("vi", NULL), 1, ft_putchar_term);
	if (input && final->cursor_pos != final->cursor_max && input[0] != '\n'
		&& input[0] != 127 && input[0] != 8)
		final->result = ft_insert_char(final, input);
	else if (input && input[0] != '\n' && input[0] != 127 && input[0] != 8)
	{
		final->result = ft_strjoin(final->result, input);
		len = ft_strlen(input);
		final->cursor_max += (final->cursor_max == 0) ? len + 1 : len;
		final->cursor_pos = final->cursor_max;
	}
	else if (input && input[0] == 127 && final->cursor_pos > 1)
		final->result = ft_delete_char(final);
	tputs(tgetstr("rc", NULL), 1, ft_putchar_term);
	tputs(tgetstr("ce", NULL), 1, ft_putchar_term);
	ft_print_line(final);
	if (input && input[0] != '\n')
		ft_place_cursor(final);
	else
		ft_putstr("\n");
	tputs(tgetstr("ve", NULL), 1, ft_putchar_term);
	return (final->result);
}
