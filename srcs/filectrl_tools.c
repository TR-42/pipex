/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filectrl_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:18:27 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/30 16:28:49 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_string/ft_string.h"
#include "../libft/ft_mem/ft_mem.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static char	*join_path(const char *path1, const char *path2)
{
	size_t	path1_len;
	size_t	path2_len;
	size_t	concat_slash;
	char	*ret;

	path1_len = ft_strlen(path1);
	path2_len = ft_strlen(path2);
	if (path1[path1_len - 1] == '/')
		concat_slash = 0;
	else
		concat_slash = 1;
	ret = malloc(path1_len + concat_slash + path2_len + 1);
	if (ret != NULL)
	{
		ft_memmove(ret, path1, path1_len);
		ft_memmove(ret + path1_len, "/", concat_slash);
		ft_memmove(ret + path1_len + concat_slash, path2, path2_len);
		ret[path1_len + concat_slash + path2_len] = '\0';
	}
	return (ret);
}

char	*chk_and_get_fullpath(const char *given_path, const char **env_path)
{
	char	*path;

	if (given_path == NULL || env_path == NULL || *given_path == '\0')
		return (NULL);
	if (given_path[0] == '/' || given_path[0] == '.')
		path = ft_strdup(given_path);
	else
	{
		while (*env_path != NULL)
		{
			path = join_path(*env_path, given_path);
			if (access(path, X_OK) == 0)
				return (path);
			free(path);
			path = NULL;
			env_path++;
		}
		return (NULL);
	}
	if (access(path, X_OK) == 0)
		return (path);
	perror(__func__);
	free(path);
	return (NULL);
}
