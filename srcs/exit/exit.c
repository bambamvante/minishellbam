/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:17:17 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/24 11:17:21 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	*ext(void)
{
	static int	ext = 0;

	return (&ext);
}

bool	is_exit(int num)
{
	if (num == 0)
		return (!*ext());
	*ext() = num;
	return (!*ext());
}
