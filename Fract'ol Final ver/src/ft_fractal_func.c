/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractal_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 03:17:26 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/02 03:17:27 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

static void	ft_color_change(int *col, t_data *data)
{
	int				tmp;
	unsigned char	*ptr;

	tmp = *col;
	ptr = (unsigned char*)col;
	ptr[0] = data->color.blue * (tmp) / MAX_ITER;
	ptr[1] = data->color.green * (tmp) / MAX_ITER;
	ptr[2] = data->color.red * (tmp) / MAX_ITER;
}

double		ft_get_world_pos(double screen_coord, double widheight, double zoom)
{
	return (((screen_coord - widheight / 2) / zoom));
}

void		ft_fractal_choice(t_data *data)
{
	if (data->set == 'j' || data->set == 'm' || data->set == 'b'
	|| data->set == 't')
		ft_multi_thread(data, 6);
	else if (data->set == 's')
		sierpinski_triangle(data, 10000000);
}

static int	ft_checkif_in_set(t_data *data, double a, double b)
{
	if (data->set == 'j')
		return (julia_set(data,
			ft_get_world_pos(a, data->winwidth, data->zoom) - data->movex,
			ft_get_world_pos(b, data->winheight, data->zoom) - data->movey));
	else if (data->set == 'm')
		return (mandelbrot_set(data,
			ft_get_world_pos(a, data->winwidth, data->zoom) - data->movex,
			ft_get_world_pos(b, data->winheight, data->zoom) - data->movey));
	else if (data->set == 'b')
		return (burning_ship(data,
			ft_get_world_pos(a, data->winwidth, data->zoom) - data->movex,
			ft_get_world_pos(b, data->winheight, data->zoom) - data->movey));
	else if (data->set == 't')
		return (tricorn(data,
			ft_get_world_pos(a, data->winwidth, data->zoom) - data->movex,
			ft_get_world_pos(b, data->winheight, data->zoom) - data->movey));
		return (0);
}

void		*draw_fractal(void *param)
{
	t_data	*data;
	int		col;
	int		a;
	int		b;

	data = param;
	a = data->thread_range.start.x;
	while (a < data->thread_range.end.x)
	{
		b = data->thread_range.start.y;
		while (b < data->thread_range.end.y)
		{
			if ((col = ft_checkif_in_set(data, (double)a, (double)b)))
			{
				ft_color_change(&col, data);
				ft_image_fill(data, a, b, col);
			}
			b++;
		}
		a++;
	}
	return (NULL);
}
