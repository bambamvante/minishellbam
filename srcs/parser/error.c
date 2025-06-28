/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 12:04:08 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/29 00:50:56 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	quote_pair_error(t_shell *shell, bool s_quote, bool d_quote)
{
	if (s_quote)
		return (unmatched_quote_error(shell, '\''));
	if (d_quote)
		return (unmatched_quote_error(shell, '\"'));
	return (true);
}

bool	token_syntax_error(t_shell *shell, char *token)
{
	(void)shell;
	ft_putstr_fd("bash: syntax error near unexpected token `", STDERR_FILENO);
	if (token[0] == '\0')
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	*get_code() = 2;
	return (false);
}

bool	unmatched_quote_error(t_shell *shell, char quote)
{
	(void)shell;
	if (quote == '\'')
		ft_putstr_fd("bash: syntax error: unmatched single quote\n",
			STDERR_FILENO);
	else if (quote == '\"')
		ft_putstr_fd("bash: syntax error: unmatched double quote\n",
			STDERR_FILENO);
	*get_code() = 2;
	return (false);
}

char	*check_error_token(char *input, int pos, t_op_type error_type)
{

	if (error_type == ERR_PIPE)
		return ("|");
	else if (error_type == ERR_APPEND_PIPE)
		return ("||");
	else if (error_type == ERR_REDIRECT)
	{
		if (input[pos] == '<' && input[pos + 1] == '<')
			return ("<<");
		else if (input[pos] == '>' && input[pos + 1] == '>')
			return (">>");
		else if (input[pos] == '<')
			return ("<");
		else
			return (">");
	}
	else if (error_type == ERR_NEWLINE)
		return ("");
	return ("");
}
