/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ch_proc_info_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:22:46 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/08 01:21:23 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/env_util.h"
#include "../headers/get_ch_proc_info_arr.h"

#include "../libft/ft_mem/ft_mem.h"
#include "../libft/ft_string/ft_string.h"
#include <stdio.h>

#define ARGV_INDEX_TOP (2)

t_ch_proc_info	*get_ch_proc_info_arr(
	int argc, const char *argv[], char *const envp[])
{
	t_ch_proc_info	*arr;
	int				argv_index;
	const char		**path_arr;

	arr = ft_calloc_nofill(argc - 3, sizeof(t_ch_proc_info));
	if (arr == NULL)
		return (NULL);
	path_arr = (const char **)get_path_in_env(envp);
	argv_index = ARGV_INDEX_TOP - 1;
	while (++argv_index < (argc - 1))
	{
		arr[argv_index - ARGV_INDEX_TOP].fname_in = argv[FNAME_IN_INDEX];
		arr[argv_index - ARGV_INDEX_TOP].fname_out = argv[argc - 1];
		arr[argv_index - ARGV_INDEX_TOP].arg_str = argv[argv_index];
		arr[argv_index - ARGV_INDEX_TOP].path_arr = path_arr;
		arr[argv_index - ARGV_INDEX_TOP].envp = (const char **)envp;
	}
	return (arr);
}
