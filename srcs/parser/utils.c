/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:00:11 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/29 16:26:06 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_null(char *input)
{
	char	*res;

	if (!input)
		return (true);
	res = ft_strtrim(input, "\t\n");
	if (!res || res[0] == '\0')
	{
		free(res);
		return (true);
	}
	free(res);
	return (false);
}

bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

bool	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

bool	is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == ';');
}

bool	is_double_op(char c1, char c2)
{
	return ((c1 == '|' && c2 == '|') || (c1 == '&' && c2 == '&'));
}
