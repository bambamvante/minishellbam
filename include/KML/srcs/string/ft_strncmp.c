/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 12:15:51 by knakto            #+#    #+#             */
/*   Updated: 2025/06/08 22:38:35 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned char	*first_str;
	unsigned char	*second_str;

	if (!s1 || !s2)
		return (0);
	first_str = (unsigned char *)s1;
	second_str = (unsigned char *)s2;
	while (*first_str && len > 0 && *first_str == *second_str)
	{
		first_str++;
		second_str++;
		len--;
	}
	if (len == 0)
		return (0);
	return (*first_str - *second_str);
}
