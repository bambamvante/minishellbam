/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safealloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arphueng <arphueng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:02:24 by arphueng          #+#    #+#             */
/*   Updated: 2025/06/08 21:03:19 by arphueng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"

/**
* Returns a pointer to a static list that tracks allocated memory pointer.
*
* @param nth_chain An ID for the target tracker to get the tracker head from
*
* @return A pointer to the head of the tracker list.
**/
static t_list	**get_tracker_head(size_t nth_chain)
{
	static t_list	*trackers[MAX_TRACKER_CHAINS] = {0};

	return (&trackers[nth_chain]);
}

/**
* Add a pointer to the static memory pointer list
*
* @param ptr A pointer to be added to the static memory pointer list
**/
static void	track_allocated_ptr(void *ptr, size_t nth_chain)
{
	t_list	**head;

	head = get_tracker_head(nth_chain);
	ft_lstadd_back(head, ft_lstnew(ptr));
}

/**
* Frees all memory that was allocated using `safealloc`.
**/
void	free_safealloc(void)
{
	t_list	**head;
	size_t	nth_chain;

	nth_chain = 0;
	while (nth_chain < MAX_TRACKER_CHAINS)
	{
		head = get_tracker_head(nth_chain);
		if (*head)
			ft_lstclear(head, &free);
		nth_chain++;
	}
}

/**
* @brief 
* 
* @param nth_chain 
**/
void	free_nth_chain(size_t nth_chain)
{
	t_list	**head;

	head = get_tracker_head(nth_chain);
	if (*head)
		ft_lstclear(head, &free);
}

/**
* Allocates memory and tracks the allocated pointer
* which can be free with `free_safealloc`.
*
* If allocation fails, all memory allocated with `safealloc` will be free
* and will exit form the execution with exit status `1`.
*
* @param count Number of elements to allocate.
* @param size Size of each element.
* @param nth_chain An ID for the target tracker to track on.
* @return Pointer to the allocated memory block.
**/
void	*safealloc(size_t count, size_t size, size_t nth_chain)
{
	void	*ptr;

	if (nth_chain >= MAX_TRACKER_CHAINS)
	{
		ft_putendl_fd("Error: nth_chain exceeds max tracker chain limit.",
			STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		free_safealloc();
		ft_putendl_fd("Error: safealloc failed.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	track_allocated_ptr(ptr, nth_chain);
	return (ptr);
}
