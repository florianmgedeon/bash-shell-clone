/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:11:15 by aszabo            #+#    #+#             */
/*   Updated: 2023/09/18 11:11:21 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (new)
	{
		if (!*lst)
		{
			*lst = new;
			return ;
		}
		temp = ft_lstlast(*lst);
		temp->next = new;
	}
}

/* int main(void)
{
    t_list *head = NULL;

    for (int i = 1; i <= 5; i++)
    {
        int *content = malloc(sizeof(int));
        *content = i;

        t_list *new = malloc(sizeof(t_list));
        new->content = content;
        new->next = NULL;

        ft_lstadd_back(&head, new);
    }
    printf("The contents of the list: \n");
    t_list *curr = head;
    while (curr != NULL)
    {
        printf("%d ", *(int *)curr->content);
        curr = curr->next;
    }
    printf("\n");
    while (head != NULL)
    {
        t_list *temp = head;
        head = head->next;
        free(temp->content);
        free(temp);
    }
    return (0);
} */