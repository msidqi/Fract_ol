/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:43:22 by msidqi            #+#    #+#             */
/*   Updated: 2018/11/24 04:59:23 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGL_H
# define LIBGL_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <pthread.h>
# include <time.h>

# define RIGHT_ARROW 124
# define LEFT_ARROW 123
# define UP_ARROW 126
# define DOWN_ARROW 125
# define ZOOM_OUT 78
# define ZOOM_IN 69
# define SPACE 49
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define MOUSE_PRESS_CODE 4
# define MOUSE_MOVE_CODE 6
# define KEY_PRESS_CODE 2
# define RED_BUTTON_CODE 17
# define MAX_ITER 30
# define ABS(Value) (Value >= 0) ? (Value) : -(Value)


typedef struct	s_point
{
	double		x;
	double		y;
}				t_point;

typedef struct	s_startend
{
	t_point		start;
	t_point		end;
}				t_startend;

typedef enum
{
		false,
		true
}		bool;

typedef	struct	s_data
{
	t_point		juliaPos;
	t_point		winPos;
	t_point		worldPos;
	bool		isLocked;
	int			winwidth;
	int			winheight;
	void		*mlx;
	void		*win;
	void		*img_ptr;
	int			*image;
	int			palette_choice;
	int			palette[8];
	int			backgroundcolor;
	double		zoom;
	double		movex;
	double		movey;
	char		set;
	t_startend	thread_range;


	int			max_iter;
	int			endian;
	int			size_line;
	int			bpp;
}				t_data;

void			drawcircle(void *mlx, void *win, int centerx,
					int centery, int radius, int color);
void			drawline(t_data *data, int startpoint, int nlines, int color);
void			drawnsquares(t_data *data, int onedlen);
void			connect(t_data *data, int *tab, int color);
//int				key_press(int key_code, void *param);
void			interfacetext(t_data *data);
void			interfaceUI(t_data *data);
void			ft_palette(t_data *data);
void			*draw_fractal(void *param);
void			ft_fractal_choice(t_data *data);
int				ft_sqrt(int nb);
int				ft_window_setup(t_data *data, char *win_name,
											int winheight, int winwidth);
int     		ft_image_setup(t_data *data);
void			ft_palette_rotation(t_data *data);

#endif