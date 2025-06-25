/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 00:49:12 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:47:14 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static bool	access_relative(char *cmd)
{
	if (!access(cmd, X_OK | F_OK))
		return (true);
	return (false);
}

static char	*access_absolute(char *cmd, char *path)
{
	char	**all_path;
	char	*temp;
	int		i;
	bool	status;

	if (cmd[0] == '.' || cmd[0] == '/')
		return (ft_strdup(cmd));
	if (ft_strrchr(cmd, '/') != NULL)
		cmd = ft_strrchr(cmd, '/');
	all_path = ft_split(path, ':');
	i = 0;
	status = false;
	while (all_path[i] && !status)
	{
		temp = ft_strjoin(all_path[i], "/");
		temp = fjoin(temp, cmd);
		if (!access(temp, X_OK | F_OK))
			status = true;
		else
			free(temp);
		i++;
	}
	free_split(all_path);
	if (status)
		return (temp);
	return (NULL);
}

bool	chech_eccess(char ***cmd, char *path)
{
	char	*cmd_path;
	char	*temp;
	bool	relative_status;

	cmd_path = NULL;
	relative_status = access_relative(cmd[0][0]);
	if (!path && !relative_status)
		return (false);
	if (path)
		cmd_path = access_absolute(cmd[0][0], path);
	if (!cmd_path)
	{
		if (relative_status)
			return (true);
		return (false);
	}
	temp = **cmd;
	**cmd = cmd_path;
	free(temp);
	return (true);
}
