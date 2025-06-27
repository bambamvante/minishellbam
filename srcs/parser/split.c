/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 19:35:34 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/28 03:37:08 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
