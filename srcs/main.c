/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:45:11 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/04 19:39:04 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/print_error.h"
#include "../headers/get_ch_proc_info_arr.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, const char *argv[], char *const envp[])
{
	t_ch_proc_info	*proc_info_arr;
	t_ch_proc_info	v;
	size_t			i;
	size_t			proc_info_arr_len;

	if (argc < REQUIRED_ARGC)
		print_err_exit(ERR_HELP_MSG, ERR_HELP_EXITNUM);
	proc_info_arr = get_ch_proc_info_arr(argc, argv, envp);
	i = 0;
	while (i < (size_t)argc)
	{
		printf("argv[%zu]: '%s'\n", i, argv[i]);
		i++;
	}
	i = 0;
	printf("~~~~~~~~~~~~~~~~\n");
	if (proc_info_arr == NULL)
	{
		printf("ERR!: `proc_info_arr` is NULL!\n");
		return (EXIT_FAILURE);
	}
	proc_info_arr_len = argc - 3;
	if (proc_info_arr[0].is_here_doc)
		proc_info_arr_len -= 1;
	i = 0;
	while (i < proc_info_arr_len)
	{
		v = proc_info_arr[i];
		printf("arr[%zu]:\t is_here_doc:%d, fname_in:'%s', fname_out:'%s', arg_str:'%s'\n", i, v.is_here_doc, v.fname_in, v.fname_out, v.arg_str);
		i++;
	}
}
