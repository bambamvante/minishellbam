/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:03:34 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/25 00:58:57 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

void	print_token(t_token *token_list)
{
	int	pos;

	pos = 0;
	t_token *curr = token_list;

    while (curr)
    {
        printf("pos: %d | type: %d | redirect_type: %d | value: [%s]\n",
               pos, curr->type, curr->redirect_type, curr->value);
        curr = curr->next;
        pos++;
    }
}
