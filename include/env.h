/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 17:21:36 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/24 17:22:09 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <unistd.h>
# include <stdlib.h>
# include "KML/include/kml.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

#endif
