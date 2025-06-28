/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:06:42 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/28 23:58:14 by arphueng         ###   ########.fr       */
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

char	**split_cmd_and_redirect(char *split, t_redirect **redir_list,
	char **tmp)
{
	char	**token;
	char	**cmd;
	int		cmd_count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = NULL;
	cmd_count = 0;
	tmp = split_with_quotes(split, 0, 0);
	if (!tmp)
		return (NULL);
	token = split_token_redirect(tmp);
	free_split(tmp);
	if (!token)
		return (NULL);
	parse_redirect(token, redir_list);
	cmd = parse_cmd(token, i, j, cmd_count);
	free_split(token);
	return (cmd);
}

bool	process_cmd(t_process **proc_list, char *split)
{
	t_process	*proc;

	proc = init_process();
	if (!proc)
		return (false);
	proc->cmd = split_cmd_and_redirect(split, &proc->redirect, NULL);
	if (!proc->cmd)
	{
		free(proc);
		return (false);
	}
	add_process(proc_list, proc);
	return (true);
}

bool	lexer(char *line, int i)
{
	char		**split;
	t_process	**proc_list;
	char		*trimmed;

	proc_list = get_t_process();
	split = ft_split(line, '|');
	if (!split)
		return (false);
	while (split[i])
	{
		trimmed = ft_strtrim(split[i], " \t\n");
		if (!trimmed || !process_cmd(proc_list, trimmed))
		{
			free(trimmed);
			free_split(split);
			clear_t_process();
			return (false);
		}
		free(trimmed);
		i++;
	}
	free_split(split);
	return (true);
}
