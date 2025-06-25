/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 22:34:09 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 03:01:38 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	signal_print_newline(int sig)
{
	(void)sig;
	rl_on_new_line();
}

void	signal_reset_prompt(int sig)
{
	(void)sig;

	pnf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_handle(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
		*sig_status() = 1;
	else if (sig == SIGINT)
		*sig_status() = 2;
}

void	check_sig_status(void)
{
	if (*sig_status() == 1)
	{
		pnf("Coredump\n");
		*get_code() = 128 + SIGQUIT;
	}
	else if (*sig_status() == 2)
	{
		pnf("\n");
		*get_code() = 128 + SIGINT;
	}
	*sig_status() = 0;
}
