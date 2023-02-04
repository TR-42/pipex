/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ch_proc_info_arr.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:22:46 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/04 19:32:38 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/env_util.h"
#include "../headers/get_ch_proc_info_arr.h"

#include "../libft/ft_mem/ft_mem.h"
#include "../libft/ft_string/ft_string.h"

t_ch_proc_info	*get_ch_proc_info_arr(
	int argc, const char *argv[], char *const envp[])
{
	t_ch_proc_info	*arr;
	int				f_in_index;
	int				argv_index;
	bool			is_here_doc;
	const char		**path_arr;

	f_in_index = 1;
	is_here_doc = is_here_doc_mode(argv[f_in_index]);
	if (is_here_doc)
		f_in_index += 1;
	arr = ft_calloc_nofill(argc - f_in_index - 2, sizeof(t_ch_proc_info));
	if (arr == NULL)
		return (NULL);
	path_arr = (const char **)get_path_in_env(envp);
	argv_index = f_in_index;
	while (++argv_index < (argc - 1))
	{
		arr[argv_index - f_in_index - 1].is_here_doc = is_here_doc;
		arr[argv_index - f_in_index - 1].fname_in = argv[f_in_index];
		arr[argv_index - f_in_index - 1].fname_out = argv[argc - 1];
		arr[argv_index - f_in_index - 1].arg_str = argv[argv_index];
		arr[argv_index - f_in_index - 1].path_arr = path_arr;
		arr[argv_index - f_in_index - 1].envp = (const char **)envp;
	}
	return (arr);
}
