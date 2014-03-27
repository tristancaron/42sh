/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:26:41 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:26:42 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#include "../libft.h"
#include <unistd.h>

int				ft_first_control_syntax(char *input)
{
	int		c;
	int		pipe;

	c = 0;
	pipe = 0;
	while (*input)
	{
		if (CHAR_S(*input) && !c)
			c = *input;
		else if (c && *input == c)
			c = 0;
		else if (*input == '|' || *input == '\\')
			pipe = 1;
		else if (pipe && *input != ' ')
			pipe = 0;
		input++;
	}
	return (c || pipe);
}

static char		*ft_second_controlbis(char *s, int i, int j, char *start)
{
	char	*end;

	while (s[i++])
	{
		if (s[i] == ';' && (j = i))
		{
			while (s[++j] && (s[j] == ' ' || s[j] == '\t'))
				;
			if (s[j] == '<' || s[j] == '>')
			{
				s[i + 1] = '\0';
				start = ft_strdup(s);
				end = ft_strdup(&s[j]);
				s[i + 1] = '!';
				ft_free(s);
				if (s[j] == '<')
					s = ft_strjoin(start, " more ");
				else
					s = ft_strjoin(start, " cat ");
				s = ft_strjoin(s, end);
				ft_free(end);
			}
		}
	}
	return (s);
}

char			*ft_second_control(char *s)
{
	char	*result;

	s = ft_second_controlbis(s, 0, 0, NULL);
	if (s[0] == '<')
	{
		result = ft_strjoin(ft_strdup("more "), s);
		ft_free(s);
		return (result);
	}
	if (s[0] == '>')
	{
		result = ft_strjoin(ft_strdup("cat "), s);
		ft_free(s);
		return (result);
	}
	return (s);
}
