/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 06:42:05 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/31 14:05:29 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/env_util.h"
#include "../libft/ft_string/ft_string.h"

#include <stdbool.h>
#include <stddef.h>

static const char	*is_this_requested_env(char *const envp, const char *name);

const char	*get_env_value(char *const envp[], const char *name)
{
	const char	*p_value;

	p_value = NULL;
	if (envp == NULL || name == NULL)
		return (NULL);
	while (*envp != NULL && p_value == NULL)
	{
		p_value = is_this_requested_env(*envp, name);
		envp++;
	}
	return (p_value);
}

static const char	*is_this_requested_env(char *envp, const char *name)
{
	if (envp == NULL)
		return (NULL);
	while (*envp != '=')
	{
		if (*envp == '\0' || *envp != *name)
			return (NULL);
		envp++;
		name++;
	}
	if (*name == '\0')
		return (envp + 1);
	else
		return (NULL);
}

char	**get_path_in_env(char *const envp[])
{
	const char	*path;

	path = get_env_value(envp, "PATH");
	if (path == NULL)
		return (NULL);
	return (ft_split(path, ':'));
}
