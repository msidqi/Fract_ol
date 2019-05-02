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

int		mouse_move(int x, int y, t_data *data)
{
	ft_refresh_image(data);
	if (!data->isLocked)
	{
		data->juliaPos.x = (double)(x * 1.5) / data->winwidth;
		data->juliaPos.y = (double)(y * 1.5) / data->winheight;
	}
	data->winPos.x = (double)x;
	data->winPos.y = (double)y;
	ft_fractal_choice(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}

int		mouse_press(int button, int x, int y, t_data *data)
{
	double	oldzoom;

	(void)x;
	(void)y;
	ft_refresh_image(data);
	if (button == LEFT_CLICK)
		data->max_iter += 10;
	else if (button == RIGHT_CLICK)
		data->max_iter -= 10;
	if (button == SCROLL_UP)
	{
		oldzoom = data->zoom;
		data->zoom *= 1.3;
		data->movex += (data->winPos.x - data->winwidth / 2) / data->zoom
					- (data->winPos.x - data->winwidth / 2) / (oldzoom);
		data->movey += (data->winPos.y - data->winheight / 2) / data->zoom
					- (data->winPos.y - data->winheight / 2) / (oldzoom);
	}
	else if (button == SCROLL_DOWN)
	{
		if (data->zoom <= 1)
			data->zoom = 1;
		else
		{
			oldzoom = data->zoom;
			data->zoom *= 0.7;
			data->movex -= (data->winPos.x - data->winwidth / 2) / data->zoom
						- (data->winPos.x - data->winwidth / 2) / (oldzoom);
			data->movey -= (data->winPos.y - data->winheight / 2) / data->zoom
						- (data->winPos.y - data->winheight / 2) / (oldzoom);
		}
	}
	ft_fractal_choice(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}

int		key_press(int key_code, t_data *data)
{
	if (key_code == 53)
	{
		mlx_destroy_image(data->mlx, data->img_ptr);
		free(data);
		data = NULL;
		exit(0);
	}
	ft_refresh_image(data);
	if (key_code == LEFT_ARROW)
		data->movex += -data->winwidth / 10 / (data->zoom);
	else if (key_code == RIGHT_ARROW)
		data->movex -= -data->winwidth / 10 / (data->zoom);
	if (key_code == UP_ARROW)
		data->movey += -data->winheight / 10 / (data->zoom);
	else if (key_code == DOWN_ARROW)
		data->movey -= -data->winheight / 10 / (data->zoom);
	if (key_code == 91)
		data->max_iter += 10;
	else if (key_code == 89)
		data->max_iter -= 10;
	if (key_code == 8)
	{
		if (data->color.red)
		{
			data->color.red = 0;
			data->color.green = 255;
		}
		else if (data->color.green)
		{
			data->color.green = 0;
			data->color.blue = 255;
		}
		else
		{
			data->color.red = 255;
			data->color.blue = 0;
		}
	}
	if (key_code == 1)
	{
		if (data->set == 'm')
			data->set = 'j';
		else if (data->set == 'j')
			data->set = 's';
		else if (data->set == 's')
			data->set = 'b';
		else
			data->set = 'm';
	}
	if (key_code == 37)
		data->isLocked = data->isLocked ? false : true;
	if (key_code == 15)
		ft_init_fractal(data);
	ft_fractal_choice(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}
