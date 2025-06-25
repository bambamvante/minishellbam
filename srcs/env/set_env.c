/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:37:47 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 03:07:26 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	len_env_list(void)
{
	t_env	*env;
	int		i;

	env = *get_t_env();
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	set_value_env(char *key, char *value)
{
	t_env	*env;

	if (!key)
		return ;
	env = *get_t_env();
	while (env && ft_strncmp(key, env->key, ft_strlen(key) + 1))
		env = env->next;
	if (ft_strncmp(key, env->key, ft_strlen(key) + 1))
		return ;
	if (env->value)
		free(env->value);
	env->value = NULL;
	if (value)
		env->value = ft_strdup(value);
	set_env();
}

static void	temp_set_env(t_env *env_list, char ***temp, int *i)
{
	char	*block;

	if (env_list->value && env_list->key[0] != '$')
	{
		block = ft_strjoin(env_list->key, "=");
		block = fjoin(block, env_list->value);
		temp[0][*i] = block;
		*i += 1;
	}
}

void	set_env(void)
{
	char	**temp;
	int		len;
	int		i;
	t_env	*env_list;

	if (env()[0] != NULL)
		free_split(env()[0]);
	i = 0;
	len = len_env_list();
	env_list = *get_t_env();
	temp = malloc(sizeof(char *) * (len + 1));
	if (!temp)
		return ;
	while (i <= len)
		temp[i++] = NULL;
	i = 0;
	while (i < len && env_list)
	{
		temp_set_env(env_list, &temp, &i);
		env_list = env_list->next;
	}
	*env() = temp;
}
