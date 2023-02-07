/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_first_last.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:00:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/04 19:14:08 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/child_process.h"
#include "../headers/get_ch_proc_info_arr.h"

// - open
// - O_RDONLY / O_WRONLY / O_CLOEXEC
#include <fcntl.h>

// no return
// here_docでは、forkで別プロセスを作成し、そこでgnlをかける
void	exec_command_first(t_ch_proc_info *info_arr, size_t index)
{
	info_arr[index].fd_to_this = open(info_arr->fname_in, O_RDONLY | O_CLOEXEC);
	exec_command(info_arr, index);
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
