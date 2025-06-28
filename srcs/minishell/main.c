/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 11:07:19 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/29 00:50:28 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_shell(t_shell *shell)
{
	shell->line = NULL;
	shell->tmp = NULL;
}

void	minishell(t_shell *shell)
{
	while (is_exit(0))
	{
		dup2(*std_in(), 0);
		shell->tmp = readline("minishell$ ");
		if (!shell->tmp)
			break ;
		shell->line = ft_strtrim(shell->tmp, " ");
		free(shell->tmp);
		shell->tmp = NULL;
		if (!shell->line)
			break ;
		if (*shell->line)
		{
			add_history(shell->line);
			parser(shell);
			process();
			clear_t_process();
		}
		free(shell->line);
	}
	close(*std_in());
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	t_shell		shell;

	(void)ac;
	(void)av;
	init_env(envp);
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, signal_reset_prompt);
	minishell(&shell);
	clear_t_process();
	clear_env();
	return (*get_code());
}
