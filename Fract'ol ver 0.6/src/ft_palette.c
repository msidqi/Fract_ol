/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_palette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 01:38:04 by msidqi            #+#    #+#             */
/*   Updated: 2018/12/10 22:04:01 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgl.h"

 /* change current palette to 0 if u change the palette type*/
void	ft_palette_rotation(t_data *data)
{
	int size;

	size = sizeof(data->palette)/sizeof(data->palette[0]);
	data->palette_choice++;
	
	if (data->palette_choice > (size - 1))
		data->palette_choice = 0;
	ft_palette(data);	
}

static	void	ft_palette3(t_data *data)
{
	if (data->palette_choice == 4)
	{
		data->palette[0] = 0x30b1c3;
		data->palette[1] = 0xabe9f0;
		data->palette[2] = 0x9a4e00;
		data->palette[3] = 0xba7e00;
		data->palette[4] = 0xff6700;
		data->palette[5] = 0xffa700;
		data->palette[6] = 0xffF700;
		data->palette[7] = 0xfcffcd;
	}
	else if (data->palette_choice == 5)
	{
		data->palette[0] = 0xb9c1d1;
		data->palette[1] = 0xe9d1e1;
		data->palette[2] = 0x909cb5;
		data->palette[3] = 0xa0bcd5;
		data->palette[4] = 0x707a8a;
		data->palette[5] = 0x7f7b81;
		data->palette[6] = 0x9f9ba1;
		data->palette[7] = 0xc2bdb7;
	}
}

static	void	ft_palette2(t_data *data)
{
	if (data->palette_choice == 2)
	{
		data->palette[0] = 0xe5c883;
		data->palette[1] = 0xf5f8b3;
		data->palette[2] = 0xfffef2;
		data->palette[3] = 0xff8080;
		data->palette[4] = 0xffa0a0;
		data->palette[5] = 0xf4d8ac;
		data->palette[6] = 0xffA16c;
		data->palette[7] = 0xf0d38c;
	}
	else if (data->palette_choice == 3)
	{
		data->palette[0] = 0x8bd9f0;
		data->palette[1] = 0xabe9f0;
		data->palette[2] = 0xa2e7f6;
		data->palette[3] = 0xb2d7f6;
		data->palette[4] = 0xb5f2fb;
		data->palette[5] = 0xbb813c;
		data->palette[6] = 0x77f6f5;
		data->palette[7] = 0x33f455;
	}
	else if (data->palette_choice >= 4)
		ft_palette3(data);
}

void			ft_palette(t_data *data)
{
	if (data->palette_choice == 0)
	{
		data->palette[0] = 0x0000e6;
		data->palette[1] = 0x4ddbff;
		data->palette[2] = 0xccff66;
		data->palette[3] = 0xffff00;
		data->palette[4] = 0xffcc00;
		data->palette[5] = 0xff9933;
		data->palette[6] = 0xff6600;
		data->palette[7] = 0xFFFFFE;
	}
	else if (data->palette_choice == 1)
	{
		data->palette[0] = 0x230827;
		data->palette[1] = 0x491647;
		data->palette[2] = 0x7c265e;
		data->palette[3] = 0xff5454;
		data->palette[4] = 0xff9494;
		data->palette[5] = 0xff813c;
		data->palette[6] = 0xffA16c;
		data->palette[7] = 0xfff400;
	}
	else if (data->palette_choice >= 2)
		ft_palette2(data);
}
