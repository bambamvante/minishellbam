/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:41:26 by knakto            #+#    #+#             */
/*   Updated: 2025/06/03 13:05:17 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	error(void)
{
	pnf_fd(2, "bash: exit: too many arguments\n");
	exit(1);
}

static bool	conditions(char **cmd, int i)
{
	return (!(ft_isalnum(cmd[1][i]) || cmd[1][0] == '-' \
|| cmd[1][0] == '+') || ft_isalpha(cmd[1][0]) \
|| cmd[1][1] == '+' || cmd[1][1] == '-');
}

void	ft_exit(char **cmd)
{
	int		code;
	int		status;
	int		i;

	if (!cmd[1])
		is_exit(1);
	else if (cmd[1] && !cmd[2])
	{
		status = 0;
		i = -1;
		while (cmd[1][++i])
			if (conditions(cmd, i))
				status = 1;
		code = ft_atoi(cmd[1]);
		if (status)
			code = 2;
		else if (code >= 256)
			code %= 256;
		else if (code < 0)
			code = (((code * -1) % 256) - 256) * -1;
		*get_code() = code;
	}
	else
		error();
}
