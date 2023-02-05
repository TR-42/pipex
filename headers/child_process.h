/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 12:28:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/04 23:02:02 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHILD_PROCESS_H
# define CHILD_PROCESS_H

# include "../libft/ft_vect/ft_vect.h"

// - pid_t
# include <unistd.h>

# define PIPEFD_FROM_THIS (1)
# define PIPEFD_TO_THIS (0)
# define PIPEFD_FROM_PREV (PIPEFD_TO_THIS)
# define PIPEFD_TO_NEXT (PIPEFD_FROM_THIS)

typedef struct s_ch_proc_info
{
	bool			is_here_doc;
	const char		*fname_in;
	const char		*fname_out;
	int				fd_to_this;
	int				fd_from_this;
	pid_t			pid;
	const char		**path_arr;
	const char		*arg_str;
	const char		**envp;
}	t_ch_proc_info;

void	pipe_fork_exec(t_ch_proc_info *info_arr, size_t index, size_t count);
void	exec_command(t_ch_proc_info *info_arr, size_t index);
void	exec_command_first(t_ch_proc_info *info_arr, size_t index);
void	exec_command_last(t_ch_proc_info *info_arr, size_t index);

#endif
