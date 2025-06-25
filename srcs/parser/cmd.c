/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 01:06:48 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/26 03:24:25 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_process	*init_process(void)
{
	t_process	*proc;

	proc = malloc(sizeof(t_process));
	if (!proc)
		return (NULL);
	proc->cmd = NULL;
	proc->next = NULL;
	proc->redirect = NULL;
	proc->pid = -1;
	return (proc);
}

void	add_process(t_process **proc_list, t_process *new_proc)
{
	t_process	*tmp;

	if (!proc_list || !new_proc)
		return ;
	if (*proc_list == NULL)
		*proc_list = new_proc;
	else
	{
		tmp = *proc_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_proc;
		printf("[ADD] appended cmd: %s\n", new_proc->cmd[0]);
	}
}

char	**parse_cmd(char **token, int i, int j, int cmd_count)
{
	char	**cmd;

	while (token[i])
	{
		if (is_redirect_token(token[i]))
			i += 2;
		else
		{
			cmd_count++;
			i++;
		}
	}
	cmd = malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (token[i])
	{
		if (is_redirect_token(token[i]))
			i += 2;
		else
			cmd[j++] = ft_strdup(token[i++]);
	}
	cmd[j] = NULL;
	return (cmd);
}
