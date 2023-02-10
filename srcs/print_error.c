/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:49:32 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/10 15:00:54 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/print_error.h"
#include "../libft/ft_string/ft_string.h"

// - perror
#include <stdio.h>

// - exit
#include <stdlib.h>

// - write
#include <unistd.h>

void	print_err_exit(const char *msg, const int exit_code)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(exit_code);
}

void	perror_dispose_exit(const char *msg, t_ch_proc_info *info_arr)
{
	perror(msg);
	dispose_proc_info_arr(info_arr);
	exit(EXIT_FAILURE);
}

void	perror_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
