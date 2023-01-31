/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:45:11 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/31 15:21:00 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/print_error.h"
#include "../headers/filectrl_tools.h"
#include "../headers/env_util.h"
#include "../libft/ft_vect/ft_vect.h"
#include "../headers/parse_cmd.h"

#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

static void	free_ptr_arr(void **ptr_arr);

int	main(int argc, const char *argv[], char *const envp[])
{
	int			pipefd[2];
	const char	**path_arr;
	t_vect		cmd1;
	char		*cmd1_path;
	t_vect		cmd2;
	char		*cmd2_path;
	pid_t		pid1;
	pid_t		pid2;
	int			fd;

	if (argc < REQUIRED_ARGC)
		print_err_exit(ERR_HELP_MSG, ERR_HELP_EXITNUM);
	path_arr = (const char **)get_path_in_env(envp);
	cmd1 = parse_cmd(argv[2]);
	cmd1_path = chk_and_get_fullpath(*(const char **)(cmd1.p), path_arr);
	cmd2 = parse_cmd(argv[3]);
	cmd2_path = chk_and_get_fullpath(*(const char **)(cmd2.p), path_arr);
	if (cmd1_path == NULL)
	{
		if (path_arr == NULL)
			print_err_exit("env `PATH` not found", 1);
		else
			print_err_exit("file1 not found", 1);
	}
	if (cmd2_path == NULL)
	{
		if (path_arr == NULL)
			print_err_exit("env `PATH` not found", 1);
		else
			print_err_exit("file2 not found", 1);
	}
	free_ptr_arr((void **)path_arr);
	pipe(pipefd);
	pid1 = fork();
	if (pid1 < 0)
	{
		perror("fork 1");
		exit(-1);
	}
	else if (pid1 == PID_FORKED)
	{
		close(pipefd[PIPEFD_IN]);
		fd = open(argv[1], O_RDONLY | O_CLOEXEC);
		dup2(fd, STDIN_FILENO);
		close(fd);
		dup2(pipefd[PIPEFD_OUT], STDOUT_FILENO);
		close(pipefd[PIPEFD_OUT]);
		execve(cmd1_path, (char *const *)cmd1.p, envp);
		perror(cmd1_path);
		return (-1);
	}
	pid2 = fork();
	if (pid2 < 0)
	{
		perror("fork 2");
		exit(-1);
	}
	else if (pid2 == PID_FORKED)
	{
		close(pipefd[PIPEFD_OUT]);
		dup2(pipefd[PIPEFD_IN], STDIN_FILENO);
		close(pipefd[PIPEFD_IN]);
		fd = open(argv[4], O_WRONLY | O_CREAT | O_CLOEXEC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execve(cmd2_path, (char *const *)cmd2.p, envp);
		perror(cmd2_path);
		return (-1);
	}
	close(pipefd[PIPEFD_IN]);
	close(pipefd[PIPEFD_OUT]);
	waitpid(pid1, &fd, 0);
	waitpid(pid2, &fd, 0);
}

static void	free_ptr_arr(void **ptr_arr)
{
	size_t	i;

	i = 0;
	while (ptr_arr[i] != NULL)
		free(ptr_arr[i++]);
	free(ptr_arr);
}
