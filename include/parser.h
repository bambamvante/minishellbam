/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:37:07 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/25 00:52:41 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdio.h>
# include "KML/include/kml.h"
# include "minishell.h"
# include "env.h"

typedef struct s_shell			t_shell;

typedef enum e_op_type
{
	ERR_NONE,
	ERR_PIPE,
	ERR_APPEND_PIPE,
	ERR_REDIRECT,
	ERR_NEWLINE
}	t_op_type;

typedef enum e_redirect_type
{
	READ_FILE,
	HERE_DOC,
	WRITE_FILE,
	APPEND_FILE,
}	t_redirect_type;

typedef enum e_token_type
{
	CMD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_HEREDOC,
	REDIRECT_APPEND,
}	t_token_type;

typedef struct s_token
{
	char				*value;
	t_redirect_type		redirect_type;
	t_token_type		type;
	struct s_token		*prev;
	struct s_token		*next;
}	t_token;

//parser
bool			parser(t_shell *shell);

//syntax
bool			syntax_valid(t_shell *shell, char *input, int i);

//lexer
bool			lexer(t_shell *shell, t_token **token, char *line);
t_token_type	check_type(char *str);
char			**split_by_spaces(char *line);
//lexer-pipe
char			**split_pipe_word(char *str);
int				count_pipe_split(char *str);
void			add_type_pipe(t_token *token);
t_token_type	check_type(char *str);
//lexer-redirect
void			split_redirect_word(t_token **token);
void			split_token_redirect(t_token *curr, t_token **token);
void			remove_token(t_token **token, t_token *target);
void 			add_token_before(t_token **head, t_token *target, char *value,
					t_token_type type);
int				redirect_operator_len(char *str);
bool			token_need_split(t_token *token);
t_redirect_type	redirect_type_from_value(char *value);
void			remove_empty_or_space_token(t_token **token);
bool			is_redirect_operator(t_token *token);
//token
t_token			*new_token(t_token_type type, char *str, int quoted);
void			add_token(t_token **token, t_token_type type, char *str,
					int quoted);
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
void			print_token(t_token *token_list);

#endif