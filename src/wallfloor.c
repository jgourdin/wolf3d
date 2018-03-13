/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallfloor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 12:02:04 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/24 01:00:16 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** Dans un premier temps on regarde la position du sol en face du mur.
** Il y a 4 possibilites possible Nord, Sud, Est, Ouest.
** Une fois qu'on a cette distance et position on peut dessiner le sol jusqu'en
** bas de l'ecran.
*/

void		put_floor(t_wolf *env, int x, int y)
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
	draw_floor(env, x, y);
}

/*
** C'est ici qu'on dessiner jusqu'en bas.
** Le plafond est dessine par symetrie d'ou l'interet
** d'avoir des images de meme taille.
*/

void		draw_floor(t_wolf *env, int x, int y)
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
		FLOORTEXX = (int)(CURRENTFLOORX * env->texture[5].text.largeur / 4) %
			env->texture[5].text.largeur;
		FLOORTEXY = (int)(CURRENTFLOORY * env->texture[5].text.hauteur / 4) %
			env->texture[5].text.hauteur;
		pixel = get_floor_color(env, 5);
		pixel2 = get_floor_color(env, 0);
		sym = HEIGHT - y;
		mlx_pixel_to_image(x, y++, env, pixel);
		mlx_pixel_to_image(x, sym, env, pixel2);
	}
}

/*
** Semblable au get_texture_color.
*/

int			get_floor_color(t_wolf *env, int id)
{
	int		index_text;
	int		ptr;

	if (env->info.vapormod == 1)
	{
		index_text = (FLOORTEXY * env->vapor[id].imgv.sizel) + (FLOORTEXX *
			env->vapor[id].imgv.bpp / 8);
		ptr = *(int *)&env->vapor[id].imgv.data[index_text];
	}
	else
	{
		index_text = (FLOORTEXY * env->texture[id].text.sizel) + (FLOORTEXX *
			env->texture[id].text.bpp / 8);
		ptr = *(int *)&env->texture[id].text.data[index_text];
	}
	return (ptr);
}
