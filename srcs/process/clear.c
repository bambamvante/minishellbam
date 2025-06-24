/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:35:03 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/24 16:36:10 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_t_redirect(t_redirect *re)
{
	t_redirect	*temp;

	while (re)
	{
		free(re->value);
		temp = re;
		re = re->next;
		free(temp);
	}
}

void	clear_t_process(void)
{
	t_process	*proc;
	t_process	*temp;

	proc = *get_t_process();
	while (proc)
	{
		free_split(proc->cmd);
		clear_t_redirect(proc->redirect);
		temp = proc;
		proc = proc->next;
		free(temp);
	}
	*get_t_process() = NULL;
}
