/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 03:13:04 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/02 03:13:05 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int			mouse_move(int x, int y, t_data *data)
{
	ft_refresh_image(data);
	if (!data->islocked)
	{
		data->juliapos.x = (double)(x * 1.5) / data->winwidth;
		data->juliapos.y = (double)(y * 1.5) / data->winheight;
	}
	data->winpos.x = (double)x;
	data->winpos.y = (double)y;
	ft_fractal_choice(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}

static void	mouse_press_scroll(int button, t_data *data)
{
	double	oldzoom;

	if (button == SCROLL_UP)
	{
		oldzoom = data->zoom;
		data->zoom *= 1.3;
		data->movex += (data->winpos.x - data->winwidth / 2) / data->zoom
					- (data->winpos.x - data->winwidth / 2) / (oldzoom);
		data->movey += (data->winpos.y - data->winheight / 2) / data->zoom
					- (data->winpos.y - data->winheight / 2) / (oldzoom);
	}
	else if (button == SCROLL_DOWN)
	{
		if (data->zoom <= 1)
			data->zoom = 1;
		else
		{
			oldzoom = data->zoom;
			data->zoom *= 0.7;
			data->movex -= (data->winpos.x - data->winwidth / 2) / data->zoom
						- (data->winpos.x - data->winwidth / 2) / (oldzoom);
			data->movey -= (data->winpos.y - data->winheight / 2) / data->zoom
						- (data->winpos.y - data->winheight / 2) / (oldzoom);
		}
	}
}

int			mouse_press(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	ft_refresh_image(data);
	if (button == LEFT_CLICK)
		data->max_iter += 10;
	else if (button == RIGHT_CLICK)
		data->max_iter -= 10;
	mouse_press_scroll(button, data);
	ft_fractal_choice(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}
