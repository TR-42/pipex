/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:49:32 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/04 17:46:47 by kfujita          ###   ########.fr       */
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

void	perror_exit(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
