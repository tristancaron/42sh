/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:26:17 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:26:17 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <termcap.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "../header.h"
#include "../libft.h"

static char		*get_line(char *tmp, char *buffer, int check, int ret)
{
	tmp[ret] = '\0';
	if (check)
		buffer = ft_strjoin(buffer, tmp);
	else
		buffer = ft_strdup(tmp);
	ft_free(tmp);
	return (buffer);
}

char			*ft_read_input(char *buffer, int fd)
{
	int				ret;
	char			*tmp;
	static int		check = 0;

	tmp = (char *)ft_malloc((sizeof(char) * BUFF_SIZE + 1));
	ret = (int)read(fd, tmp, BUFF_SIZE);
	if (ret > 0)
		buffer = get_line(tmp, buffer, check, ret);
	else
		ft_free(tmp);
	if (ret == BUFF_SIZE)
	{
		check++;
		return (ft_read_input(buffer, fd));
	}
	else
	{
		check = 0;
		return (buffer);
	}
}

static char		*ft_get_input_2(t_cmd *line)
{
	t_input	final;
	char	*input;

	final.result = ft_strnew(1);
	final.save = ft_strnew(1);
	final.cursor_max = 1;
	final.cursor_pos = 1;
	input = NULL;
	while (1)
	{
		input = ft_read_input(input, 0);
		final.result = ft_check_key(&input, &final, line);
		if (input && input[0] == '\n')
			break ;
		if (ft_current_id(0) == ft_get_id(0))
		{
			ft_free(final.save);
			final.save = ft_strdup(final.result);
		}
		ft_free(input);
	}
	if (input && input[0] == '\n')
		ft_free(input);
	ft_free(final.save);
	return (final.result);
}

static int		ft_only_space(char *result)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(result);
	while (result[i] && result[i] == ' ')
		i++;
	if (i == len)
		return (1);
	else
		return (0);
}

char			*ft_get_input(t_cmd *line)
{
	char	*result;
	char	*next;

	result = ft_get_input_2(line);
	while ((result && result[0] == '\0') || ft_only_space(result))
	{
		ft_prompt();
		ft_free(result);
		result = ft_get_input_2(line);
	}
	while (ft_first_control_syntax(result) != 0)
	{
		ft_putstr("> ");
		tputs(tgetstr("sc", NULL), 1, ft_putchar_term);
		ft_prompt_len(2);
		next = ft_get_input_2(line);
		if (result[ft_strlen(result) - 1] == '\\')
			result[ft_strlen(result) - 1] = '\0';
		result = ft_strjoin(result, next);
		ft_free(next);
	}
	return (result);
}
