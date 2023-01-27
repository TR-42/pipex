/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_reserve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:32:55 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/28 01:35:56 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vect.h"
#include "../ft_mem/ft_mem.h"
#include "stdlib.h"

bool	vect_reserve(t_vect *vect, size_t newcap)
{
	void	*p_new;

	if (vect->elemsize == 0 || vect->len < newcap)
		return (false);
	if (newcap == 0)
		p_new = NULL;
	else
	{
		p_new = ft_calloc_nofill(newcap, vect->elemsize);
		if (p_new == NULL)
			return (false);
		ft_memmove(vect->p, p_new, vect->elemsize * vect->len);
		free(vect->p);
	}
	vect->p = p_new;
	vect->cap = newcap;
	return (true);
}
