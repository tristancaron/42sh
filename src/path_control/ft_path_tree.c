/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:26:00 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:26:00 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header.h"
#include "../libft.h"

static t_data	*ft_create_elem(char *cmd, char *path)
{
	t_data		*elem;

	elem = (t_data *)ft_malloc(sizeof(t_data));
	elem->cmd = ft_strdup(cmd);
	elem->path = ft_strdup(path);
	elem->right = NULL;
	return (elem);
}

static void		ft_add_elem_path(char *cmd, char *path, t_data *elem)
{
	while (elem->right)
		elem = elem->right;
	elem->right = ft_create_elem(cmd, path);
}

void			ft_init_tab(t_data **tab)
{
	int	i;

	i = 0;
	while (i < 4096)
	{
		tab[i] = NULL;
		i++;
	}
}

void			ft_set_node(char *cmd, char *path, t_data **tab)
{
	int			i;

	i = ft_hash(cmd);
	if (tab[i] == NULL)
		tab[i] = ft_create_elem(cmd, path);
	else
		ft_add_elem_path(cmd, path, tab[i]);
}
