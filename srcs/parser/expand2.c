/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:58:12 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/29 00:13:33 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_quote_type	check_quote_type(const char *str)
{
	int	len;

	if (!str)
		return (NO_QUOTE);
	len = ft_strlen(str);
	if (len >= 2)
	{
		if (str[0] == '\'' && str[len - 1] == '\'')
			return (SINGLE_QUOTE);
		if (str[0] == '\"' && str[len - 1] == '\"')
			return (DOUBLE_QUOTE);
	}
	return (NO_QUOTE);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

char	*interpret_escapes(char *cmd, int i, int j)
{
	char	*res;

	res = malloc(ft_strlen(cmd) + 1);
	while (cmd[i])
	{
		if (cmd[i] == '\\')
		{
			i++;
			if (cmd[i] == 'n')
				res[j++] = '\n';
			else if (cmd[i] == 't') 
				res[j++] = '\t';
			else if (cmd[i] == '\\')
				res[j++] = '\\';
			else
				res[j++] = cmd[i];
		}
		else
			res[j++] = cmd[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}


char	*parse_ansi_c_quoted(const char *cmd, int *i)
{
	int		start;
	char	quote;
	char	*raw;
	char	*translated;

	quote = cmd[*i + 1];
	if (quote != '\'' && quote != '"')
		return (NULL); 
	start = *i + 2;
	*i = start;
	while (cmd[*i] && (cmd[*i] != quote))
		(*i)++;
	raw = ft_substr(cmd, start, *i - start);
	translated = interpret_escapes(raw, 0, 0);
	free(raw);
	if (cmd[*i] == '\'' || cmd[*i] == '\"')
		(*i)++;
	return (translated);
}
