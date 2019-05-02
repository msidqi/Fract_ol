/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keyboard_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 04:38:36 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/02 04:38:38 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void		key_press_color(int key_code, t_data *data)
{
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
}

static void		key_press_set(int key_code, t_data *data)
{
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
}

int				key_press(int key_code, t_data *data)
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
	key_press_set(key_code, data);
	key_press_color(key_code, data);
	if (key_code == 37)
		data->islocked = data->islocked ? false : true;
	if (key_code == 15)
		ft_init_fractal(data);
	ft_fractal_choice(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}
