/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:48:17 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/11 23:54:52 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_ERROR_H
# define PRINT_ERROR_H

# include "child_process.h"

void	print_err_exit(const char *msg, const int exit_code);
void	perror_dispose_exit(const char *msg, t_ch_proc_info *info_arr);
void	perror_exit(const char *msg);

#endif
