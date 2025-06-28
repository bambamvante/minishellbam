/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 01:26:46 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/28 21:05:17 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*unquote_all(char *input, int i, int j)
{
	char	*res;
	bool	in_squote;
	bool	in_dquote;

	if (!input)
		return (NULL);
	res = malloc(ft_strlen(input) + 1);
	in_squote = false;
	in_dquote = false;
	if (!res)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		else if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else
			res[j++] = input[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}


bool	unquote(void)
{
	t_process		*proc;
	char			**cmd;
	int				i;
	t_quote_type	type;
	char			*unquote;

	proc = *get_t_process();
	while (proc)
	{
		cmd = proc->cmd;
		i = 0;
		while (cmd && cmd[i])
		{
			type = check_quote_type(cmd[i]);
			if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
			{
				unquote = unquote_all(cmd[i], 0, 0);
				free(cmd[i]);
				cmd[i] = unquote;
			}
			i++;
		}
		proc = proc->next;
	}
	return (true);
}

