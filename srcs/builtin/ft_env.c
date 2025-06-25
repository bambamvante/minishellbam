/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:38:45 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:53:21 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_env(char **arg)
{
	if (len_arg(arg) != 1)
	{
		pnf_fd(2, "bash: env: too many arguments\n");
		exit(127);
	}
	print_env();
	exit(0);
}
