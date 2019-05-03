/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractal_sets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 03:10:01 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/02 03:10:02 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int			tricorn(t_data *data, double c_x, double c_y)
{
	double	real;
	double	imaginary;
	double	tmpreal;
	int		i;

	i = 0;
	imaginary = 0;
	real = 0;
	while (i < data->max_iter)
	{
		tmpreal = real * real - imaginary * imaginary + c_x;
		imaginary = -2 * real * imaginary + c_y;
		real = tmpreal;
		if (real * real + imaginary * imaginary > 4)
			return (i);
		i++;
	}
	return (0);
}

int			mandelbrot_set(t_data *data, double c_x, double c_y)
{
	double	real;
	double	imaginary;
	double	tmpreal;
	int		i;

	i = 0;
	imaginary = 0;
	real = 0;
	while (i < data->max_iter)
	{
		tmpreal = real * real - imaginary * imaginary + c_x;
		imaginary = 2 * real * imaginary + c_y;
		real = tmpreal;
		if (real * real + imaginary * imaginary > 4)
			return (i);
		i++;
	}
	return (0);
}

int			burning_ship(t_data *data, double c_x, double c_y)
{
	double	real;
	double	imaginary;
	double	tmpreal;
	int		i;

	i = 0;
	imaginary = 0;
	real = 0;
	while (i < data->max_iter)
	{
		tmpreal = ABS(real * real - imaginary * imaginary + c_x);
		imaginary = ABS(2 * real * imaginary + c_y);
		real = tmpreal;
		if (real * real + imaginary * imaginary > 4)
			return (i);
		i++;
	}
	return (0);
}

int			julia_set(t_data *data, double real, double imaginary)
{
	double	c_x;
	double	c_y;
	double	tmpreal;
	int		i;

	c_x = data->juliapos.x;
	c_y = data->juliapos.y;
	i = 0;
	while (i < data->max_iter)
	{
		tmpreal = real * real - imaginary * imaginary + c_x;
		imaginary = 2 * real * imaginary + c_y;
		real = tmpreal;
		if (real * real + imaginary * imaginary > 4)
		{
			return (i);
		}
		i++;
	}
	return (0);
}

void		sierpinski_triangle(t_data *data, int max_iter)
{
	int		corner;
	t_point	points[4];

	ft_init_sierpinski(data, points);
	while (max_iter--)
	{
		if (!(corner = rand() % 3))
		{
			points[3].x = lerp(points[3].x, points[0].x, (double)0.5);
			points[3].y = lerp(points[3].y, points[0].y, (double)0.5);
		}
		else if (corner == 1)
		{
			points[3].x = lerp(points[3].x, points[1].x, (double)0.5);
			points[3].y = lerp(points[3].y, points[1].y, (double)0.5);
		}
		else
		{
			points[3].x = lerp(points[3].x, points[2].x, (double)0.5);
			points[3].y = lerp(points[3].y, points[2].y, (double)0.5);
		}
		ft_image_fill(data, points[3].x, points[3].y, 0xFF0000);
	}
}
