/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 04:50:04 by msidqi            #+#    #+#             */
/*   Updated: 2019/04/25 04:50:06 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

int     ft_image_setup(t_data *data)
{
    	/* creates an image in memory, return (void *) */
	if (!(data->img_ptr = mlx_new_image(data->mlx, data->winwidth,
		data->winheight)))
        return (0);
	
	/*takes pointer to the image and returns details about it + (char *) to 1st byte*/
	if (!(data->image = (int *)mlx_get_data_addr(data->img_ptr, &data->bpp,
                                            &data->size_line, &data->endian)))
        return (0);
	/* casted to int to make defining colors easier by using Hex numbers for RGBA instead of each byte on its own */
	return (1);
}