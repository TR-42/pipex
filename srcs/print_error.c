/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:49:32 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/28 07:12:09 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/print_error.h"
#include "../libft/ft_string/ft_string.h"

#include <stdlib.h>
#include <unistd.h>

void	print_err_exit(const char *msg, const int exit_code)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(exit_code);
}
