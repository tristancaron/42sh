/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_termods.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:26:55 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:26:55 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include "../libft.h"
#include "../header.h"

struct termios		*ft_oldline(struct termios *line, int value)
{
	static struct termios	*oldline = NULL;

	if (oldline == NULL)
	{
		oldline = line;
		return (line);
	}
	if (value)
	{
		ft_free(oldline);
		oldline = NULL;
	}
	return (oldline);
}

int					ft_putchar_term(int c)
{
	int		fd_term;

	fd_term = 1;
	if (fd_term)
	{
		write(fd_term, &c, (unsigned long)1);
		return (c);
	}
	else
	{
		ft_restore();
		_exit(0);
	}
	return (c);
}

int					ft_restore(void)
{
	struct termios	*oldline;

	oldline = NULL;
	oldline = ft_oldline(oldline, 0);
	if (tcsetattr(0, TCSANOW, oldline) < 0)
		ft_putstr_fd("Error with ft_restore\n", 2);
	return (1);
}

int					ft_non_canonical(void)
{
	struct termios	line;
	struct termios	*oldline;

	oldline = NULL;
	if (!(oldline = ft_oldline(oldline, 0)))
		oldline = (struct termios *)malloc(sizeof(line));
	if (!oldline)
		ft_putstr_fd("Error in ft_non_canonical\n", 2);
	if (tcgetattr(0, oldline) < 0)
		ft_putstr_fd("Error with ft_canonical_mode\n", 2);
	oldline = ft_oldline(oldline, 0);
	ft_memmove(&line, oldline, sizeof(line));
	line.c_lflag &= ~(unsigned long)(ICANON | ECHO);
	line.c_cc[VMIN] = 1;
	line.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &line) < 0)
		ft_putstr_fd("Error with ft_canonical_mode (2)\n", 2);
	return (1);
}
