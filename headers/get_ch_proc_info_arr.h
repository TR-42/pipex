/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ch_proc_info_arr.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:24:58 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/08 00:25:34 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_CH_PROC_INFO_ARR_H
# define GET_CH_PROC_INFO_ARR_H

# include "child_process.h"

# include <stdbool.h>

# define FNAME_IN_INDEX (1)

bool			is_here_doc_mode(const char *fname_in);

t_ch_proc_info	*get_ch_proc_info_arr(
					int argc, const char *argv[], char *const envp[]);

#endif
