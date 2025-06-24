/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:26:04 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/24 23:50:46 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**split_by_spaces(char *line)
{
	char	**str;

	if (!line)
		return (NULL);
	str = ft_split(line, ' ');
	if (!str)
		return (NULL);
	return (str);
}

int	count_pipe_split(char *str)
{
	int	i;
	int	count;
	int	start;

	i = 0;
	count = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (i > start)
				count++;
			count++;
			start = i + 1;
		}
		i++;
	}
	if (i > start)
		count++;
	printf("[count_pipe_split] count=%d for string='%s'\n", count, str);
	return (count);
}

char	**split_pipe_word(char *str)
{
	char	**res;
	int		i;
	int		idx;
	int		start;
	int		count;

	i = -1;
	idx = 0;
	start = 0;
	if (!str)
		return (NULL);
	count = count_pipe_split(str);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	while (str[++i])
	{
		if (str[i] == '|')
		{
			if (i > start)
				res[idx++] = ft_substr(str, start, i - start);
			res[idx++] = ft_strdup("|");
			start = i + 1;
		}
	}
	if (i > start)
		res[idx++] = ft_substr(str, start, i - start);
	res[idx] = NULL;
	return (res);
}
