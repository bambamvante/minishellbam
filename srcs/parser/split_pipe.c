/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:53:30 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/29 18:09:50 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes_outside_quotes(char *line, int i, int count)
{
	bool	in_squote;
	bool	in_dquote;

	in_squote = false;
	in_dquote = false;
	while (line[i])
	{
		if (line[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (line[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (line[i] == '|' && !in_squote && !in_dquote)
			count++;
		i++;
	}
	return (count);
}

char	**split_by_pipe_respecting_quotes(char *line, int i, int j, int start)
{
	bool	in_squote;
	bool	in_dquote;
	char	**res;
	int		count;

	count = count_pipes_outside_quotes(line, 0, 1);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	in_dquote = false;
	in_squote = false;
	while (line[i])
	{
		if (line[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (line[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (line[i] == '|' && !in_squote && !in_dquote)
		{
			res[j++] = ft_strndup(line + start, i - start);
			start = i + 1;
		}
		i++;
	}
	res[j++] = ft_strndup(line + start, i - start);
	res[j] = NULL;
	return (res);
}


