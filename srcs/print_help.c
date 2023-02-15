/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:31:21 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/16 01:49:14 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/print_help.h"

// - exit
// - EXIT_FAILURE
#include <stdlib.h>

// - write
// - STDERR_FILENO
#include <unistd.h>

static const char	g_help_str[] = "./pipex file1 cmd1 cmd2 file2\n";
static const char	g_equivalent1[]
	= "Equivalent:\n\t$ < file1 cmd1 | cmd2 > file2\n";

void	print_help_exit(void)
{
	write(STDERR_FILENO, g_help_str, sizeof(g_help_str) - 1);
	write(STDERR_FILENO, g_equivalent1, sizeof(g_equivalent1) - 1);
	exit(EXIT_FAILURE);
}
