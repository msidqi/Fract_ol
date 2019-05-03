/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 04:51:26 by msidqi            #+#    #+#             */
/*   Updated: 2019/05/02 05:05:36 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"
#include "libft.h"

void			ft_init_fractal(t_data *data)
{
	data->movex = 0;
	data->movey = 0;
	data->zoom = data->winwidth / 4;
	data->max_iter = MAX_ITER;
	data->islocked = false;
	data->color.red = 255;
	data->color.green = 0;
	data->color.blue = 255;
}

double			lerp(double x1, double x2, double lerp)
{
	return (x1 * (1.0 - lerp)) + (x2 * lerp);
}

/*
** color is 0x00RRGGBB         change 00 for opacity
** 0x330033 dark-purple
** 0x3300DD p-blue
** z = 0;
** z' = z*z + c; ==> z' = c;
**
** z'' = z*z + c; ==> z'' = (a+bi)(a+bi) + c
**                        = a*a - b*b + 2bi  + c
** 					     ( real  ) + (imaginary)
**
** 						so to draw in the complex plane
**
** >real part a:
** x = a*a - b*b + x(real part of c, which is x of the point
**	that we're currently iterating on)
**
** >imaginary part b:
** x = 2bi + y(imaginary part of c, which is y of the point
** that we're currently iterating on)
*/

int				ft_input_check(t_data *data, int argc, char **argv)
{
	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "Julia"))
			data->set = 'j';
		else if (!ft_strcmp(argv[1], "Mandelbrot"))
			data->set = 'm';
		else if (!ft_strcmp(argv[1], "Sierp"))
			data->set = 's';
		else if (!ft_strcmp(argv[1], "Burning"))
			data->set = 'b';
		else if (!ft_strcmp(argv[1], "Tric"))
			data->set = 't';
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

/*
**	The Mandelbrot set is the set of complex numbers c for which the sequence :
**	Z0 = 0
**	Zn = Zn-1 + c
**	converges.
**
**	The Mandelbrot set:
**	is a picture in parameter space
**	records the fate of the orbit of 0
**
**	The filled Julia set
**	is a picture in dynamical plane
**	records the fate of all orbits
**
**	interfaceUI(data);
**	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
**	interfacetext(data); // should be after put_image because
** the str is not included in the image char *
*/

static void		ft_print_instructions(void)
{
	ft_putendl(" ___________________________________________________________");
	ft_putendl("| Arrows :      Move                                        |");
	ft_putendl("| S :           Switch fractal                              |");
	ft_putendl("| R :           Reset values                                |");
	ft_putendl("| L :           Lock Julia set                              |");
	ft_putendl("| C :           Change color                                |");
	ft_putendl("| Mouse wheel : Zoom                                        |");
	ft_putendl("| L/R click :   Increace/Decrease iteration                 |");
	ft_putendl(" -----------------------------------------------------------");
}

int				main(int argc, char **argv)
{
	t_data	*data;
	char	*s;

	s = ft_strdup("Usage: ./fractol [Mandelbrot][Julia][Sierp][Burning][Tric]");
	srand(time(NULL));
	if (!(data = malloc(sizeof(t_data))))
		return (0);
	if (!ft_input_check(data, argc, argv))
	{
		ft_putendl(s);
		free(data);
		data = NULL;
		free(s);
		s = NULL;
		return (0);
	}
	if (!(ft_window_setup(data, "Fract'ol", 600, 600)) || !ft_image_setup(data))
		return (0);
	ft_init_fractal(data);
	ft_fractal_choice(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	ft_print_instructions();
	ft_mlx_hooks(data);
	return (0);
}
