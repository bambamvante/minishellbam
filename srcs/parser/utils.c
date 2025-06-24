/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:00:11 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/24 22:36:03 by arphueng         ###   ########.fr       */
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

int	is_redirect(char c)
{
	return (c == '<' || c == '>');
}

int	is_all_space(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
