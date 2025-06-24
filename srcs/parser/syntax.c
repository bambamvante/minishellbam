/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:55:57 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/25 01:02:12 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	check_pipe(char *input, int pos, t_op_type *error_type)
{
	pos++;
	while (input[pos] && ft_isspace(input[pos]))
		pos++;
	if (!input[pos])
	{
		*error_type = ERR_NEWLINE;
		return (false);
	}
	if (input[pos] == '|' && input[pos + 1] == '|')
	{
		*error_type = ERR_APPEND_PIPE;
		return (false);
	}
	if (input[pos] == '|')
	{
		*error_type = ERR_PIPE;
		return (false);
	}
	return (true);
}

static bool	check_redirect(char *input, int *pos, t_op_type *error_type)
{
	int		i;

	i = 0;
	if ((ft_strncmp(&input[*pos], ">>", 2) == 0)
		|| (ft_strncmp(&input[*pos], "<<", 2) == 0))
		*pos += 2;
	else if (input[*pos] == '>' || input[*pos] == '<')
		*pos += 1;
	i = *pos;
	while (input[i] && ft_isspace(input[i]))
		i++;
	if (!input[i])
	{
		*error_type = ERR_NEWLINE;
		return (false);
	}
	if (is_operator(input[i]))
	{
		*error_type = ERR_REDIRECT;
		return (false);
	}
	return (true);
}

static bool	check_operator(char *input, int pos, t_op_type *error_type)
{
	if (input[pos] == '|')
		return (check_pipe(input, pos, error_type));
	else if (input[pos] == '>' || input[pos] == '<')
		return (check_redirect(input, &pos, error_type));
	*error_type = ERR_NONE;
	return (true);
}

static bool	handle_operator(t_shell *shell, char *input, int pos)
{
	t_op_type	error_type;
	char		*token;

	while (ft_isspace(input[pos]))
		pos++;
	if (!is_operator(input[pos]))
		return (false);
	if (!check_operator(input, pos, &error_type))
	{
		token = check_error_token(input, pos, error_type);
		return (token_syntax_error(shell, token));
	}
	return (true);
}

bool	syntax_valid(t_shell *shell, char *input, int i)
{
	bool	single_quote;
	bool	double_quote;

	single_quote = false;
	double_quote = false;
	while (input[i])
	{
		if (input[i] == '\"' && !single_quote)
			double_quote = !double_quote;
		else if (input[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		if (!double_quote && !single_quote)
		{
			if (is_operator(input[i]))
			{
				if (!handle_operator(shell, input, i))
					return (false);
			}
		}
		i++;
	}
	if (!quote_pair_error(shell, single_quote, double_quote))
		return (false);
	return (true);
}


