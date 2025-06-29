/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <knakto@student.42bangkok.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 01:43:30 by knakto            #+#    #+#             */
/*   Updated: 2025/04/29 19:08:29 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_arg(char **arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		pnf("%s", arg[i]);
		if (arg[i + 1])
			pnf(" ");
		i++;
	}
}

void	ft_echo(char **arg)
{
	if (len_arg(arg) == 1)
		pnf("\n");
	else if (len_arg(arg) > 2)
	{
		if (!ft_strncmp(arg[1], "-n", 3))
			print_arg(&arg[2]);
		else
		{
			print_arg(&arg[1]);
			pnf("\n");
		}
	}
	else
	{
		print_arg(&arg[1]);
		pnf("\n");
	}
	exit(0);
}
