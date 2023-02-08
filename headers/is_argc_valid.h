/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_argc_valid.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:23:54 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/09 00:24:44 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_ARGC_VALID_H
# define IS_ARGC_VALID_H

# include <stdbool.h>

# define REQUIRED_ARGC 5

bool	is_argc_valid(int argc);

#endif
