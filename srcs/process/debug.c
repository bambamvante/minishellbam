/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 10:24:46 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:06:32 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

#if DEBUG_PROCESS==1

static void	print_re(t_redirect *re)
{
	while (re)
	{
		pnf("redirect: [%s]\n", re->value);
		if (re->type == HERE_DOC)
			pnf("type: [HEREDOC]\n");
		else if (re->type == APPEND_FILE)
			pnf("type: [APPEND]\n");
		else if (re->type == READ_FILE)
			pnf("type: [READ]\n");
		else if (re->type == WRITE_FILE)
			pnf("type: [WRITE]\n");
		re = re->next;
	}
}

void	print_proc(void)
{
	t_process	*proc;
	t_redirect	*re;
	int			i;

	proc = *get_t_process();
	re = NULL;
	while (proc)
	{
		i = 0;
		pnf("\n----------------------\n");
		while (proc->cmd[i])
			pnf("[%s] ", proc->cmd[i++]);
		pnf("\n----------------------\n");
		if (proc->redirect)
		{
			re = proc->redirect;
			print_re(re);
		}
		proc = proc->next;
	}
	pnf("============================================\n");
}

#else

void	print_proc(void)
{
}

#endif
