/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 03:15:08 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/28 01:05:47 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include <stdlib.h>

void	*ft_calloc_nofill(size_t count, size_t size)
{
	size_t	bytes_to_allocate;

	bytes_to_allocate = count * size;
	if (bytes_to_allocate != 0
		&& (bytes_to_allocate < count || bytes_to_allocate < size))
		return (NULL);
	if (bytes_to_allocate <= 0)
		bytes_to_allocate = 1;
	return (malloc(bytes_to_allocate));
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p_ret;

	p_ret = ft_calloc_nofill(count, size);
	if (p_ret != NULL)
		ft_bzero(p_ret, count * size);
	return (p_ret);
}
