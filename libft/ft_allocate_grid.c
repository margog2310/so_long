/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate_grid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 01:33:32 by margo             #+#    #+#             */
/*   Updated: 2024/05/31 18:59:20 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_allocate_grid(int rows, int cols, size_t size)
{
	int		i;
	int		j;
	void	**grid;

	grid = malloc(rows * sizeof(void *));
	if (grid == NULL)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		grid[i] = malloc(cols * size);
		if (grid[i] == NULL)
		{
			j = 0;
			while (j < i)
				free(grid[j]);
			free(grid);
			return (NULL);
		}
	}
	return (grid);
}
