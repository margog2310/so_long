/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grid_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:48:57 by mganchev          #+#    #+#             */
/*   Updated: 2024/06/06 18:39:46 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_grid_size(char **grid, int *rows, int *cols)
{
	*rows = 0;
	*cols = 0;
	while (grid[*rows])
		(*rows)++;
	while (grid[0] && grid[0][*cols])
		(*cols)++;
}