/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 01:15:16 by knakto            #+#    #+#             */
/*   Updated: 2025/06/26 02:10:40 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <stdbool.h>
# include <stdlib.h>

int		*get_code(void);
int		*std_in(void);
bool	is_exit(int num);

#endif
