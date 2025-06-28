/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:37:28 by knakto            #+#    #+#             */
/*   Updated: 2025/06/29 00:51:03 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "signal.h"

static int	len_process(void)
{
	t_process	*proc;
	int			len;

	proc = *get_t_process();
	len = 0;
	while (proc)
	{
		proc = proc->next;
		len++;
	}
	return (len);
}

static void	run_process(t_process *proc, int sw)
{
	int			pipe_fd[2];
	static int	fd = -1;

	pipe(pipe_fd);
	proc->pid = fork();
	if (proc->pid < 0)
	{
		pnf_fd(2, "bash: error: broken fork\n");
		clear_t_process();
		exit(1);
	}
	sub_fnc_process(proc, &fd, sw, pipe_fd);
}

static void	ft_wait_proc(int all_proc, pid_t last_pid)
{
	int		i;
	int		temp_code;
	int		temp_pid;

	i = 0;
	temp_code = 0;
	temp_pid = 0;
	while (i < all_proc)
	{
		temp_pid = wait(&temp_code);
		if (temp_pid == last_pid)
			*get_code() = (temp_code / 256);
		i++;
	}
	check_sig_status();
	signal(SIGINT, signal_reset_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	process(void)
{
	t_process	*proc;
	int			all_proc;
	pid_t		last_pid;

	proc = *get_t_process();
	if (read_all_heredoc(proc) || check_builtin(proc))
		return ;
	all_proc = len_process();
	last_pid = 0;
	while (proc)
	{
		if (proc->next)
			run_process(proc, 1);
		else
		{
			run_process(proc, 0);
			last_pid = proc->pid;
		}
		proc = proc->next;
	}
	ft_wait_proc(all_proc, last_pid);
	clear_t_process();
}
