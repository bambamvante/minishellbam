/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:17:39 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/28 02:55:01 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_dollar(char *cmd, int *pos, t_env *env)
{
	int		start;
	int		i;
	char	*key;
	char	*value;

	start = *pos + 1;
	i = start;
	if (cmd[i] == '?')
	{
		value = ft_itoa(*get_code());
		*pos = i + 1;
		return (value);
	}
	if (cmd[i] == '$')
	{
		value = ft_itoa(*minishell_pid());
		*pos = i + 1;
		return (value);
	}
	if (!ft_isalpha(cmd[i]) && cmd[i] != '_')
	{
		value = ft_strdup("$");
		*pos = i;
		return (value);
	}
	while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
		i++;
	key = ft_substr(cmd, start, i - start);
	value = get_value(key);
	free(key);
	*pos = i;
	return (value);
}

char	*expand_variable(char *cmd, t_env *env)
{
	char	*res;
	int		i;
	int		start;
	char	*tmp;

	i = 0;
	res = ft_strdup("");
	while (cmd[i])
	{
		if (cmd[i] == '$')
			tmp = expand_dollar(cmd, &i, env);
		else
		{
			start = i;
			while (cmd[i] && cmd[i] != '$')
				i++;
			tmp = ft_substr(cmd, start, i - start);
		}
		res = ft_strjoin_and_free(res, tmp);
	}
	return (res);
}

char	*expand_one_token(char *cmd, t_quote_type type)
{
	int		len;
	char	*no_double_quote;
	char	*expanded;

	if (!cmd)
		return (NULL);
	len = ft_strlen(cmd);
	if (type == SINGLE_QUOTE)
	{
		if (len >= 2)
			return (ft_strndup(cmd + 1, len - 2));
		else
			return (ft_strdup(""));
	}
	else if (type == DOUBLE_QUOTE)
	{
		if (len >= 2)
		{
			no_double_quote = ft_strndup(cmd + 1, len - 2);
			expanded = expand_variable(no_double_quote, *get_t_env());
			free(no_double_quote);
			return (expanded);
		}
		else
			return (ft_strdup(""));
	}
	else
		return (expand_variable(cmd, *get_t_env()));
}

bool	expand_tokens(void)
{
	t_process		*proc;
	char			**cmd;
	int				i;
	char			*expanded;
	t_quote_type	type;

	proc = *get_t_process();
	while (proc)
	{
		i = 0;
		cmd = proc->cmd;
		while (cmd && cmd[i])
		{
			type = check_quote_type(cmd[i]);
			expanded = expand_one_token(cmd[i], type);
			free(cmd[i]);
			cmd[i] = expanded;
			i++;
		}
		proc = proc->next;
	}
	return (true);
}
