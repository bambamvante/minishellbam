/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:01:12 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/29 15:08:49 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_redirect_token(char *token)
{
	if (!token)
		return (false);
	if (ft_strncmp(token, "<", 2) == 0 && token[1] == '\0')
		return (true);
	if (ft_strncmp(token, "<<", 3) == 0 && !is_in_quote(token))
		return (true);
	if (ft_strncmp(token, ">", 2) == 0 && token[1] == '\0')
		return (true);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (true);
	return (false);
}

t_redirect_type	get_redirect_type(char *token)
{
	if (!token)
		return (-1);
	if (ft_strncmp(token, "<<", 3) == 0)
		return (HERE_DOC);
	if (ft_strncmp(token, ">>", 3) == 0)
		return (APPEND_FILE);
	if (ft_strncmp(token, "<", 2) == 0)
		return (READ_FILE);
	if (ft_strncmp(token, ">", 2) == 0)
		return (WRITE_FILE);
	return (-1);
}


t_redirect	*init_redirect(t_redirect_type type, char *value)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->value = value;
	redir->next = NULL;
	return (redir);
}

void	add_redirect(t_redirect **redir_list, t_redirect *new_redir)
{
	t_redirect	*tmp;

	if (!redir_list || !new_redir)
		return ;
	if (*redir_list == NULL)
		*redir_list = new_redir;
	else
	{
		tmp = *redir_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redir;
	}
}

