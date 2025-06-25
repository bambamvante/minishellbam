/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:22:21 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:53:17 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	set_old_pwd(char *thispath)
{
	set_value_env("OLDPWD", thispath);
	if (!getcwd(thispath, sizeof(thispath)))
		return ;
	set_value_env("PWD", thispath);
}

static void	go_to_home(void)
{
	int		i;

	i = 0;
	while (env()[0][i])
	{
		if (!ft_strncmp(env()[0][i], "HOME=", 5))
			break ;
		i++;
	}
	if (ft_strncmp(env()[0][i], "HOME=", 5))
	{
		pnf_fd(2, "bash: cd: HOME not set\n");
		return ;
	}
	if (chdir(env()[0][i] + 5) != 0)
	{
		pnf("bash: cd: %s: No such file or directory\n", env()[0][i] + 5);
		*get_code() = 1;
	}
	else
		set_env();
}

static char	*absolute_path(char **arg)
{
	int		i;

	if (!ft_strncmp(arg[1], "/", 1))
		return (ft_strdup(arg[1]));
	i = 0;
	while (env()[0][i] && ft_strncmp(env()[0][i], "HOME=", 5))
		i++;
	if (ft_strncmp(env()[0][i], "HOME=", 5))
		pnf_fd(2, "bash: cd: HOME not set\n");
	else
	{
		if (ft_strlen(arg[1]) != 1)
			return (ft_strjoin(env()[0][i] + 5, arg[1] + 1));
		return (ft_strdup(env()[0][i] + 5));
	}
	return (NULL);
}

static void	change_dir(char **arg)
{
	char	thispath[1024];
	char	*nextpath;

	if (!ft_strncmp(arg[1], "/", 1) || !ft_strncmp(arg[1], "~", 1))
	{
		nextpath = absolute_path(arg);
		if (!nextpath)
			return ;
	}
	else
	{
		getcwd(thispath, sizeof(thispath));
		nextpath = ft_strjoin(thispath, "/");
		nextpath = fjoin(nextpath, arg[1]);
	}
	if (chdir(nextpath) != 0)
	{
		pnf_fd(2, "bash: cd: %s: No such file or directory\n", arg[1]);
		*get_code() = 1;
	}
	else
		set_env();
	free(nextpath);
	set_old_pwd(thispath);
}

void	ft_chdir(char **arg)
{
	char	thispath[1024];

	if (len_arg(arg) == 1)
		go_to_home();
	else if (len_arg(arg) > 2)
	{
		pnf_fd(2, "bash: cd: too many arguments\n");
		*get_code() = 1;
	}
	else if (!ft_strncmp(arg[1], "-", 1))
	{
		if (!getcwd(thispath, sizeof(thispath)))
			return ;
		pnf("%s\n", thispath);
	}
	else
		change_dir(arg);
}
