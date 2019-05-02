/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window_setup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 09:51:13 by msidqi            #+#    #+#             */
/*   Updated: 2019/03/21 09:51:15 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int	ft_window_setup(t_data *data, char *win_name, int winheight, int winwidth)
{
	data->winheight = winheight;
	data->winwidth = winwidth;
	if (!(data->mlx = mlx_init()))
		return (0);
	/* creates and opens a window*/
	if (!(data->win = mlx_new_window(data->mlx, data->winwidth,
		data->winheight, win_name)))
		return (0);
	return (1);
}