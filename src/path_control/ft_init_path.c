/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcaron <tcaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 16:25:48 by tcaron            #+#    #+#             */
/*   Updated: 2014/02/09 16:25:48 by tcaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <termcap.h>
#include <termios.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../header.h"
#include "../libft.h"

int				ft_hash(char *key)
{
	unsigned long	hash;
	int				i;

	hash = 5381;
	i = 0;
	while (key[i])
	{
		hash = ((hash << 5) + hash) + key[i];
		i++;
	}
	return (hash % HASH_SIZE);
}

t_data			**ft_save_path_data(t_data **tab)
{
	static t_data	**save = NULL;
	static char		*path = NULL;
	static int		count = 0;
	char			*tmp;

	if (tab)
	{
		save = tab;
		path = ft_get_env("PATH=");
		ft_cleaner(tab, NULL, 0);
	}
	else if ((tmp = ft_get_env("PATH=")) == NULL
			|| ft_strcmp(path, ft_get_env("PATH=")) != 0)
	{
		if (!count)
			count++;
		else if (!(count = 0))
			return (NULL);
		ft_free_data_hash(save);
		save = NULL;
		ft_init_path();
	}
	return (save);
}

static void		ft_init_tab_path(char **final, int i, char *f_path)
{
	t_data			**tab;
	DIR				*d;
	struct dirent	*dir;

	tab = (t_data **)ft_malloc(sizeof(t_data *) * 4096);
	ft_init_tab(tab);
	while (final[++i] != NULL)
	{
		d = opendir(final[i]);
		if (d)
		{
			while ((dir = readdir(d)))
			{
				f_path = ft_strjoin(ft_strdup(final[i]), "/");
				f_path = ft_strjoin(f_path, dir->d_name);
				ft_set_node(dir->d_name, f_path, tab);
				ft_free(f_path);
			}
			closedir(d);
		}
		ft_free(final[i]);
	}
	ft_free(final);
	ft_save_path_data(tab);
	return ;
}

char			*ft_cmdpath(char *cmd)
{
	t_data		*start;
	t_data		**tab;
	struct stat	file;

	tab = ft_save_path_data(NULL);
	if (!tab)
		return (NULL);
	start = tab[ft_hash(cmd)];
	while (start)
	{
		if (ft_strcmp(cmd, start->cmd) == 0)
			return (start->path);
		start = start->right;
	}
	stat(cmd, &file);
	if (access(cmd, X_OK) == 0 && !S_ISDIR(file.st_mode))
		return (ft_strdup(cmd));
	return (NULL);
}

void			ft_init_path(void)
{
	char	*path;
	char	**final;

	path = ft_get_env("PATH=");
	if (path)
	{
		final = ft_strsplit(path, ':');
		ft_init_tab_path(final, -1, NULL);
	}
	return ;
}
