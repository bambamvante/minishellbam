/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:12:34 by knakto            #+#    #+#             */
/*   Updated: 2025/06/24 22:47:44 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include "KML/include/kml.h"
# include "parser.h"
# include "env.h"

typedef enum e_redirect_type	t_redirect_type;

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
		type	WRITE_static 
	
}direct
		NULL
	pid	0
next
process);
}
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

typedef struct s_shell
{
	char				*tmp;
	char				*line;
}	t_shell;

//main
void		init_shell(t_shell *shell);
void		init_envp(char **envp);
void		minishell(t_shell *shell);
//exit
static int	*ext(void);
bool		is_exit(int num);
//execute
t_process	**get_t_process(void);
//utils
int			*get_code(void);
void		clear_t_process(void);
//fd
int			*std_in(void);

#endif
