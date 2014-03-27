/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 14:58:25 by tcaron            #+#    #+#             */
/*   Updated: 2014/03/21 14:58:25 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft.h"
#include "../header.h"

void	test_free(char **var)
{
	if (*var != NULL)
		free(*var);
	*var = NULL;
}

void	*ft_malloc(int s)
{
	void	*result;

	result = NULL;
	result = malloc(s);
	if (!result)
	{
		ft_putstr_fd("Error with memory allocation\n", 2);
		return (NULL);
	}
	else
		return (result);
}

void	ft_free(void *var)
{
	if (var != NULL)
		free(var);
	var = NULL;
	return ;
}

void	ft_free_data_hash(t_data **var)
{
	int		i;
	t_data	*tmp;

	i = -1;
	while (++i < 4096 && var)
	{
		if (var[i])
		{
			ft_free(var[i]->cmd);
			ft_free(var[i]->path);
			tmp = var[i];
			while (var[i]->right)
			{
				var[i] = var[i]->right;
				ft_free(tmp);
				tmp = var[i];
				ft_free(var[i]->cmd);
				ft_free(var[i]->path);
			}
		}
		ft_free(var[i]);
	}
	ft_free(var);
	return ;
}

void	ft_free_split(char **var)
{
	int		i;

	i = 0;
	if (var == NULL)
		return ;
	while (var[i + 1])
	{
		ft_free(var[i]);
		i++;
	}
	ft_free(var);
	return ;
}
