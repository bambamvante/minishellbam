/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 01:24:26 by knakto            #+#    #+#             */
/*   Updated: 2025/06/29 15:51:42 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*create_name_temp_file(int id)
{
	char	*heredoc;
	char	*name_id;
	char	*res;

	heredoc = "/tmp/heredoc_";
	name_id = ft_itoa(id);
	res = ft_strjoin(heredoc, name_id);
	free(name_id);
	return (res);
}

static void	end_heredoc(t_redirect *re, char *name_file, int fd)
{
	if (fd > 0)
		close(fd);
	free(re->value);
	re->value = name_file;
}

static void	error(t_redirect *redirect, char *name_file, int fd)
{
	if (*sig_status() != 2)
		pnf_fd(2, HEREDOC_ERR, redirect->value);
	else
		pnf("\n");
	end_heredoc(redirect, name_file, fd);
}

void	ft_heredoc(t_redirect *redirect)
{
	static int	id = 0;
	int			fd;
	char		*name_file;
	char		*line;

	if (*sig_status() == 2)
		return ;
	name_file = create_name_temp_file(id++);
	fd = open(name_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	line = readline(">");
	while (line)
	{
		if (!ft_strncmp(redirect->value, line, ft_strlen(redirect->value)) \
&& ft_strlen(line) == ft_strlen(redirect->value))
		{
			end_heredoc(redirect, name_file, fd);
			free(line);
			return ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
		line = readline(">");
	}
	error(redirect, name_file, fd);
}

int	read_all_heredoc(t_process *proc)
{
	t_redirect	*re;

	signal(SIGINT, sig_set_null);
	while (proc)
	{
		re = proc->redirect;
		while (re)
		{
			if (re->type == HERE_DOC && !is_in_quote(re->value))
				ft_heredoc(re);
			re = re->next;
		}
		proc = proc->next;
	}
	if (*sig_status() == 2)
	{
		signal(SIGINT, signal_prompt);
		*sig_status() = 0;
		*get_code() = 128 + SIGINT;
		return (1);
	}
	return (0);
}
