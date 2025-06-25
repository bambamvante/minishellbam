/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 05:04:28 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:53:31 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_before_add_env(char *name, char *value)
{
	int		i;
	int		status;

	i = 0;
	status = 0;
	while (name[i] && (ft_isalpha(name[0]) || name[0] == '_') \
&& (ft_isalpha(name[i]) || ft_isalnum(name[i]) || name[0] == '_'))
		i++;
	if (!name[i])
		add_env(name, value);
	else
	{
		pnf_fd(2, "bash: export: `%s': not a valid identifier\n", name);
		*get_code() = 1;
	}
}

static bool	check(char **arg, int i)
{
	char	*temp;

	if (ft_strchr(arg[i], '=') != NULL && ft_strlen(arg[i]) >= 2)
	{
		temp = ft_strtrim(arg[i], "=");
		if (!*temp)
		{
			free(temp);
			return (false);
		}
		return (true);
	}
	return (false);
}

void	set_export(char **arg)
{
	int		i;
	char	**temp;
	char	*sub;

	i = 1;
	while (arg[i])
	{
		if (check(arg, i))
		{
			temp = ft_split(arg[i], '=');
			if (ft_strchr(temp[0], '=') != NULL)
			{
				sub = ft_substr(temp[0], 0, ft_strlen(arg[i]) - 1);
				add_env(sub, "");
				free(sub);
			}
			else
				check_before_add_env(temp[0], temp[1]);
			free_split(temp);
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
