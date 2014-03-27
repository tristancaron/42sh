/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_escp_seq.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:23:03 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:23:03 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "../header.h"
#include "../libft.h"

static char		*ft_cacheofcpy(char *s, t_input *final)
{
	static char	*buffer = NULL;

	if (s && final->cursor_pos != final->cursor_max)
	{
		ft_free(buffer);
		buffer = ft_strdup(&s[final->cursor_pos - 1]);
		return (NULL);
	}
	else if (buffer)
		return (buffer);
	return (final->result);
}

static char		*ft_do_paste(t_input *final)
{
	char	*begin;
	char	*insert;
	char	*end;
	char	*result;

	begin = ft_strdup(final->result);
	insert = ft_cacheofcpy(NULL, final);
	end = ft_strdup(&final->result[final->cursor_pos - 1]);
	begin[final->cursor_pos - 1] = '\0';
	result = ft_strjoin(begin, insert);
	result = ft_strjoin(result, end);
	final->cursor_max += ft_strlen(insert);
	return (result);
}

char			*ft_ccp_seq(t_input *final)
{
	int		ret;
	char	input[5];
	char	*tmp;

	ret = (int)read(0, input, 1);
	if (ret == -1)
		ft_putstr_fd("Error with read in ft_ccp_seq", 2);
	if (input[0] == 'x' || input[0] == 'X')
	{
		ft_cacheofcpy(final->result, final);
		tmp = ft_strdup(final->result);
		tmp[final->cursor_pos - 1] = '\0';
		final->cursor_max = (int)ft_strlen(tmp) + 1;
		final->cursor_pos = final->cursor_pos;
		return (tmp);
	}
	else if (input[0] == 'c' || input[0] == 'C')
	{
		ft_cacheofcpy(final->result, final);
		return (final->result);
	}
	else if (input[0] == 'v' || input[0] == 'V')
		return (ft_do_paste(final));
	else
		return (final->result);
}
