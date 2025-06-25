/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:03:40 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 03:07:01 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_env(void)
{
	int		i;

	i = 0;
	while (env()[0][i])
		pnf("%s\n", env()[0][i++]);
}

static void	sub_fnc(t_env *low, int *i)
{
	if (low->value)
	{
		if (!*low->value)
			pnf("declare -x %s=\n", low->key);
		else
			pnf("declare -x %s=\"%s\"\n", low->key, low->value);
	}
	else
		pnf("declare -x %s\n", low->key);
	low->index = 1;
	*i += 1;
}

void	print_env_list(void)
{
	int		total;
	t_env	*env;
	t_env	*low;
	int		i;

	total = len_env();
	i = 0;
	while (i < total)
	{
		env = *get_t_env();
		low = NULL;
		while (env)
		{
			if (env->index == -1)
				if (!low || ft_strcmp(env->key, low->key) < 0)
					low = env;
			env = env->next;
		}
		if (low)
			sub_fnc(low, &i);
	}
}
