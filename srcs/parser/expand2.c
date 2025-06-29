/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:58:12 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/29 19:00:53 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_quote_type	check_quote_type(const char *str)
{
	int	len;

	if (!str)
		return (NO_QUOTE);
	len = ft_strlen(str);
	if (len >= 2)
	{
		if (str[0] == '\'' && str[len - 1] == '\'')
			return (SINGLE_QUOTE);
		if (str[0] == '\"' && str[len - 1] == '\"')
			return (DOUBLE_QUOTE);
	}
	return (NO_QUOTE);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

