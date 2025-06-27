/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:23:32 by knakto            #+#    #+#             */
/*   Updated: 2025/06/27 17:56:09 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	***env(void)
{
	static char	**env = NULL;

	return (&env);
}

t_env	**get_t_env(void)
{
	static t_env	*env;

	return (&env);
}

int	*minishell_pid(void)
{
	static int	pid;

	return (&pid);
}
