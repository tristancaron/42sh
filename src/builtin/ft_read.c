/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdezier <hdezier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 15:58:19 by hdezier           #+#    #+#             */
/*   Updated: 2014/02/17 15:58:20 by hdezier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <stdlib.h>
#include <unistd.h>

static void		ft_init_list(char *key, char *data, t_list **tab, int n)
{
	t_list	*result;
	t_list	*tmp;

	result = (t_list *)ft_malloc(sizeof(t_list));
	result->data = data;
	result->key = key;
	tmp = tab[n];
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->key))
		{
			tmp->data = data;
			return ;
		}
		tmp = tmp->next;
	}
	result->next = tab[n];
	tab[n] = result;
}

static void		ft_init_tab_list(t_list ***tab)
{
	int	i;

	i = -1;
	(*tab) = (t_list **)ft_malloc(4096 * sizeof(t_list *));
	while (++i < 4096)
		(*tab)[i] = NULL;
}

t_list			**ft_add_data(char *s, int *op)
{
	static t_list	**tab = NULL;
	char			buf[2];
	char			*result;

	buf[0] = 0;
	if (!s)
		return (tab);
	if (!tab)
		ft_init_tab_list(&tab);
	result = ft_strnew(1);
	while (42)
	{
		read(0, buf, 1);
		if ((op[0] > 0 && buf[0] == op[0]) || (!op[2])
			|| (op[0] < 0 && op[2] < 0 && buf[0] == '\n'))
			break ;
		ft_putchar(buf[0]);
		result = ft_strjoin(result, buf);
		(op[2])--;
	}
	ft_init_list(s, result, tab, ft_hash(s));
	ft_putchar('\n');
	if (op[1] > 0)
		ft_putendl(result);
	return (NULL);
}

static void		ft_read_arg(char *s, int *op)
{
	int		size;
	char	*result;

	size = 0;
	if (op[0] > 0 || op[2] > 0)
	{
		while (*s == ' ')
			s++;
		if (op[0] > 0)
			op[0] = *s;
		if (op[2] > 0)
			op[2] = ft_atoi(s);
		while (*s != ' ' && *s)
			s++;
	}
	while (*s == ' ')
		s++;
	while (!CHAR_END(s[size]))
		size++;
	result = (char *)ft_malloc((size + 1) * sizeof(char));
	result[size] = '\0';
	while (--size >= 0)
		result[size] = s[size];
	ft_add_data(result, op);
}

void			ft_read(t_seq *seq)
{
	int	op[3];
	int	i;

	i = 0;
	ft_init_op_tab(op);
	if (CHAR_END(seq->args[0]))
		ft_add_data("REPLY", op);
	else
	{
		if (seq->args[0] == '-' && seq->args[1])
		{
			i++;
			while (!CHAR_END(seq->args[i]))
			{
				if (seq->args[i] == 'd')
					op[0] = 1;
				else if (seq->args[i] == 'E')
					op[1] = 1;
				else if (seq->args[i] == 'n')
					op[2] = 1;
				i++;
			}
		}
		ft_read_arg(seq->args + i, op);
	}
}
