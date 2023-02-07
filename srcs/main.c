/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:45:11 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/04 23:15:17 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/print_error.h"
#include "../headers/get_ch_proc_info_arr.h"
#include "../headers/child_process.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, const char *argv[], char *const envp[])
{
	t_ch_proc_info	*proc_info_arr;
	int				status;
	size_t			i;
	size_t			proc_info_arr_len;
	bool			exit_with_fail;

	if (argc < REQUIRED_ARGC)
		print_err_exit(ERR_HELP_MSG, ERR_HELP_EXITNUM);
	proc_info_arr = get_ch_proc_info_arr(argc, argv, envp);
	if (proc_info_arr == NULL)
		perror_exit("malloc for proc_info_arr");
	proc_info_arr_len = argc - 3;
	i = 0;
	while (i < proc_info_arr_len)
		pipe_fork_exec(proc_info_arr, i++, proc_info_arr_len);
	i = 0;
	while (i < proc_info_arr_len)
	{
		waitpid(proc_info_arr[i++].pid, &status, 0);
		exit_with_fail = (exit_with_fail || WIFSIGNALED(status)
				|| (WIFEXITED(status) && WEXITSTATUS(status) != 0));
	}
	return (exit_with_fail & 0x01);
}
