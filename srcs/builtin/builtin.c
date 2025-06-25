/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:29:04 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:55:08 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	len_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

void	use_function(t_process *proc, t_use_function func)
{
	if (func == FT_CD)
		ft_chdir(proc->cmd);
	else if (func == FT_ECHO)
		ft_echo(proc->cmd);
	else if (func == FT_PWD)
		ft_pwd(proc->cmd);
	else if (func == FT_ENV)
		ft_env(proc->cmd);
	else if (func == FT_EXPORT)
		ft_export(proc->cmd);
	else if (func == FT_UNSET)
		ft_unset(proc->cmd);
	else if (func == FT_EXIT)
		ft_exit(proc->cmd);
}

int	builtin(t_process *proc)
{
	if (!ft_strncmp(proc->cmd[0], "cd", 3))
		use_function(proc, FT_CD);
	else if (!ft_strncmp(proc->cmd[0], "echo", 5))
		use_function(proc, FT_ECHO);
	else if (!ft_strncmp(proc->cmd[0], "pwd", 4))
		use_function(proc, FT_PWD);
	else if (!ft_strncmp(proc->cmd[0], "env", 4))
		use_function(proc, FT_ENV);
	else if (!ft_strncmp(proc->cmd[0], "export", 7))
		use_function(proc, FT_EXPORT);
	else if (!ft_strncmp(proc->cmd[0], "unset", 7))
		use_function(proc, FT_UNSET);
	else if (!ft_strncmp(proc->cmd[0], "exit", 5))
		use_function(proc, FT_EXIT);
	else
		return (0);
	return (1);
}
