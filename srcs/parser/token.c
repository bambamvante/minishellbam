/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:20:43 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/25 01:00:10 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_token	*new_token(t_token_type type, char *str, int quoted)
{
	t_token	*new_token;

	new_token = (t_token *)safealloc(1, sizeof(t_token), 0);
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(str);
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **token, t_token_type type, char *str, int quoted)
{
	t_token	*new;
	t_token	*curr;

	new = new_token(type, str, quoted);
	if (!new)
		return ;
	if (!*token)
	{
		*token = new;
		return ;
	}
	curr = *token;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}
