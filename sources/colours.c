/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 22:24:19 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/18 00:51:27 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	gen_trgb(int opacity, int red, int green, int blue)
{
	if (opacity > 255 || red > 255 || green > 255 || blue > 255)
		return (0);
	return (opacity << 24 | red << 16 | green << 8 | blue);
}

int	get_opacity(int trgb)
{
	return ((trgb >> 24) & 0XFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0XFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0XFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
