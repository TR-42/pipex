/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 00:18:17 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:18:50 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

// Dependency:
// - size_t
# include <stddef.h>

int		ft_min(int a, int b);
long	ft_minl(long a, long b);
size_t	ft_minp(size_t a, size_t b);
double	ft_minf(double a, double b);

int		ft_max(int a, int b);
long	ft_maxl(long a, long b);
size_t	ft_maxp(size_t a, size_t b);
double	ft_maxf(double a, double b);

#endif
