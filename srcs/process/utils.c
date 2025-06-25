/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:17:44 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:07:15 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_builtin(t_process *proc)
{
	if (!ft_strncmp(proc->cmd[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(proc->cmd[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(proc->cmd[0], "env", 4))
		return (1);
	else if (!ft_strncmp(proc->cmd[0], "export", 7) && !proc->cmd[1])
		return (1);
	else
		return (0);
}

static void	sub_fnc_parent(int *fd, int pipe_fd[2], int sw)
{
	if (*fd != -1)
		close(*fd);
	close(pipe_fd[1]);
	if (sw)
	{
		close(pipe_fd[1]);
		*fd = pipe_fd[0];
	}
	else
		*fd = -1;
}

void	sub_fnc_process(t_process *proc, int *fd, int sw, int pipe_fd[2])
{
	if (proc->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (*fd != -1)
		{
			dup2(*fd, 0);
			close(*fd);
		}
		if (sw)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], 1);
			close(pipe_fd[1]);
		}
		redirect(proc);
		if (is_builtin(proc))
			builtin(proc);
		exec(proc->cmd, *env());
	}
	signal(SIGINT, sig_handle);
	signal(SIGQUIT, sig_handle);
	sub_fnc_parent(fd, pipe_fd, sw);
}
