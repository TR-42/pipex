/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:26:17 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/05 21:36:49 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/print_error.h"
#include "../headers/child_process.h"
#include "../headers/parse_cmd.h"
#include "../headers/filectrl_tools.h"
#include "../libft/ft_printf/ft_printf.h"

// - perror
#include <stdio.h>

// - pipe
// - fork
// - pid_t
// - dup2
// - execve
#include <unistd.h>

// - exit
#include <stdlib.h>

// - close
#include <fcntl.h>

#define PID_FORKED (0)

// no return
void	pipe_fork_exec(t_ch_proc_info *info_arr, size_t index, size_t count)
{
	int		pipefd[2];

	if ((index + 1) != count)
	{
		if (pipe(pipefd) < 0)
			perror_exit("Create Pipe");
		info_arr[index].fd_from_this = pipefd[PIPEFD_FROM_THIS];
		info_arr[index + 1].fd_to_this = pipefd[PIPEFD_FROM_PREV];
	}
	info_arr[index].pid = fork();
	if (info_arr[index].pid < 0)
		perror_exit("fork");
	else if (info_arr[index].pid == PID_FORKED)
	{
		if ((index + 1) == count)
			exec_command_last(info_arr, index);
		close(pipefd[PIPEFD_FROM_PREV]);
		if (index == 0)
			exec_command_first(info_arr, index);
		else
			exec_command(info_arr, index);
	}
	else if ((index + 1) != count)
		close(pipefd[PIPEFD_FROM_THIS]);
}

// no return
void	exec_command(t_ch_proc_info *info_arr, size_t index)
{
	t_vect		cmd;
	char		*cmd_path;
	char *const	*argv;
	const char	**envp;

	envp = info_arr[index].envp;
	cmd = parse_cmd(info_arr[index].arg_str);
	argv = (char *const *)cmd.p;
	cmd_path = chk_and_get_fullpath(*argv, info_arr[index].path_arr);
	free(info_arr[index].path_arr);
	if (cmd_path == NULL)
	{
		ft_dprintf(STDERR_FILENO,
			"command not found: %s\n", *argv);
		exit(EXIT_FAILURE);
	}
	dup2(info_arr[index].fd_to_this, STDIN_FILENO);
	close(info_arr[index].fd_to_this);
	dup2(info_arr[index].fd_from_this, STDOUT_FILENO);
	close(info_arr[index].fd_from_this);
	free(info_arr);
	execve(cmd_path, argv, (char *const *)envp);
	perror(cmd_path);
	vect_dispose_ptrarr(&cmd);
	exit(EXIT_FAILURE);
}
