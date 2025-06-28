/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 17:11:21 by knakto            #+#    #+#             */
/*   Updated: 2025/06/29 00:51:36 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	file_in(int *fd, t_redirect *re)
{
	if (*fd > 2)
	{
		close(*fd);
		*fd = 0;
	}
	if (access(re->value, F_OK))
		return (1);
	if (access(re->value, R_OK))
		return (2);
	*fd = open(re->value, O_RDONLY);
	return (0);
}

static int	file_out(int *fd, t_redirect *re)
{
	if (*fd > 2)
		close(*fd);
	if (re->type == WRITE_FILE)
		*fd = open(re->value, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (re->type == APPEND_FILE)
		*fd = open(re->value, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (access(re->value, W_OK))
	{
		if (*fd > 2)
			close(*fd);
		return (2);
	}
	return (0);
}

static void	fd_err(int fd_in, int fd_out, int status, t_redirect *re)
{
	if (fd_in > 2)
		close(fd_in);
	if (fd_out > 2)
		close(fd_out);
	if (status == 1)
	{
		pnf_fd(2, "bash: %s: No such file or directory\n", re->value);
		clear_t_process();
		exit(1);
	}
	else if (status == 2)
	{
		pnf_fd(2, "bash: %s: Permission denied\n", re->value);
		clear_t_process();
		exit(1);
	}
}

void	find_fd(t_redirect *re, int *fd_in, int *fd_out)
{
	int		status;

	status = 0;
	*fd_out = 1;
	*fd_in = 0;
	while (re)
	{
		if (re->type == HERE_DOC || re->type == READ_FILE)
			status = file_in(fd_in, re);
		else if (re->type == APPEND_FILE || re->type == WRITE_FILE)
			status = file_out(fd_out, re);
		if (status > 0)
			fd_err(*fd_in, *fd_out, status, re);
		re = re->next;
	}
}

void	redirect(t_process *proc)
{
	int		fd_in;
	int		fd_out;
	int		status;

	find_fd(proc->redirect, &fd_in, &fd_out);
	status = 1;
	if (!ft_strncmp(proc->cmd[0], "cd", 3) \
|| (!ft_strncmp(proc->cmd[0], "export", 7) && proc->cmd[1]) \
|| !ft_strncmp(proc->cmd[0], "unset", 6) \
|| !ft_strncmp(proc->cmd[0], "exit", 5))
		status = 0;
	if (fd_in > 0)
	{
		if (status)
			dup2(fd_in, 0);
		close(fd_in);
	}
	if (fd_out > 1)
	{
		if (status)
			dup2(fd_out, 1);
		close(fd_out);
	}
}
