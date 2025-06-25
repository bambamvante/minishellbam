/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_t.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:25:27 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/26 02:41:11 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*get_code(void)
{
	static int	status = 0;

	return (&status);
}

int	*std_in(void)
{
	static int	fd = -10;

	if (fd == -10)
		fd = dup(0);
	return (&fd);
}
 