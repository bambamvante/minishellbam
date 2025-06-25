/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:51:22 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 03:06:30 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	search(char *key)
{
	t_env	*env;

	env = *get_t_env();
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
			return (1);
		env = env->next;
	}
	return (0);
}

void	add_env(char *key, char *value)
{
	t_env	*env;

	env = *get_t_env();
	if (search(key))
	{
		set_value_env(key, value);
		return ;
	}
	while (env->next)
		env = env->next;
	env->next = new_env(key, value);
	set_env();
}
