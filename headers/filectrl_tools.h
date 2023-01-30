/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filectrl_tools.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 16:16:23 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/30 16:29:43 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILECTRL_TOOLS_H
# define FILECTRL_TOOLS_H

char	*chk_and_get_fullpath(const char *given_path, const char **env_path);
#endif
