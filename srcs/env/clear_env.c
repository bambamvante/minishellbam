/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 23:15:42 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 03:06:39 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	clear_env(void)
{
	t_env	*envp;
	t_env	*temp;

	envp = *get_t_env();
	while (envp)
	{
		temp = envp;
		envp = envp->next;
		del(temp);
	}
	free_split(env()[0]);
}
