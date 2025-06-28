/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:25:53 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/28 12:43:07 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	*get_is_double_quote(void)
{
	static bool	is_double_quote;

	return (&is_double_quote);
}

static bool	*get_is_single_quote(void)
{
	static bool	is_single_quote;

	return (&is_single_quote);
}

void	init_check_quote(void)
{
	*get_is_single_quote() = false;
	*get_is_double_quote() = false;
}

bool	check_quote(char c)
{
	bool	in_single;
	bool	in_double;

	in_single = *get_is_single_quote();
	in_double = *get_is_double_quote();
	if (c == '\'' && !in_double)
		in_single = !in_single;
	else if (c == '\"' && !in_single)
		in_double = !in_double;
	*get_is_single_quote() = in_single;
	*get_is_double_quote() = in_double;
	return (!(in_single || in_double));
}

