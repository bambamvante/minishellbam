/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:37:07 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/28 03:30:19 by arphueng         ###   ########.fr       */
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

typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}	t_quote_type;

typedef enum e_state
{
	DEFAULT,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE
}	t_state;

typedef enum e_op_type
{
	ERR_NONE,
	ERR_PIPE,
	ERR_APPEND_PIPE,
	ERR_REDIRECT,
	ERR_NEWLINE
}	t_op_type;

typedef struct s_token
{
	t_quote_type	type;
	char			*value;
}	t_token;

//parser
bool			parser(t_shell *shell);

//syntax
bool			syntax_valid(t_shell *shell, char *input, int i);

//lexer
bool			lexer(char *line, int i);
char			**split_cmd_and_redirect(char *split, t_redirect **redir_list,
					char **tmp);
char			**split_by_pipe(char *line);
bool			process_cmd(t_process **proc_list, char *split);
char			**lexer_split_cmd(char *input, int i, int t, int err);
static char		*get_plain_token(const char *s, int *i);
static char		*get_quoted_token(const char *s, int *i, int *err);

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
char			**split_token_redirect(char **tokens);
static int		redirect_op_len(const char *str);
static int		count_tokens_after_split(char **tokens, int i, int count);
static int		fill_split_token(char *token, char **res, int j);
static int		count_tokens_after_split(char **tokens, int i, int count);

//expand
bool			expand_tokens(void);
t_quote_type	check_quote_type(const char *str);
char			*ft_strjoin_and_free(char *res, char *tmp);
char			*expand_dollar(char *cmd, int *pos, t_env *env);
char			*expand_variable(char *cmd, t_env *env);

//unquote
char			*unquote(char *cmd);
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