/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:12:34 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:52:45 by arphueng         ###   ########.fr       */
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
# include <sys/stat.h>
# include "KML/include/kml.h"
# include "parser.h"
# include "env.h"
# include "process.h"
# include "exit.h"
# include "builtin.h"

typedef struct s_shell
{
	char				*tmp;
	char				*line;
}	t_shell;

//main
void		init_shell(t_shell *shell);
void		init_envp(char **envp);
void		minishell(t_shell *shell);

//signal
int			*sig_status(void);
void		sig_prompt(void);
void		signal_print_newline(int signal);
void		signal_reset_prompt(int signo);
void		sig_handle(int sig);
void		check_sig_status(void);
void		sig_set_null(int sig);
void		signal_prompt(int sig);

#endif
