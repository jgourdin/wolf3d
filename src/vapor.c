/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vapor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 23:10:26 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/23 03:41:38 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		init_vapor_file(t_wolf *env)
{
	env->vapor->file[0] = "VaporXPM/grass.xpm";
	env->vapor->file[1] = "VaporXPM/horizon.xpm";
	env->vapor->file[2] = "VaporXPM/Quadri.xpm";
	env->vapor->file[3] = "VaporXPM/water.xpm";
	env->vapor->file[4] = "VaporXPM/pinky.xpm";
	env->vapor->file[5] = "VaporXPM/space.xpm";
	env->vapor->file[6] = "VaporXPM/illuminati.xpm";
	env->vapor->file[7] = "VaporXPM/Macintosh.xpm";
}

int			init_vapor_text(t_wolf *env)
{
	int		i;

	i = 0;
	env->vapor = malloc(sizeof(t_text) * 8);
	env->vapor->file = malloc(sizeof(char *) * 9);
	init_vapor_file(env);
	while (i < 8)
	{
		env->vapor[i].imgv.img = mlx_xpm_file_to_image(INIT,
				env->vapor->file[i], &env->vapor[i].imgv.largeur,
				&env->vapor[i].imgv.hauteur);
		if (env->vapor[i].imgv.img == NULL)
			return (0);
		env->vapor[i].imgv.data = mlx_get_data_addr(env->vapor[i].imgv.img,
				&env->vapor[i].imgv.bpp, &env->vapor[i].imgv.sizel,
				&env->vapor[i].imgv.endian);
		i++;
	}
	return (1);
}

void		put_floor_vapor(t_wolf *env, int x, int y)
{
	if (SIDE == 0 && RAYDIRX > 0)
	{
		FLOORXWALL = MAPX;
		FLOORYWALL = MAPY + WALLX;
	}
	else if (SIDE == 0 && RAYDIRX < 0)
	{
		FLOORXWALL = MAPX + 1.0;
		FLOORYWALL = MAPY + WALLX;
	}
	else if (SIDE == 1 && RAYDIRY > 0)
	{
		FLOORXWALL = MAPX + WALLX;
		FLOORYWALL = MAPY;
	}
	else
	{
		FLOORXWALL = MAPX + WALLX;
		FLOORYWALL = MAPY + 1.0;
	}
	DISTWALL = PERPWALLDIST;
	DISTPLAYER = 0.0;
	draw_floor_vapor(env, x, y);
}

void		draw_floor_vapor(t_wolf *env, int x, int y)
{
	int		pixel;
	int		sym;
	int		pixel2;

	if (DRAWEND < 0)
		DRAWEND = HEIGHT;
	y = DRAWEND + 1;
	while (y < HEIGHT)
	{
		CURRENTDIST = HEIGHT / (2.0 * y - HEIGHT);
		WEIGHT = (CURRENTDIST - DISTPLAYER) / (DISTWALL - DISTPLAYER);
		CURRENTFLOORX = WEIGHT * FLOORXWALL + (1.0 - WEIGHT) * POSX;
		CURRENTFLOORY = WEIGHT * FLOORYWALL + (1.0 - WEIGHT) * POSY;
		FLOORTEXX = (int)(CURRENTFLOORX * env->vapor[5].imgv.largeur / 2) %
			env->vapor[5].imgv.largeur;
		FLOORTEXY = (int)(CURRENTFLOORY * env->vapor[5].imgv.hauteur / 2) %
			env->vapor[5].imgv.hauteur;
		pixel = get_floor_color(env, 5);
		pixel2 = get_floor_color(env, 0);
		sym = HEIGHT - y;
		mlx_pixel_to_image(x, y++, env, pixel);
		mlx_pixel_to_image(x, sym, env, pixel2);
	}
}
