/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 23:34:55 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 03:06:54 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_value(char *key)
{
	char	*value;
	t_env	*env;

	env = *get_t_env();
	if (key[0] == '$')
		return (ft_itoa(*minishell_pid()));
	if (key[0] == '?')
		return (ft_itoa(*get_code()));
	if (!key || !search(key))
		return (ft_strdup(""));
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(key)))
			if (env->value)
				return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
