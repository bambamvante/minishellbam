/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:44:40 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/26 03:45:17 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	redirect_op_len(const char *str)
{
	if (!str)
		return (0);
	if (strncmp(str, "<<", 2) == 0 || strncmp(str, ">>", 2) == 0)
		return (2);
	if (*str == '<' || *str == '>')
		return (1);
	return (0);
}

int	count_tokens_after_split(char **tokens)
{
	int i = 0;
	int count = 0;
	int pos;
	int len;

	while (tokens[i])
	{
		pos = 0;
		while (tokens[i][pos])
		{
			len = redirect_op_len(&tokens[i][pos]);
			if (len > 0)
			{
				if (pos > 0)
					count++;
				count++;
				pos += len;
			}
			else
				pos++;
		}
		count++;
		i++;
	}
	return count;
}

char	**split_token_redirect(char **tokens)
{
	int		i = 0;
	int		j = 0;
	int		count = count_tokens_after_split(tokens);
	char	**result = malloc(sizeof(char *) * (count + 1));
	char	*token;
	int		pos;
	int		start;
	int		len;

	if (!result)
		return (NULL);

	while (tokens[i])
	{
		token = tokens[i];
		pos = 0;
		start = 0;
		while (token[pos])
		{
			len = redirect_op_len(&token[pos]);
			if (len > 0)
			{
				if (pos > start)
					result[j++] = strndup(&token[start], pos - start);
				result[j++] = strndup(&token[pos], len);
				pos += len;
				start = pos;
			}
			else
				pos++;
		}
		if (pos > start)
			result[j++] = strndup(&token[start], pos - start);
		i++;
	}
	result[j] = NULL;
	return (result);
}
