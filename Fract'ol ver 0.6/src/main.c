/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 04:51:26 by msidqi            #+#    #+#             */
/*   Updated: 2019/02/04 04:54:56 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"
#include "libft.h"

double		ft_get_worldPos(double screen_coordinate, double winwidthOrheight, double zoom)
{
	return (((screen_coordinate - winwidthOrheight/2) / zoom));
}

// double interpolate(double start, double end, double interpolation)
// {
//     return start + ((end - start) * interpolation);
// }

double lerp(double x1, double x2, double lerp)
{
	return (x1 * (1.0 - lerp)) + (x2 * lerp);
}

int red_button(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img_ptr);
	free(data);
	data = NULL;
    exit(0);
    return (0);
}

void	ft_refresh_image(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img_ptr);
	data->img_ptr = mlx_new_image(data->mlx, data->winwidth,data->winheight);
	data->image = (int *)mlx_get_data_addr(data->img_ptr, &data->bpp, &data->size_line, &data->endian);
}

void	ft_init_fractal(t_data *data)
{
	data->movex = 0;
	data->movey = 0;
	data->zoom = data->winwidth/4;
	data->max_iter = MAX_ITER;
	data->palette_choice = 0;
	data->isLocked = false;
	data->backgroundcolor = 0x00;

	// data->thread_range.start.x = 0;
	// data->thread_range.start.y = 0;
	// data->thread_range.end.x = data->winwidth;
	// data->thread_range.end.y = step;

	// data->thread_range.start.x = 0;
	// data->thread_range.start.y = step;
	// data->thread_range.end.x = data->winwidth;
	// data->thread_range.end.y = step * 2;

	// data->thread_range.start.x = 0;
	// data->thread_range.start.y = step * 2;
	// data->thread_range.end.x = data->winwidth;
	// data->thread_range.end.y = step * 3;

	// data->thread_range.start.x = 0;
	// data->thread_range.start.y = step * 3;
	// data->thread_range.end.x = data->winwidth;
	// data->thread_range.end.y = step * 4;
}

int mouse_move(int x, int y, t_data *data)
{
	ft_refresh_image(data);
	if (!data->isLocked)
	{
		data->juliaPos.x = (double)(x * 1.5)/ data->winwidth;
		data->juliaPos.y = (double)(y * 1.5) / data->winheight;
	}
	data->winPos.x = (double)x;
	data->winPos.y = (double)y;
	data->worldPos.x = ft_get_worldPos(data->winPos.x, data->winwidth, data->zoom);
	data->worldPos.y = ft_get_worldPos(data->winPos.y, data->winheight, data->zoom);

	//printf("\nzoom == %.14Lf\nworldPos.x == %.14Lf\nworldPos.y == %.14Lf\nmovex == %.14Lf\nmovey == %.14Lf\n",data->zoom,data->worldPos.x,data->worldPos.y,data->movex,data->movey);
	ft_fractal_choice(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}

int mouse_press(int button,int x,int y, t_data *data)
{
	double	oldZoom;
	(void)x;
	(void)y;

	ft_refresh_image(data);
	if (button == LEFT_CLICK)
	{
		data->max_iter += 10;
	}
	else if (button == RIGHT_CLICK)
	{
		data->max_iter -= 10;
	}
	if (button == SCROLL_UP) // + zoom scroll up
	{
		oldZoom = data->zoom;
		data->zoom *= 1.3;
		//printf("new == %f\nold == %f\n\n", (data->winPos.x - data->winwidth/2)/ data->zoom,  (data->winPos.x - data->winwidth/2)/ (oldZoom));
		/* calculate the difference between oldWorldPos and newWorldPos and subtract it from current(new pos) to keep the cursor is same worldPos
						same as	 ft_get_worldPos(a, data->winwidth, data->zoom)	-	old world pos == difference between oldpoint and new point >> apply it to all pixels */
		data->movex += (data->winPos.x - data->winwidth/2)/ data->zoom - (data->winPos.x - data->winwidth/2)/ (oldZoom);
		data->movey += (data->winPos.y - data->winheight/2)/ data->zoom  - (data->winPos.y - data->winheight/2)/ (oldZoom);
	}
	else if (button == SCROLL_DOWN) // - zoom scroll down
	{
		if (data->zoom <= 1)
			data->zoom = 1;
		else
		{
			oldZoom = data->zoom;
			data->zoom *= 0.7;
			data->movex -= (data->winPos.x - data->winwidth/2)/ data->zoom - (data->winPos.x - data->winwidth/2)/ (oldZoom);
			data->movey -= (data->winPos.y - data->winheight/2)/ data->zoom  - (data->winPos.y - data->winheight/2)/ (oldZoom);
		}
	}
	ft_fractal_choice(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}
int key_press(int key_code, t_data *data)
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
		data->movex += -data->winwidth/ 10/ (data->zoom); // move 10% of worldScreenSize
	else if (key_code == RIGHT_ARROW)
		data->movex -= -data->winwidth/ 10 / (data->zoom);
	if (key_code == UP_ARROW)
		data->movey += -data->winheight/ 10 / (data->zoom);
	else if (key_code == DOWN_ARROW)
		data->movey -= -data->winheight/ 10 / (data->zoom);
	if (key_code == 91) // iter-up num 8
		data->max_iter += 10;
	else if (key_code == 89) // Iter-down num 7
		data->max_iter -= 10;
	if (key_code == 8)
		ft_palette_rotation(data);
	if (key_code == 1) // S
	{
		if (data->set == 'm')
		{
			data->max_iter = MAX_ITER;
			data->set = 'j';
		}
		else if (data->set == 'j')
		{
			//data->max_iter = MAX_ITER;
			data->set = 's';
		}
		else if (data->set == 's')
		{
			data->max_iter = MAX_ITER;
			data->set = 'b';
		}
		else
			data->set = 'm';
	}
	if (key_code == 11) // B
	{
		if (data->backgroundcolor == 0xFFFFFF)
			data->backgroundcolor = 0x00;
		else
			data->backgroundcolor = 0xFFFFFF;
	}
	if (key_code == 37) // L
		data->isLocked = data->isLocked ? false : true;		
	if (key_code == 15) // R reset
		ft_init_fractal(data);
	ft_fractal_choice(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	return (0);
}

void	ft_image_fill(t_data *data, int x, int y, int color)
{
	data->image[y * data->winwidth + x] = color;
	//((char *)(data->image))[y * data->winwidth + x + 3] = (char)255;
}

void ft_color_change(int *col)
{
		*col = 0xFF * (*col) / MAX_ITER;
	// double pas;

	// pas = ((double)(0xFFFFFF) / (300));
	// *col = (int)((*col) * pas);

	// if (*col % 2)
	// 	*col = 0x000000;
	// else
	// {
	// 	*col = 0xFFFFFF; //0x660022
	// }
}

/*
color is 0x00RRGGBB         change 00 for opacity
0x330033 dark-purple
0x3300DD p-blue
z = 0;
z' = z*z + c; ==> z' = c;

z'' = z*z + c; ==> z'' = (a+bi)(a+bi) + c
                       = a*a - b*b + 2bi  + c
					     ( real  ) + (imaginary)

						so to draw in the complex plane

						>real part a:
						 x = a*a - b*b + x(real part of c, which is x of the point that we're currently iterating on)

						>imaginary part b:
						 x = 2bi + y(imaginary part of c, which is y of the point that we're currently iterating on)
*/

int		mandlebrot_set(t_data *data, double c_x, double c_y)
{
	double real = 0;
	double imaginary = 0;
	double tmpreal;
	int i = 0;

	while (i < data->max_iter)
	{//				a * a     -       b * b
		tmpreal = real * real - imaginary * imaginary + c_x;
	//              2abi
		imaginary = 2 * real * imaginary + c_y;
		real = tmpreal;
		// magnitude = sqrt(r*r + i*i)
		// if [sqrt(r*r + i*i) > 2 == > r*r + i*i > 4]
		if (real * real + imaginary  * imaginary > 4)
			return (i);
		i++;
	}
	return 0;
}

int		burning_ship(t_data *data, double c_x, double c_y)
{
	double real = 0;
	double imaginary = 0;
	double tmpreal;
	int i = 0;

	while (i < data->max_iter)
	{//				a * a     -       b * b
		tmpreal = ABS(real * real - imaginary * imaginary + c_x);
	//              2abi
		imaginary = ABS(2 * real * imaginary + c_y);
		real = tmpreal;
		// magnitude = sqrt(r*r + i*i)
		// if [sqrt(r*r + i*i) > 2 == > r*r + i*i > 4]
		if (real * real + imaginary  * imaginary > 4)
			return (i);
		i++;
	}
	return 0;
}


int		julia_set(t_data *data, double real, double imaginary)
{
	double c_x = data->juliaPos.x;
	double c_y = data->juliaPos.y;
	double tmpreal;
	int i;
	
	i = 0;
	while (i < data->max_iter)
	{//				a * a     -       b * b
		tmpreal = real * real - imaginary * imaginary + c_x;
	//              2abi
		imaginary = 2 * real * imaginary + c_y;

		real = tmpreal;
		// magnitude = sqrt(r*r + i*i)
		// if [sqrt(r*r + i*i) > 2 == > r*r + i*i > 4]
		if (real * real + imaginary  * imaginary > 4)
		{
			return i;
		}
		i++;
	}
	return 0;
}

int		 sierpinski_triangle(t_data *data)
{
	int corner;
	int i;
	t_point point1;
	t_point point2;
	t_point point3;
	t_point ranpoint;
	
	
	point1.x = data->winwidth / 2;
	point1.y = 0;
	point2.x = 0;
	point2.y = data->winheight;
	point3.x = data->winheight;
	point3.y = data->winheight;
	ranpoint.x = point1.x;
	ranpoint.y = data->winheight / 2;
	i = 0;
	//loop
	while (i++ < data->max_iter)
	{
		if (!(corner = rand() % 3))
		{
			ranpoint.x = lerp(ranpoint.x, point1.x, (double)0.5);
			ranpoint.y = lerp(ranpoint.y, point1.y, (double)0.5);
			ft_image_fill(data, ranpoint.x , ranpoint.y, 0xFF0000);
		}
		else if (corner == 1)
		{
			ranpoint.x = lerp(ranpoint.x, point2.x, (double)0.5);
			ranpoint.y = lerp(ranpoint.y, point2.y, (double)0.5);
			ft_image_fill(data, ranpoint.x , ranpoint.y, 0xFF0000);
		}
		else
		{
			ranpoint.x = lerp(ranpoint.x, point3.x, (double)0.5);
			ranpoint.y = lerp(ranpoint.y, point3.y, (double)0.5);
			ft_image_fill(data, ranpoint.x , ranpoint.y, 0xFF0000);
		}
	}
	return (1);
}

int		ft_checkif_in_set(t_data *data, double a, double b)
{
	if (data->set == 'j')
	{
		return (julia_set(data, ft_get_worldPos(a, data->winwidth, data->zoom) - data->movex,
							ft_get_worldPos(b, data->winheight, data->zoom) - data->movey));
	}
	else if (data->set == 'm')
	{
		return (mandlebrot_set(data, ft_get_worldPos(a, data->winwidth, data->zoom) - data->movex,
							ft_get_worldPos(b, data->winheight, data->zoom) - data->movey));
	}
	else if (data->set == 'b')
	{
		return (burning_ship(data, ft_get_worldPos(a, data->winwidth, data->zoom) - data->movex,
							ft_get_worldPos(b, data->winheight, data->zoom) - data->movey));
	}
	return (0);
}

void	ft_handle_threads(t_data *datacopy0, t_data *datacopy1, t_data *datacopy2, t_data *datacopy3)
{
	pthread_t thread_id0;
	pthread_t thread_id1;
	pthread_t thread_id2;
	pthread_t thread_id3;
	// int step;

	// step = data->winheight / 4;
	datacopy0->thread_range.start.x = 0;
	datacopy0->thread_range.start.y = 0;
	datacopy0->thread_range.end.x = datacopy0->winwidth;
	datacopy0->thread_range.end.y = 150;

	pthread_create(&thread_id0, NULL, draw_fractal, (void *)datacopy0);
	datacopy1->thread_range.start.x = 0;
	datacopy1->thread_range.start.y = 150;
	datacopy1->thread_range.end.x = datacopy1->winwidth;
	datacopy1->thread_range.end.y = 150 * 2;
	pthread_create(&thread_id1, NULL, draw_fractal, (void *)datacopy1);
	datacopy2->thread_range.start.x = 0;
	datacopy2->thread_range.start.y = 150 * 2;
	datacopy2->thread_range.end.x = datacopy2->winwidth;
	datacopy2->thread_range.end.y = 150 * 3;
	pthread_create(&thread_id2, NULL, draw_fractal, (void *)datacopy2);
	datacopy3->thread_range.start.x = 0;
	datacopy3->thread_range.start.y = 150 * 3;
	datacopy3->thread_range.end.x = datacopy3->winwidth;
	datacopy3->thread_range.end.y = 150 * 4;
	pthread_create(&thread_id3, NULL, draw_fractal, (void *)datacopy3);
	pthread_join(thread_id0, NULL);
	pthread_join(thread_id1, NULL);
	pthread_join(thread_id2, NULL);
	pthread_join(thread_id3, NULL);
}

void ft_multi_thread(t_data *data)
{
	t_data datacopy0;
	t_data datacopy1;
	t_data datacopy2;
	t_data datacopy3;

	datacopy0 = *data;
	datacopy1 = *data;
	datacopy2 = *data;
	datacopy3 = *data;
	ft_handle_threads(&datacopy0, &datacopy1, &datacopy2, &datacopy3);
	
	

	
	
}

void	ft_fractal_choice(t_data *data)
{
	if (data->set == 'j' || data->set == 'm' || data->set == 'b')
	{
		ft_multi_thread(data);
		//draw_fractal(data);
	}
	else if (data->set == 's')
	{
		data->max_iter = 10000000;
		sierpinski_triangle(data);
	}
}

void	*draw_fractal(void *param)
{
	t_data *data;

	data = param;
	int col;
	int a = data->thread_range.start.x, b = data->thread_range.start.y;
	//		x (real)	y (imaginary)
	while (a < data->thread_range.end.x)
	{
		b = data->thread_range.start.y;
		while (b < data->thread_range.end.y)
		{			// return number of iter
			if ((col = ft_checkif_in_set(data, (double)a, (double)b)))
			{
				ft_color_change(&col);
				ft_image_fill(data, a, b, col);
			}
			else
				ft_image_fill(data, a, b, data->backgroundcolor);
			b++;
		}
		a++;
	}
	return (NULL);
}

int		ft_input_check(t_data *data, int argc, char **argv)
{
	if (argc == 2)
	{
		if (!ft_strcmp(argv[1], "Julia"))
			data->set = 'j';
		else if (!ft_strcmp(argv[1], "Mandelbrot"))
			data->set = 'm';
		else if (!ft_strcmp(argv[1], "Sierpinski"))
			data->set = 's';
		else if (!ft_strcmp(argv[1], "Burningship"))
			data->set = 'b';
		else
			return (0);
	}
	else
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	srand(time(NULL));
	if (!(data = malloc(sizeof(t_data))))
		return (0);
	if (!ft_input_check(data, argc, argv))
	{
		ft_putendl("Usage: ./fractol [Mandelbrot] [Julia] [Sierpinski] [Burningship]");
		free(data);
		data = NULL;
		return(0);
	}
	ft_palette(data);
	if (!(ft_window_setup(data, "Wired", 600, 600)) || !ft_image_setup(data))
		return (0);
/*
	The Mandelbrot set is the set of complex numbers c for which the sequence :
	Z0 = 0
	Zn = Zn-1 + c
	converges.

	The Mandelbrot set:
	is a picture in parameter space
	records the fate of the orbit of 0

	The filled Julia set
	is a picture in dynamical plane
	records the fate of all orbits
*/
	ft_init_fractal(data);
	ft_fractal_choice(data);
	//interfaceUI(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img_ptr, 0, 0);
	//interfacetext(data); // should be after put_image because the str is not included in the image char *
	mlx_hook(data->win, MOUSE_MOVE_CODE, 0, &mouse_move, (void *)data);
	mlx_hook(data->win, KEY_PRESS_CODE, 0, &key_press, (void *)data);
	mlx_hook(data->win, MOUSE_PRESS_CODE, 0, &mouse_press, (void *)data);
	mlx_hook(data->win, RED_BUTTON_CODE, 0, &red_button, (void *)data);
	mlx_loop(data->mlx);
	//mlx_destroy_image(); frees image
	return (0);
}
