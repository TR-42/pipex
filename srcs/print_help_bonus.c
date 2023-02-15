/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 01:31:21 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/16 01:49:20 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/print_help.h"

// - exit
// - EXIT_FAILURE
#include <stdlib.h>

// - write
// - STDERR_FILENO
#include <unistd.h>

static const char	g_help_str_bonus[]
	= "./pipex [here_doc DELIMITER | file1] cmd1 cmd2 [cmd3 ...] file2\n";
static const char	g_equivalent1_bonus[]
	= "Equivalent:\n\t$ < file1 cmd1 | cmd2 [| cmd3 ...] > file2\n";
static const char	g_equivalent2_bonus[]
	= "\t$ << DELIMITER cmd1 | cmd2 [| cmd3 ...] >> file2\n";

void	print_help_exit(void)
{
	write(STDERR_FILENO, g_help_str_bonus, sizeof(g_help_str_bonus) - 1);
	write(STDERR_FILENO, g_equivalent1_bonus, sizeof(g_equivalent1_bonus) - 1);
	write(STDERR_FILENO, g_equivalent2_bonus, sizeof(g_equivalent2_bonus) - 1);
	exit(EXIT_FAILURE);
}
