/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 05:04:28 by knakto            #+#    #+#             */
/*   Updated: 2025/06/28 02:19:19 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_before_add_env(char *name, char *value)
{
	int		i;

	if (!name || !name[0])
	{
		pnf_fd(2, "bash: export: `%s': not a valid identifier\n", name);
		*get_code() = 1;
		return ;
	}
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
	{
		pnf_fd(2, "bash: export: `%s': not a valid identifier\n", name);
		*get_code() = 1;
		return ;
	}
	i = 1;
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
		{
			pnf_fd(2, "bash: export: `%s': not a valid identifier\n", name);
			*get_code() = 1;
			return ;
		}
		i++;
	}
	add_env(name, value);
}


static bool	check(char *arg)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign && (equal_sign != arg))
		return (true);
	return (false);
}


void	set_export(char **arg)
{
	int		i;
	char	*equal_pos;
	char	*name;
	char	*value;

	i = 1;
	while (arg[i])
	{
		if (check(arg[i]))
		{
			equal_pos = ft_strchr(arg[i], '=');
			name = ft_substr(arg[i], 0, equal_pos - arg[i]);
			value = ft_strdup(equal_pos + 1);
			check_before_add_env(name, value);
			free(name);
			free(value);
		}
		else
			check_before_add_env(arg[i], NULL);
		i++;
	}
}


void	ft_export(char **arg)
{
	if (len_arg(arg) == 1)
	{
		print_env_list();
		exit(127);
	}
	set_export(arg);
}
