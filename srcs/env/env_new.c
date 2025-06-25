/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:40:44 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 03:06:45 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	if (!key)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->value = NULL;
	if (value)
		env->value = ft_strdup(value);
	env->key = ft_strdup(key);
	env->index = -1;
	env->next = NULL;
	return (env);
}
