/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_first_last.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:00:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/08 23:36:43 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/child_process.h"
#include "../headers/get_ch_proc_info_arr.h"
#include "../headers/print_error.h"

#include "../libft/ft_math/ft_math.h"
#include "../libft/ft_string/ft_string.h"

// - open
// - O_RDONLY / O_WRONLY / O_CLOEXEC
#include <fcntl.h>

// - exit
// - EXIT_SUCCESS
#include <stdlib.h>

// - INT32_MAX
#include <stdint.h>

// - write
// - size_t / ssize_t
#include <unistd.h>

// no return
static void	write_heredoc(t_ch_proc_info *info_arr, size_t index)
{
	size_t	str_len;
	ssize_t	written_len;
	char	*str;

	str = (char *)info_arr[index].arg_str;
	str_len = ft_strlen(str);
	while (0 < str_len)
	{
		written_len = write(info_arr[index].fd_from_this,
				str, ft_minp(INT32_MAX, str_len));
		if (written_len <= 0)
			perror_exit("write heredoc text");
		str_len -= (size_t)written_len;
		str += written_len;
	}
	close(info_arr[index].fd_from_this);
	free((void *)info_arr[index].arg_str);
	free((void *)info_arr[index].path_arr);
	free(info_arr);
	exit(EXIT_SUCCESS);
}

// no return
void	exec_command_first(t_ch_proc_info *info_arr, size_t index)
{
	if (!is_here_doc_mode(info_arr[index].fname_in))
	{
		info_arr[index].fd_to_this
			= open(info_arr[index].fname_in, O_RDONLY | O_CLOEXEC);
		exec_command(info_arr, index);
	}
	else
		write_heredoc(info_arr, index);
}

// no return
void	exec_command_last(t_ch_proc_info *info_arr, size_t index)
{
	int	oflag;

	oflag = O_WRONLY | O_CREAT | O_CLOEXEC;
	if (is_here_doc_mode(info_arr[index].fname_in))
		oflag = oflag | O_APPEND;
	info_arr[index].fd_from_this = open(info_arr[index].fname_out, oflag, 0644);
	if (index == 0)
		exec_command_first(info_arr, index);
	else
		exec_command(info_arr, index);
}
