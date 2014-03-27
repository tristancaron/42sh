/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbuiltin_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/26 12:33:57 by tcaron            #+#    #+#             */
/*   Updated: 2014/03/26 12:33:57 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"

void		ft_init_builtin(t_builtin_cmd *tab)
{
	tab[0].name = ft_strdup("exit");
	tab[0].handler = do_exit;
	tab[1].name = ft_strdup("cd");
	tab[1].handler = ft_cd;
	tab[2].name = ft_strdup("env");
	tab[2].handler = ft_env;
	tab[3].name = ft_strdup("setenv");
	tab[3].handler = set_env;
	tab[4].name = ft_strdup("unsetenv");
	tab[4].handler = unset_env;
	tab[5].name = ft_strdup("echo");
	tab[5].handler = ft_echo;
	tab[6].name = ft_strdup("read");
	tab[6].handler = ft_read;
	tab[7].name = ft_strdup("set");
	tab[7].handler = ft_set;
	tab[8].name = ft_strdup("unset");
	tab[8].handler = ft_unset;
	tab[9].name = NULL;
	tab[9].handler = NULL;
}

void		ft_free_builtin(t_builtin_cmd *tab)
{
	ft_free(tab[0].name);
	ft_free(tab[1].name);
	ft_free(tab[2].name);
	ft_free(tab[3].name);
	ft_free(tab[4].name);
	ft_free(tab[5].name);
	ft_free(tab[6].name);
	ft_free(tab[7].name);
	ft_free(tab[8].name);
}

void		ft_init_op_tab(int op[3])
{
	op[0] = -1;
	op[1] = -1;
	op[2] = -1;
}
