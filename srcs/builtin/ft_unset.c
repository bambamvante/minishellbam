/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 05:23:32 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:53:39 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_unset(char **arg)
{
	int		i;

	if (len_arg(arg) == 1)
		return ;
	i = 1;
	while (arg[i])
		del_env(arg[i++]);
}
