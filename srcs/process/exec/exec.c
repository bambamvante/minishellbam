/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 00:21:47 by knakto            #+#    #+#             */
/*   Updated: 2025/06/28 22:26:25 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	chech_eccess(char ***cmd, char *path);
void	clear_execution_failed(char **cmd, char **env);

static char	*get_command_path(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	return (env[i] + 5);
}

static void	throw_error(char **cmd, char **env)
{
	if (!access(cmd[0], X_OK))
	{
		pnf_fd(2, "minishell: %s: Permission denied\n", cmd[0]);
		clear_execution_failed(cmd, env);
		exit(126);
	}
	if (!access(cmd[0], F_OK))
	{
		pnf_fd(2, "bash: %s: No such file or directory\n", cmd[0]);
		clear_execution_failed(cmd, env);
		exit(127);
	}
	pnf_fd(2, "bash: %s: command not found\n", cmd[0]);
	clear_execution_failed(cmd, env);
	exit(127);
}

int is_directory(const char *path) {
    struct stat path_stat;

    if (stat(path, &path_stat) != 0) {
        // stat failed (file doesn't exist etc.)
        return 0;
    }
    return S_ISDIR(path_stat.st_mode);
}

void	exec(char **cmd, char **env)
{
	char	*path;
	bool	status;

	while (!cmd[0][0])
		cmd += 1;
	if (is_directory(cmd[0]))
	{
		pnf_fd(2, "minishell: %s: Is a directory\n", cmd[0]);
		exit(126);
	}
	path = get_command_path(env);
	status = chech_eccess(&cmd, path);
	if (!status)
		throw_error(cmd, env);
	execve(cmd[0], cmd, env);
	throw_error(cmd, env);
}
