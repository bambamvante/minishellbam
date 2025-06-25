/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:37:07 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/26 03:48:16 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include "KML/include/kml.h"
# include "minishell.h"
# include "process.h"
# include "env.h"

typedef struct s_shell			t_shell;
typedef struct s_process		t_process;
typedef struct s_redirect		t_redirect;
typedef enum e_redirect_type	t_redirect_type;

typedef enum e_op_type
{
	ERR_NONE,
	ERR_PIPE,
	ERR_APPEND_PIPE,
	ERR_REDIRECT,
	ERR_NEWLINE
}	t_op_type;

//parser
bool			parser(t_shell *shell);

//syntax
bool			syntax_valid(t_shell *shell, char *input, int i);

//lexer
bool			lexer(char *line, int i);
char			**split_cmd_and_redirect(char *split, t_redirect **redir_list,
					char **tmp);
char			**split_by_pipe(char *line);

//lexer -> [cmd]
char			**parse_cmd(char **token, int i, int j, int cmd_count);
t_process		*init_process(void);
void			add_process(t_process **proc_list, t_process *new_proc);

// lexer -> [redirect]
bool			is_redirect_token(char *token);
t_redirect_type	get_redirect_type(char *token);
void			parse_redirect(char **token, t_redirect **redir_list);
t_redirect		*init_redirect(t_redirect_type type, char *value);
void			add_redirect(t_redirect **redir_list, t_redirect *new_redir);
int				redirect_op_len(const char *str);
int				count_tokens_after_split(char **tokens);
char			**split_token_redirect(char **tokens);

//free
void			free_redirect_list(t_redirect *redir);
void			free_process(t_process *proc);
void			free_process_list(t_process *proc_list);

//expand
bool			expand_tokens(t_shell *shell);

//error
bool			quote_pair_error(t_shell *shell, bool s_quote, bool d_quote);
bool			token_syntax_error(t_shell *shell, char *token);
bool			unmatched_quote_error(t_shell *shell, char quote);
char			*check_error_token(char *input, int pos, t_op_type error_type);

//utils
bool			is_null(char *input);
bool			is_quote(char c);
bool			is_operator(char c);
int				is_all_space(char *str);
//debug

#endif