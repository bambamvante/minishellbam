/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:12:09 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/25 01:01:49 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_token_before(t_token **head, t_token *target, char *value,
		t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(value);
		return ;
	}
	new->value = value;
	new->type = type;
	new->prev = target->prev;
	new->next = target;
	if (target->prev)
		target->prev->next = new;
	else
		*head = new;
	target->prev = new;
}

void	remove_token(t_token **token, t_token *target)
{
	if (!token || !*token || !target)
		return ;
	if (target->prev)
		target->prev->next = target->next;
	else
		*token = target->next;
	if (target->next)
		target->next->prev = target->prev;
	free(target->value);
	free(target);
}

int	redirect_operator_len(char *str)
{
	if (strncmp(str, "<<", 2) == 0)
		return (2);
	if (strncmp(str, ">>", 2) == 0)
		return (2);
	if (*str == '<' || *str == '>')
		return (1);
	return (0);
}

t_redirect_type	redirect_type_from_value(char *value)
{
	if (!value)
		return (READ_FILE);
	if (ft_strncmp(value, "<<", 3) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(value, ">>", 3) == 0)
		return (APPEND_FILE);
	else if (ft_strncmp(value, ">", 2) == 0)
		return (WRITE_FILE);
	else if (ft_strncmp(value, "<", 2) == 0)
		return (READ_FILE);
	return (READ_FILE);
}
