/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdezier <hdezier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 12:05:18 by hdezier           #+#    #+#             */
/*   Updated: 2014/02/18 12:05:18 by hdezier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <stdlib.h>

static void		free_list(t_list *l)
{
	free(l->key);
	free(l->data);
	free(l);
}

void			ft_set(t_seq *seq)
{
	t_list	**list;
	t_list	*tmp;
	int		i;

	i = 0;
	while (!CHAR_END(seq->args[i]))
		i++;
	if (seq->args[i] || !(list = ft_add_data(NULL, NULL)))
		return ;
	i = -1;
	while (++i < HASH_SIZE)
	{
		tmp = list[i];
		while (tmp)
		{
			ft_putstr(tmp->key);
			ft_putchar('=');
			ft_putstr(tmp->data);
			ft_putchar('\n');
			tmp = tmp->next;
		}
	}
}

static void		ft_remove_list(char *s)
{
	t_list	**list;
	t_list	*tmp;
	t_list	*current;

	if (!(list = ft_add_data(NULL, NULL)))
		return ;
	current = list[ft_hash(s)];
	tmp = NULL;
	while (current)
	{
		if (!ft_strcmp(s, current->key))
		{
			current = current->next;
			free_list(tmp->next);
			if (tmp)
				tmp->next = current;
			else
				list[ft_hash(s)] = current;
			ft_free(&s);
			return ;
		}
		tmp = current;
		current = tmp->next;
	}
	ft_free(&s);
}

void			ft_unset(t_seq *seq)
{
	int		size;
	char	*result;

	size = 0;
	if (CHAR_END(seq->args[0]))
		ft_putstr_fd("unset: not enough arguments", 2);
	else
	{
		while (!CHAR_END(seq->args[size]))
			size++;
		result = (char *)ft_malloc((size + 1) * sizeof(char));
		result[size] = '\0';
		while (--size >= 0)
			result[size] = seq->args[size];
		ft_remove_list(result);
	}
}
