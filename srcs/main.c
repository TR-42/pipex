/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:45:11 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/16 04:32:59 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/print_error.h"
#include "../headers/get_ch_proc_info_arr.h"
#include "../headers/child_process.h"
#include "../headers/is_argc_valid.h"
#include "../headers/print_help.h"

#include "../libft/ft_string/ft_string.h"
#include "../libft/gnl/get_next_line.h"
#include "../libft/ft_vect/ft_vect.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static const char	g_prompt_str[] = "> ";

static bool	is_same_line(const char *a, const char *b)
{
	if (a == NULL && b == NULL)
		return (true);
	else if (a == NULL || b == NULL)
		return (false);
	while (true)
	{
		if (*a != *b)
		{
			if ((*a == '\0' && *b == '\n') || (*a == '\n' && *b == '\0'))
				return (true);
			else
				return (false);
		}
		else if (*a == '\0')
			return (true);
		a++;
		b++;
	}
}

static void	set_here_doc_str_if_needed(t_ch_proc_info *proc_info)
{
	t_gnl_state	state;
	t_vect		str;
	char		*gnl_result;

	if (!is_here_doc_mode(proc_info->fname_in))
		return ;
	state = gen_gnl_state(STDIN_FILENO, 256);
	if (state.buf == NULL)
		perror_dispose_exit("gen_gnl_state", proc_info);
	str = vect_init(256, sizeof(char));
	if (str.p == NULL)
		perror_dispose_exit("heredoc/vect_init", proc_info);
	while (true)
	{
		write(STDOUT_FILENO, g_prompt_str, sizeof(g_prompt_str) - 1);
		gnl_result = get_next_line(&state);
		if (gnl_result == NULL || is_same_line(gnl_result, proc_info->arg_str))
			break ;
		vect_append_str(&str, gnl_result, ft_strlen(gnl_result));
		free(gnl_result);
	}
	free(gnl_result);
	dispose_gnl_state(&state);
	proc_info->arg_str = str.p;
}

static void	unlink_if_not_append(t_ch_proc_info *proc_info_arr)
{
	if (is_here_doc_mode(proc_info_arr[0].fname_in))
		return ;
	if (access(proc_info_arr[0].fname_out, F_OK) == 0
		&& unlink(proc_info_arr[0].fname_out) != 0)
		perror("unlink");
}

int	main(int argc, const char *argv[], char *const envp[])
{
	t_ch_proc_info	*proc_info_arr;
	int				status;
	int				i;

	if (!is_argc_valid(argc))
		print_help_exit();
	proc_info_arr = get_ch_proc_info_arr(argc, argv, envp);
	if (proc_info_arr == NULL)
		perror_exit("malloc for proc_info_arr");
	set_here_doc_str_if_needed(proc_info_arr);
	unlink_if_not_append(proc_info_arr);
	i = 0;
	while (i < (argc - 3))
		pipe_fork_exec(proc_info_arr, i++, (size_t)(argc - 3));
	i = 0;
	status = 0;
	while (i < (argc - 3))
		if (waitpid(proc_info_arr[i++].pid, &status, 0) < 0)
			perror("pipex/waitpid");
	dispose_proc_info_arr(proc_info_arr);
	if (WIFEXITED(status))
		return (EXIT_SUCCESS);
	else
		return (WEXITSTATUS(status));
}

#if DEBUG

__attribute__((destructor))
static void	destructor(void) {
	system("leaks -q pipex");
}

#endif
