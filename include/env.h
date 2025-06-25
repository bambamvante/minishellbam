/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:22:59 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:11:04 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <unistd.h>
# include <stdlib.h>
# include "KML/include/kml.h"
# include "exit.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

char	***env(void);
t_env	**get_t_env(void);
t_env	*new_env(char *key, char *value);
void	init_env(char **env);
void	print_env(void);
void	print_env_list(void);
void	set_env(void);
void	add_env(char *key, char *value);
int		search(char *key);
void	del_env(char *key);
void	set_value_env(char *key, char *value);
void	del(t_env *d);
void	clear_env(void);
char	*get_value(char *key);
int		*minishell_pid(void);
int		ft_strcmp(char *s1, char *s2);
int		len_env(void);

#endif
