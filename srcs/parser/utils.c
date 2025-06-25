/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:00:11 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/25 16:53:32 by arphueng         ###   ########.fr       */
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
