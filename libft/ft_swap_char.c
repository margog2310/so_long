/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:22:15 by mganchev          #+#    #+#             */
/*   Updated: 2024/04/23 18:21:38 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap_char(char *a, char *b)
{
	char	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
