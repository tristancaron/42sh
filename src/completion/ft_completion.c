/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 13:58:59 by tcaron            #+#    #+#             */
/*   Updated: 2014/03/21 13:58:59 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <dirent.h>
#include <termcap.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../header.h"
#include "../libft.h"

static void		print(char *result)
{
	ft_putstr("\033[1;30;40m");
	ft_putstr(result);
	ft_putstr("\033[0m");
}

static void		ft_get_choice_2(int *check, char **result,
								DIR *d, char *to_find)
{
	struct dirent	*dir;

	while ((dir = readdir(d)))
	{
		if (ft_strncmp(dir->d_name, to_find, ft_strlen(to_find)) == 0)
		{
			if (!*check)
				*result = ft_strdup(dir->d_name + ft_strlen(to_find));
			(*check)++;
		}
	}
	closedir(d);
}

static void		ft_get_choice(char *to_find, char *path,
								char **input, char *result)
{
	DIR				*d;
	int				check;
	char			buf[10];

	check = 0;
	if ((d = opendir(path)) != NULL)
		ft_get_choice_2(&check, &result, d, to_find);
	if (check == 1)
		*input = ft_strdup(result);
	else if (check > 1)
	{
		print(result);
		if ((check = read(1, buf, 10)) && buf[0] == 0x09)
			*input = ft_strdup(result);
		else
		{
			buf[check] = '\0';
			*input = ft_strdup(buf);
		}
	}
	else
		*input = ft_strnew(1);
	if (check >= 1)
		ft_free(result);
	return ;
}

static void		ft_getdir_completion(char *to_find, char **input,
										int i, char **tmp)
{
	char	*path;

	while (--i > 0 && to_find[i] != '/')
		;
	if (i > 0)
		path = ft_strsub(to_find, 0, i);
	else
		path = ft_strnew(1);
	if (path[0] != '/' && path[0] != '~')
	{
		*tmp = path;
		path = ft_strjoin(ft_strdup("./"), path);
		ft_free(*tmp);
	}
	if (path[0] == '~')
	{
		*tmp = path;
		path = ft_strjoin(ft_strdup(ft_get_env("HOME=")), path + 1);
		ft_free(*tmp);
	}
	*tmp = ft_strdup(&to_find[i]);
	i = (*tmp[0] == '/') ? 1 : 0;
	ft_free(to_find);
	ft_get_choice(*tmp + i, path, input, NULL);
	ft_free(path);
}

void			ft_completion(char **input, t_input *final)
{
	int		i;
	int		j;
	char	*to_find;
	char	*tmp;

	i = final->cursor_pos;
	tmp = NULL;
	if (i != final->cursor_max)
		i--;
	j = --i;
	while (--i > 0 && final->result[i] != ' ')
		;
	i += (i == 0) ? 0 : 1;
	to_find = (char *)ft_malloc(sizeof(char) * (j - i + 1));
	ft_strncpy(to_find, &final->result[i], j - i + 1);
	ft_free(*input);
	ft_getdir_completion(to_find, input, ft_strlen(to_find), &tmp);
	ft_free(tmp);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_putchar_term);
	ft_prompt();
}
