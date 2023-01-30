/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:49:23 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/30 15:02:44 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf/ft_printf.h"
#include "../headers/parse_cmd.h"

#include <stdlib.h>

int	main(int argc, char *argv[])
{
	int		i;
	size_t	j;
	t_vect	result;

	i = 0;
	while (i < argc)
	{
		ft_printf("[%d]: |%s|\n", i, argv[i]);
		result = parse_cmd(argv[i]);
		j = 0;
		while (j < result.len)
		{
			ft_printf("\t[%d]: |%s|\n", j, ((unsigned char **)result.p)[j]);
			j++;
		}
		ft_printf("~~~~~~~~~~~~~~~~~~~~\n");
		vect_dispose_ptrarr(&result);
		i++;
	}
}
