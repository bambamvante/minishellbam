/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 01:00:48 by knakto            #+#    #+#             */
/*   Updated: 2025/06/29 12:11:58 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sig_set_null(int sig)
{
	int	devnull;

	(void)sig;
	devnull = open("/dev/null", O_RDONLY);
	dup2(devnull, STDIN_FILENO);
	close(devnull);
	*sig_status() = 2;
}

void	signal_prompt(int sig)
{
	(void)sig;

	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
