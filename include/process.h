/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:58 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:55:47 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H 
# define PROCESS_H

# include <stdbool.h>
# include <sys/wait.h>
# include "env.h"
# include "builtin.h"
// # include "exec.h"
# include "KML/include/kml.h"
# include "minishell.h"

typedef enum e_redirect_type
{
	READ_FILE,
	HERE_DOC,
	WRITE_FILE,
	APPEND_FILE,
}	t_redirect_type;

typedef struct s_redirect
{
	t_redirect_type		type;
	char				*value;
	struct s_redirect	*next;
}	t_redirect;

/*
this struct is init before run all process one node 
is mean one pipe and redirect can stack multiple redirect 
pid declare init is 0 and cmd is "malloc" of cmd 

Example
---
echo helllo world > b > c | cat Makefie | < b cat
---
process
	cmd	[[echo] [hello world]]
	redirect
		type	WRITE_FILE
		value	b
		next
	redirect
		type	WRITE_FILE
		value	c
		next	NULL
	pid 0
next
process
	cmd [[cat] [Makefile]]
	redirect
		NULL
	pid	0
next
process
	cmd	[[cat]]
	redirect
		type	READ_FILE
		value	b
		next	NULL
	pid	0
next	NULL
---
*/
typedef struct s_process
{
	char				**cmd;
	t_redirect			*redirect;
	pid_t				pid;
	struct s_process	*next;
}	t_process;

t_process	**get_t_process(void);
void		exec(char **cmd, char **env);
void		ft_heredoc(t_redirect *redirect);
int			read_all_heredoc(t_process *proc);
void		check_access_file(t_redirect *re);
void		clear_t_process(void);
void		redirect(t_process *proc);
void		process(void);
int			builtin(t_process *proc);
int			check_builtin(t_process *proc);
void		print_proc(void);
void		sub_fnc_process(t_process *proc, int *fd, int sw, int pipe_fd[2]);

# define HEREDOC_ERR "bash: warning: here-document at line delimited \
by end-of-file (wanted `%s')\n"

#endif