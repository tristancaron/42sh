/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:24:57 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/19 11:58:09 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <stdlib.h>

static t_seq	*ft_is_extra(char **tab, t_seq *seq)
{
	if (tab[0][0] == ';' || tab[0][0] == '|' || tab[0][0] == '&')
		seq->extra = ft_strdup(tab[0]);
	ft_free(tab[0]);
	tab++;
	if (tab[0])
		return (ft_recursive_lexer(tab, seq));
	else
		return (seq);
}

static t_seq	*ft_is_args(char **tab, t_seq *seq)
{
	int	count;

	count = -1;
	while (tab[0] && tab[0][0] != ';' && tab[0][0] != '|' && tab[0][0] != '&')
	{
		if (++count)
			seq->args = ft_strjoin(seq->args, " ");
		seq->args = ft_strjoin(seq->args, tab[0]);
		ft_free(tab[0]);
		tab++;
	}
	if (tab[0])
		return (ft_is_extra(tab, seq));
	else
		return (seq);
}

static t_seq	*ft_is_cmd(char **tab, t_seq *seq)
{
	if (!ft_check_cmd(seq, tab))
	{
		seq->file = ft_strdup(tab[0]);
		while (*tab && *tab[0] != ';' && *tab[0] != '|' && *tab[0] != '&')
		{
			ft_free(tab[0]);
			tab++;
		}
		if (!tab[0])
			return (seq);
		else if (tab[0][0] == ';' || tab[0][0] == '|' || tab[0][0] == '&')
			return (ft_is_extra(tab, seq));
		else
			return (ft_recursive_lexer(tab, seq));
	}
	else
	{
		seq->cmd = ft_strdup(tab[0]);
		ft_free(tab[0]);
		tab++;
		if (tab[0])
			return (ft_is_args(tab, seq));
		else
			return (seq);
	}
}

t_seq			*ft_recursive_lexer(char **tab, t_seq *seq)
{
	if (!tab[0])
		return (seq);
	while (seq->next)
		seq = seq->next;
	seq->next = ft_init_seq();
	seq->next->prev = seq;
	return (ft_is_cmd(tab, seq));
}

t_seq			*ft_lexer(char *s)
{
	char	**tab;
	t_seq	*seq;

	tab = ft_strsplit(s, ' ');
	seq = ft_init_seq();
	ft_recursive_lexer(tab, seq);
	ft_free(tab);
	return (seq);
}
