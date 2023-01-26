/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:58:25 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/24 04:39:55 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "ft_printf_local.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	t_list	*list;
	int		written_count;

	if (*format == '\0')
		return (0);
	else if (format[0] != '%' && format[1] == '\0')
		return (write(STDOUT_FILENO, format, 1));
	va_start(args, format);
	list = parse_format(format, &args);
	va_end(args);
	if (list == NULL)
		return (-1);
	written_count = print_all(list);
	ft_lstclear(&list, free);
	return (written_count);
}
