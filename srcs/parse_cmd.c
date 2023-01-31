/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 22:59:04 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/31 13:48:13 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_vect/ft_vect.h"
#include "../libft/ft_is/ft_is.h"
#include "../libft/ft_string/ft_string.h"

#include <stdlib.h>

#define S_QUOTE '\''
#define D_QUOTE '\"'

static void	append_segment_or_exit(t_vect *vect, t_vect *segment);
static void	append_quoted_or_exit(t_vect *vect,
				t_vect *segment, const char **cmd);

t_vect	parse_cmd(const char *cmd)
{
	t_vect	ret;
	t_vect	segment;

	ret = vect_init(1, sizeof(char *));
	segment = vect_init(FT_VECT_EXPAND_STEP, sizeof(char));
	while (*cmd != '\0')
	{
		if (ft_isspace(*cmd))
			append_segment_or_exit(&ret, &segment);
		else if (*cmd == S_QUOTE || *cmd == D_QUOTE)
			append_quoted_or_exit(&ret, &segment, &cmd);
		else if (*cmd == '\\')
		{
			vect_push_back(&segment, (void *)(cmd + 1), NULL);
			cmd += 1;
		}
		else
			vect_push_back(&segment, (void *)(cmd), NULL);
		cmd++;
	}
	append_segment_or_exit(&ret, &segment);
	vect_dispose(&segment);
	vect_push_back(&ret, &(segment.p), NULL);
	return (ret);
}

static void	append_quoted_or_exit(t_vect *vect,
	t_vect *segment, const char **cmd)
{
	char	quote;

	quote = **cmd;
	*cmd += 1;
	while (**cmd != '\0' && **cmd != quote)
	{
		if (**cmd == '\\' && (*(*cmd + 1) != '\0'))
			*cmd += 1;
		vect_push_back(segment, (void *)*cmd, NULL);
		*cmd += 1;
	}
	if (**cmd == '\0')
	{
		vect_dispose(segment);
		vect_dispose_ptrarr(vect);
		exit(1);
	}
}

static void	append_segment_or_exit(t_vect *vect, t_vect *segment)
{
	if (segment->len == 0)
		return ;
	if (!vect_push_back(vect, &(segment->p), NULL))
	{
		vect_dispose(segment);
		vect_dispose_ptrarr(vect);
		exit(1);
	}
	*segment = vect_init(FT_VECT_EXPAND_STEP, sizeof(char));
}
