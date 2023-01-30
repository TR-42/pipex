/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:45:11 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/30 13:58:35 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/print_error.h"
#include "../headers/env_util.h"
#include "../libft/ft_printf/ft_printf.h"
#include <stddef.h>

int	main(int argc, const char *argv[], const char *envp[])
{
	if (argc < REQUIRED_ARGC)
		print_err_exit(ERR_HELP_MSG, ERR_HELP_EXITNUM);
	(void)argv;
	ft_printf("PATH = %s\n", get_env_value(envp, "PATH"));
	ft_printf("TMPDIR = %s\n", get_env_value(envp, "TMPDIR"));
	ft_printf("SHELL = %s\n", get_env_value(envp, "SHELL"));
	ft_printf("~~~~~~~~~~~~~~~~~~~~~~~~~");
	while (*envp != NULL)
	{
		ft_printf("%s\n", *envp);
		envp++;
	}
	return (0);
}
