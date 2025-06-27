/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 03:44:40 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/26 17:43:41 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	redirect_op_len(const char *str)
{
	if (!str)
		return (0);
	if (strncmp(str, "<<", 2) == 0 || strncmp(str, ">>", 2) == 0)
		return (2);
	if (*str == '<' || *str == '>')
		return (1);
	return (0);
}

static int	count_tokens_after_split(char **tokens, int i, int count)
{
	int	pos;
	int	len;

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
	return (count);
}

static int	fill_split_token(char *token, char **res, int j)
{
	int	pos;
	int	start;
	int	len;

	pos = 0;
	start = 0;
	while (token[pos])
	{
		len = redirect_op_len(&token[pos]);
		if (len > 0)
		{
			if (pos > start)
				res[j++] = ft_strndup(&token[start], pos - start);
			res[j++] = ft_strndup(&token[pos], len);
			pos += len;
			start = pos;
		}
		else
			pos++;
	}
	if (pos > start)
		res[j++] = ft_strndup(&token[start], pos - start);
	return (j);
}

char	**split_token_redirect(char **tokens)
{
	int		i;
	int		j;
	int		count;
	char	**res;
	char	*token;

	i = 0;
	j = 0;
	count = count_tokens_after_split(tokens, 0, 0);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	while (tokens[i])
		j = fill_split_token(tokens[i++], res, j);
	res[j] = NULL;
	return (res);
}
