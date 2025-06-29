/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 19:22:40 by knakto            #+#    #+#             */
/*   Updated: 2025/06/29 12:14:41 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <unistd.h>
# include <sys/wait.h>
# include "KML/include/kml.h"
# include "env.h"
# include "exit.h"
# include "process.h"

typedef struct s_process	t_process;

typedef enum e_use_function
{
	FT_CD,
	FT_PWD,
	FT_ENV,
	FT_ECHO,
	FT_EXPORT,
	FT_UNSET,
	FT_EXIT,
}	t_use_function;

int		builtin(t_process *proc);
int		len_arg(char **arg);
void	ft_chdir(char **arg);
void	ft_echo(char **arg);
void	ft_pwd(char **arg);
void	ft_env(char **arg);
void	ft_export(char **arg);
void	ft_unset(char **arg);
void	redirect(t_process *proc);
void	clear_t_process(void);
void	ft_exit(char **arg);

#endif
