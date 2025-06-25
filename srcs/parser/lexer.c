/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:06:42 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/26 03:46:39 by arphueng         ###   ########.fr       */
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

char	**split_by_pipe(char *line)
{
	return (ft_split(line, '|'));
}


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
	tmp = ft_split(split, ' ');
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

bool	lexer(char *line, int i)
{
	char		*no_whitespaces;
	char		**split;
	t_process	*proc;
	t_process	**proc_list;
	char		**tmp;

	proc_list = get_t_process();
	split = split_by_pipe(line);
	if (!split)
		return (false);
	while (split[i])
	{
		proc = init_process();
		if (!proc || !(proc->cmd = split_cmd_and_redirect(split[i],
					&proc->redirect, tmp)))
		{
			free(proc);
			free_split(split);
			return (false);
		}
		add_process(proc_list, proc);
		i++;
	}
	free_split(split);
	return (true);
}
