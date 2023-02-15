/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:26:17 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/16 04:30:22 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/print_error.h"
#include "../headers/child_process.h"
#include "../headers/get_ch_proc_info_arr.h"
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

const char	*g_errstr_no_cmd = "command not found: %s\n";

void	dispose_proc_info_arr(t_ch_proc_info *info_arr)
{
	size_t	i;

	if (info_arr == NULL)
		return ;
	if (is_here_doc_mode(info_arr[0].fname_in))
		free((void *)(info_arr[0].arg_str));
	i = 0;
	while (info_arr->path_arr[i] != NULL)
		free((void *)(info_arr->path_arr[i++]));
	free(info_arr->path_arr);
	free(info_arr);
}

static void	create_pipe(t_ch_proc_info *info_arr, size_t index, size_t count)
{
	int		pipefd[2];

	if ((index + 1) == count)
		return ;
	if (pipe(pipefd) < 0)
		perror_dispose_exit("Create Pipe", info_arr);
	info_arr[index].fd_from_this = pipefd[PIPEFD_FROM_THIS];
	info_arr[index + 1].fd_to_this = pipefd[PIPEFD_FROM_PREV];
}

// no return
void	pipe_fork_exec(t_ch_proc_info *info_arr, size_t index, size_t count)
{
	create_pipe(info_arr, index, count);
	info_arr[index].pid = fork();
	if (info_arr[index].pid < 0)
		perror_dispose_exit("fork", info_arr);
	else if (info_arr[index].pid == PID_FORKED)
	{
		if ((index + 1) == count)
			exec_command_last(info_arr, index);
		close(info_arr[index + 1].fd_to_this);
		if (index == 0)
			exec_command_first(info_arr, index);
		else
			exec_command(info_arr, index);
	}
	if ((index + 1) != count)
		close(info_arr[index].fd_from_this);
	if (index != 0)
		close(info_arr[index].fd_to_this);
}

static void	dup2_and_close(int fd_dup_from, int fd_dup_to)
{
	dup2(fd_dup_from, fd_dup_to);
	close(fd_dup_from);
}

// no return
void	exec_command(t_ch_proc_info *info_arr, size_t index)
{
	t_vect		cmd;
	char		*cmd_path;
	int			tmp;
	char *const	*envp;

	envp = (char *const *)(info_arr[index].envp);
	cmd = parse_cmd(info_arr[index].arg_str);
	tmp = chk_and_get_fpath(*(char **)(cmd.p), info_arr->path_arr, &cmd_path);
	if (tmp != CHK_GET_PATH_ERR_OK)
	{
		if (tmp == CHK_GET_PATH_ERR_NOCMD)
			ft_dprintf(STDERR_FILENO, g_errstr_no_cmd, *(char **)(cmd.p));
		else
			perror(*(char **)(cmd.p));
		dispose_proc_info_arr(info_arr);
		exit(EXIT_FAILURE);
	}
	dup2_and_close(info_arr[index].fd_to_this, STDIN_FILENO);
	dup2_and_close(info_arr[index].fd_from_this, STDOUT_FILENO);
	dispose_proc_info_arr(info_arr);
	execve(cmd_path, (char *const *)(cmd.p), envp);
	perror(cmd_path);
	free(cmd_path);
	vect_dispose_ptrarr(&cmd);
	exit(EXIT_FAILURE);
}
