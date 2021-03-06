/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marlene <marlene@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 13:16:41 by marlene           #+#    #+#             */
/*   Updated: 2022/07/13 13:37:37 by marlene          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	quick_sort(t_stack *stack_a, t_stack *stack_b)
{
	int	c;
    
	if (stack_b->size <= get_sort_simple_treshold())
	{
        while (stack_b->size > 0)
        {
            push_min(stack_b, stack_a);
            rotate(*stack_a);
        }
	}
	else
	{
		c = partition(stack_b, stack_a);
		quick_sort(stack_a, stack_b);
        push_n(stack_a, stack_b, c);
		quick_sort(stack_a, stack_b);
	}
}

int	get_pivot_index(t_stack stack_to_sort)
{
	double	diff;
	double	min_diff;
	int		min_diff_index;
	int		i;
	double	mean;

	diff = 0.0;
	i = 0;
	min_diff = 2147483647.0;
	mean = get_mean(stack_to_sort);
	while (i < stack_to_sort.size)
	{
	diff = mean - (double)get(stack_to_sort, i);
		if (diff < 0.0)
			diff *= -1.0;
		if (diff < min_diff)
		{
			min_diff = diff;
			min_diff_index = i;
		}
	i++;
	}
	return (min_diff_index);
}

int get_median(t_stack stack)
{
    int i;
    int j;
    int nb_smaller;
    int nb_larger;

    i = 0;
    while (i < stack.size)
    {
        j = 0;
        nb_smaller = 0;
        nb_larger = 0;
        while (j < stack.size)
        {
            if (i != j && get(stack, i) > get(stack, j))
                nb_smaller++;
            else if (i != j)
                nb_larger++;
            j++;
        }
        if ((nb_larger - nb_smaller) >= -1 && (nb_larger - nb_smaller) <= 1)
            return(get(stack, i));
        i++;
    }
    return (-1);
}

int get_first_index_larger(t_stack stack_to_sort, int value)
{
    int i;

    i = 0;
    while (i < stack_to_sort.size - 1)
    {
        if (get(stack_to_sort, i) > value)
            return (i);
        i++;
    }
    return (-1);
}

int partition(t_stack *stack_to_sort, t_stack *stack_buffer)
{
    int first_index_larger;
    int count;
    int pivot;

    pivot = get_median(*stack_to_sort);
    first_index_larger = get_first_index_larger(*stack_to_sort, pivot);;
    count = 0;
    while (first_index_larger != -1)
    {
        push_index(stack_to_sort, stack_buffer, first_index_larger);
        first_index_larger = get_first_index_larger(*stack_to_sort, pivot);
        count++;
    }
    return (count);
}