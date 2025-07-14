/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:56:32 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/17 11:56:50 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = 0;
	new->content = content;
	return (new);
}

/* int main(void)
{
    int *sample = malloc(sizeof(int));
    *sample = 42;

    t_list *new = ft_lstnew(sample);
    if (new)
    {
        printf("Content: %d\n", *(int *)new->content);
        printf("Next: %p\n", (void *)new->next);
    }
    else
        printf("Failed to alloc memory for new");
    free(sample);
    free(new);
    return (0);
} */
