/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:35:55 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/24 21:26:11 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	parser(t_shell *shell)
{
	int		i;
	t_token	*token;

	i = 0;
	if (!shell->line || is_null(shell->line))
		return (NULL);
	if (!syntax_valid(shell, shell->line, i))
		return (NULL);
	token = NULL;
	if (!lexer(shell, &token, shell->line))
		return (false);
	// if (!expand_token(shell))
	// 	return (false);
	// unquote_token();
	// build_cmd();
	return (true);
}
