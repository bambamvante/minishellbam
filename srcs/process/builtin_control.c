/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:58:29 by knakto            #+#    #+#             */
/*   Updated: 2025/06/27 19:50:46 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_builtin(t_process *proc)
{
	if (!proc || !proc->cmd || !proc->cmd[0])
		return (0);
	if (!ft_strncmp(proc->cmd[0], "cd", 3) \
|| (!ft_strncmp(proc->cmd[0], "export", 7) && proc->cmd[1]) \
|| !ft_strncmp(proc->cmd[0], "unset", 6) \
|| !ft_strncmp(proc->cmd[0], "exit", 5))
	{
		builtin(proc);
		return (1);
	}
	return (0);
}
