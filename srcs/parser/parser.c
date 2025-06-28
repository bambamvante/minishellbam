/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:35:55 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/29 00:05:42 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	debug_process_list(t_process *proc)
{
	int	i = 0;

	while (proc)
	{
		printf("Process %d:\n", i++);
		for (int j = 0; proc->cmd && proc->cmd[j]; j++)
			printf("  cmd[%d]: %s\n", j, proc->cmd[j]);
		for (t_redirect *r = proc->redirect; r; r = r->next)
			printf("  redirect: type %d, value %s\n", r->type, r->value);
		proc = proc->next;
	}
}

bool	parser(t_shell *shell)
{
	int			i;

	i = 0;
	if (!shell->line || is_null(shell->line))
		return (NULL);
	if (!syntax_valid(shell, shell->line, i))
		return (NULL);
	i = 0;
	if (!lexer(shell->line, i))
		return (false);
	if (!expand_tokens())
		return (false);
	if (!unquote())
		return (false);
	debug_process_list(*get_t_process());
	return (true);
}

