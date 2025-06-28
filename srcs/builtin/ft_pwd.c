/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:55:23 by knakto            #+#    #+#             */
/*   Updated: 2025/06/29 00:52:13 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	thispath[1024];

	if (!getcwd(thispath, sizeof(thispath)))
		exit(1);
	pnf("%s\n", thispath);
	exit(0);
}
