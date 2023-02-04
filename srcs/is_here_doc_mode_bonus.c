/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_here_doc_mode_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:27:16 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/04 19:28:36 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/get_ch_proc_info_arr.h"
#include "../libft/ft_string/ft_string.h"

#include <limits.h>

bool	is_here_doc_mode(const char *fname_in)
{
	return (ft_strncmp(fname_in, "here_doc", SIZE_T_MAX) == 0);
}
