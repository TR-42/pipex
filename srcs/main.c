/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:45:11 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/30 16:27:48 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"
#include "../headers/print_error.h"
#include "../headers/filectrl_tools.h"
#include "../headers/env_util.h"
#include "../libft/ft_printf/ft_printf.h"
#include <stddef.h>
#include <stdlib.h>

static void	_test(const char *fname, char **path_arr)
{
	char	*tmp;

	tmp = chk_and_get_fullpath(fname, (const char **)path_arr);
	ft_printf("%s: '%s'\n", fname, tmp);
	free(tmp);
}

int	main(int argc, const char *argv[], const char *envp[])
{
	char	**path_arr;
	size_t	i;

	if (argc < REQUIRED_ARGC)
		print_err_exit(ERR_HELP_MSG, ERR_HELP_EXITNUM);
	(void)argv;
	path_arr = get_path_in_env(envp);
	if (path_arr == NULL)
		print_err_exit("PATH not found", 1);
	i = 0;
	while (path_arr[i] != NULL)
	{
		ft_printf("%s\n", path_arr[i]);
		i++;
	}
	ft_printf("~~~~~~~~~~~~~~~~~~~~\n");
	_test("ls", path_arr);
	_test("dotnet", path_arr);
	_test("", path_arr);
	i = 0;
	while (path_arr[i] != NULL)
	{
		free(path_arr[i]);
		i++;
	}
	free(path_arr[i]);
	return (0);
}
