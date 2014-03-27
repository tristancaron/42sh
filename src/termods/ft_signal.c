/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:26:51 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:26:51 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include "../header.h"
#include "../libft.h"

static void		sigint_handler(int sig)
{
	if (!(sig = 0))
		ft_putstr("\033[2D");
	return ;
}

static void		sigint_handler_faul(int sig)
{
	if (sig)
		ft_putstr_fd("Error", 2);
}

void			ft_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGSYS, sigint_handler_faul);
}
