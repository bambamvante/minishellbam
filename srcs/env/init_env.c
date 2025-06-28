/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:39:10 by knakto            #+#    #+#             */
/*   Updated: 2025/06/29 00:52:06 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_env	*get_node(char **env, int i)
{
	char	*key;
	char	*value;
	t_env	*node;
	int		j;

	node = NULL;
	if (ft_strchr(env[i], '=') == NULL)
		node = new_env(env[i], NULL);
	else
	{
		j = 0;
		while (env[i][j] != '=')
			j++;
		key = ft_substr(env[i], 0, j);
		value = ft_strchr(env[i], '=') + 1;
		node = new_env(key, value);
		free(key);
	}
	return (node);
}

void	set_shell_level(void)
{
	t_env	*env;
	int		num;
	char	*val;

	env = *get_t_env();
	while (env)
	{
		if (!ft_strncmp(env->key, "SHLVL", 6))
		{
			if (!env->value)
				env->value = ft_strdup("1");
			else
			{
				num = ft_atoi(env->value);
				if (num < 0)
					val = ft_strdup("0");
				else
					val = ft_itoa(num + 1);
				free(env->value);
				env->value = val;
			}
			return ;
		}
		env = env->next;
	}
}

void	shell_level(void)
{
	if (!search("SHLVL"))
	{
		add_env("SHLVL", "1");
		return ;
	}
	set_shell_level();
}

void	set_minishell_pid(void)
{
	*minishell_pid() = 112548;
}

void	init_env(char **env)
{
	int		i;
	t_env	*node;
	t_env	*current;

	i = 0;
	while (env[i])
	{
		if (i == 0)
		{
			node = get_node(env, i);
			*get_t_env() = node;
			current = node;
		}
		else
		{
			current->next = get_node(env, i);
			current = current->next;
		}
		i++;
	}
	shell_level();
	set_minishell_pid();
	set_env();
}
