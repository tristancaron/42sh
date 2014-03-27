/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/10 16:29:03 by tcaron            #+#    #+#             */
/*   Updated: 2014/03/10 16:29:03 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <termcap.h>
#include <termios.h>

static void		ft_echo_escape_char(char c)
{
	if (c == 'n')
		ft_putchar('\n');
	else if (c == 'r')
		tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar_term);
	else if (c == 't')
		ft_putstr("\t");
	else if (c == 'v')
		ft_putchar('\v');
	else if (c == 'b')
		ft_putchar('\b');
	else if (c == 'a')
		ft_putchar('\a');
	else if (c == '0')
		ft_putchar('\0');
	else if (c == '"')
		ft_putchar('"');
	else if (c == '$')
		ft_putchar('$');
	else if (c == '\\')
		ft_putchar('\\');
	else
	{
		ft_putchar('\\');
		ft_putchar(c);
	}
}

static void		ft_echo_display(char *s, int op_e)
{
	char	c;

	c = 0;
	while (*s)
	{
		if (CHAR_S(*s) && !c)
		{
			c = *s;
			s++;
		}
		if (*s == '\\' && !op_e)
		{
			s++;
			ft_echo_escape_char(*s);
		}
		else if (*s != c)
			ft_putchar((*s));
		if (*s == c)
			c = 0;
		s++;
	}
}

void			ft_echo(t_seq *seq)
{
	int	op_e;
	int	op_n;
	int	i;

	op_e = 0;
	op_n = 0;
	if (!(i = 0) && seq->args[0] == '-' && seq->args[1])
	{
		while (seq->args[i] != ' ' && seq->args[i])
		{
			if (seq->args[i] == 'E')
				op_e = 1;
			else if (seq->args[i] == 'e')
				op_e = 0;
			else if (seq->args[i] == 'n')
				op_n = 1;
			i++;
		}
	}
	while (seq->args[i] == ' ')
		i++;
	ft_echo_display(&(seq->args[i]), op_e);
	if (!op_n)
		ft_putchar('\n');
}
