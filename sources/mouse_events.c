/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: margo <margo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:32:45 by mganchev          #+#    #+#             */
/*   Updated: 2024/05/31 02:03:20 by margo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mouse_event(int button, int x, int y, void *param)
{
	(void)x;
	(void)y;
	(void)param;
	return (ft_putnbr_fd(button, 1));
}

int	on_keypress(int keysym, t_game *img)
{
	(void)img;
	printf("Pressed key: %d\n", keysym);
	return (0);
}
