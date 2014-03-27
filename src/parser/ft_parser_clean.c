/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_clean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:25:23 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/19 11:55:54 by erobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../header.h"
#include "../libft.h"

static t_parse	*ft_token(t_parse *final, char *token, int *inc, int i)
{
	char	*op[9][3];

	ft_init_op(token, &i, op);
	if (i < 9)
	{
		final = ft_add_word(*op[i], final);
		(*inc)++;
	}
	else
	{
		i = -1;
		while (++i < 9 && ft_strncmp(token, *op[i], 1) != 0)
			;
		if (i < 9)
			final = ft_add_word(*op[i], final);
		else if (*token == '$')
		{
			final = ft_add_word(ft_get_var(token + 1 + *inc), final);
			while (!CHAR_END(token[*inc]))
				(*inc)++;
		}
	}
	ft_free_op(op);
	return (final);
}

static char		*ft_past_word(t_parse *final)
{
	char	*final_s;
	t_parse	*tmp;

	final_s = ft_strdup(final->word);
	ft_free(final->word);
	final_s = ft_strjoin(final_s, " \0");
	tmp = final;
	final = final->next;
	ft_free(tmp);
	while (final && final->word)
	{
		final_s = ft_strjoin(final_s, final->word);
		ft_free(final->word);
		final_s = ft_strjoin(final_s, " \0");
		tmp = final;
		final = final->next;
		ft_free(tmp);
	}
	if (final && final->next)
		ft_free(final->next);
	ft_free(final);
	return (final_s);
}

static t_parse	*ft_find_op(int j, int *i, char *buffer, t_parse *final)
{
	char	*tmp;

	if (j)
	{
		tmp = ft_strsub(buffer, *i - j, j);
		final = ft_add_word(tmp, final);
		ft_free(tmp);
	}
	if (!buffer[*i])
		return (final);
	return (ft_token(final, &buffer[*i], i, -1));
}

static t_parse	*ft_split_buffer(char *buffer, t_parse *final)
{
	int	i;
	int	j;

	i = 0;
	if (!buffer)
		return (final);
	while (buffer[i])
	{
		j = 0;
		while (buffer[i] && OP(buffer[i]))
		{
			j++;
			i++;
		}
		final = ft_find_op(j, &i, buffer, final);
		if (buffer[i])
			i++;
	}
	return (final);
}

char			*ft_parse_clean(char *buffer)
{
	char	*new_buff;
	t_parse	*final;

	final = NULL;
	final = ft_split_buffer(buffer, final);
	new_buff = ft_past_word(final);
	check_glob(&new_buff);
	return (new_buff);
}
