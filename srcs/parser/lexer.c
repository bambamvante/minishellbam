/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:06:42 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/25 01:01:18 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*

1.) split spaces
input : echo $a | cat -e | < text.txt
after cut spaces : [echo] [$a] [|] [cat] [-e] [|] [<] [text.txt]

2.) add to token (ready for expand)
input : [echo] [$a] [|] [cat] [-e] [|] [<] [text.txt]
output : [echo] -> [$a] -> [|] -> [cat] -> [-e] -> [|] -> [<] -> [text.txt]

3.) split pipe (for in case that [cat|grep] like this)
we have to check it before add to token

4.) add type to PIPE and CMD for cut by the process by process
so type will be only 2 type : CMD and PIPE

*/

t_token_type	check_type(char *str)
{
	if (str[0] == '<' && str[1] == '\0')
		return (REDIRECT_IN);
	if (strcmp(str, "<<") == 0)
		return (REDIRECT_HEREDOC);
	if (str[0] == '>' && str[1] == '\0')
		return (REDIRECT_OUT);
	if (strcmp(str, ">>") == 0)
		return (REDIRECT_APPEND);
	return (CMD);
}

bool	lexer(t_shell *shell, t_token **token, char *line)
{
	int		i;
	int		j;
	char	**tmp;
	char	**split;

	i = 0;
	j = 0;
	tmp = split_by_spaces(line);
	if (!tmp)
		return (false);
	while (tmp[i])
	{
		split = split_pipe_word(tmp[i]);
		j = 0;
		while (split[j])
		{
			add_token(token, check_type(split[j]), ft_strdup(split[j]), 0);
			j++;
		}
		free_split(split);
		i++;
	}
	free_split(tmp);
	split_redirect_word(token);
	return (true);
}

// print_token(*token);