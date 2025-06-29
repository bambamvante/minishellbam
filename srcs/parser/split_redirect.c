/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:35:34 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/29 16:31:59 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	toggle_quote_state(char c, bool *in_squote, bool *in_dquote)
{
	if (c == '\'' && !(*in_dquote))
		*in_squote = !(*in_squote);
	else if (c == '"' && !(*in_squote))
		*in_dquote = !(*in_dquote);
}

static void	push_buf(char **result, char *buf, int *j, int *buf_i)
{
	if (*buf_i > 0)
	{
		buf[*buf_i] = '\0';
		result[(*j)++] = ft_strdup(buf);
		*buf_i = 0;
	}
}

static void	process_token_loop(char *cmd, int *i, char **result, int *j)
{
	char	buf[4096];
	bool	in_squote;
	bool	in_dquote;
	int		buf_i;

	buf_i = 0;
	in_dquote = false;
	in_squote = false;
	while (cmd[*i])
	{
		toggle_quote_state(cmd[*i], &in_squote, &in_dquote);
		if (ft_isspace(cmd[*i]) && !in_squote && !in_dquote)
		{
			push_buf(result, buf, j, &buf_i);
			(*i)++;
			continue ;
		}
		buf[buf_i++] = cmd[(*i)++];
	}
	push_buf(result, buf, j, &buf_i);
}

char	**split_with_quotes(char *cmd, int i, int j)
{
	char	**result;

	result = malloc(sizeof(char *) * (ft_strlen(cmd) + 2));
	if (!result)
		return (NULL);
	process_token_loop(cmd, &i, result, &j);
	result[j] = NULL;
	return (result);
}
