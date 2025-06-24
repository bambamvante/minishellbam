/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 21:27:00 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/25 01:00:22 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_redirect_operator(t_token *token)
{
	if (!token || !token->value)
		return (false);
	if (strncmp(token->value, "<", 1) == 0)
		return (true);
	if (strncmp(token->value, "<<", 2) == 0)
		return (true);
	if (strncmp(token->value, ">", 1) == 0)
		return (true);
	if (strncmp(token->value, ">>", 2) == 0)
		return (true);
	return (false);
}

bool	token_need_split(t_token *token)
{
	char	*str;
	int		i;
	int		len;

	str = token->value;
	i = 0;
	while (str[i])
	{
		len = redirect_operator_len(&str[i]);
		if (len > 0)
		{
			if (i != 0 || str[i + len] != '\0')
				return (true);
			i += len;
		}
		i++;
	}
	return (false);
}

void	remove_empty_or_space_token(t_token **token)
{
	t_token	*curr;
	t_token	*next;

	curr = *token;
	while (curr)
	{
		next = curr->next;
		if (!curr->value || curr->value[0] == '\0' ||
			is_all_space(curr->value))
			remove_token(token, curr);
		curr = next;
	}
}

void	split_token_redirect(t_token *curr, t_token **token)
{
	char	*value;
	int		i;
	int		len;
	char	*left;
	char	*right;
	char	*operator;

	value = curr->value;
	i = 0;
	while (value[i])
	{
		len = redirect_operator_len(&value[i]);
		if (len > 0)
		{
			if (i > 0)
			{
				left = ft_substr(value, 0, i);
				if (!left)
					return ;
				add_token_before(token, curr, left, CMD);
			}
			operator = ft_substr(value, i, len);
			if (!operator)
				return ;
			add_token_before(token, curr, operator, check_type(&value[i]));
			if (value[i + len])
			{
				right = ft_strdup(&value[i + len]);
				if (!right)
					return ;
				add_token_before(token, curr, right, CMD);
			}
			remove_token(token, curr);
			break ;
		}
		i++;
	}
}

void	split_redirect_word(t_token **token)
{
	t_token	*curr;

	curr = *token;
	while (curr)
	{
		if (token_need_split(curr))
		{
			split_token_redirect(curr, token);
			curr = *token;
			continue ;
		}
		curr = curr->next;
	}
	remove_empty_or_space_token(token);
	curr = *token;
	while (curr)
	{
		if (is_redirect_operator(curr))
			curr->redirect_type = redirect_type_from_value(curr->value);
		else if (curr->prev && is_redirect_operator(curr->prev))
			curr->type = CMD;
		curr = curr->next;
	}
}
