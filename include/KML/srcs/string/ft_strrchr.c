/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knakto <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 21:22:19 by knakto            #+#    #+#             */
/*   Updated: 2025/04/04 19:21:13 by knakto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	*ptr;

	if (!s)
		return (NULL);
	ptr = (char *)s;
	len = 0;
	while (*(s + len))
		len++;
	i = len;
	if (c == 0)
		return (ptr + i);
	while (0 <= i)
	{
		if (*(s + i) == (unsigned char)c)
			return (ptr + i);
		i--;
	}
	return (0);
}
