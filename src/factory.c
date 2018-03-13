/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 01:20:45 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/24 00:58:02 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** On trouve la position du rayon et sa direction avec RAYPOS et RAYDIR
** Camera-X est la coordonnee X dans l'espace de la camera
** MAP est l'endroit ou nous nous trouvons sur la carte (wow!)
** SIDEDIST est la longueur du rayon DU cote actuel (x ou y) au second
** DELTADIST est la longueur du rayon d'UN cote (x et y) au second
** Step est la direction de step, soit 1 ou -1
** HIT,on ne va pas faire un dessin
** SIDE signifie si le rayon a touche en allant sur l'axe x ou y (0 ou 1)
*/

void		wolf_init(t_wolf *env, int x)
{
	CAMERAX = 2 * x / (double)WIDTH - 1;
	RAYPOSX = POSX;
	RAYPOSY = POSY;
	RAYDIRX = DIRX + PLANEX * CAMERAX;
	RAYDIRY = DIRY + PLANEY * CAMERAX;
	MAPX = RAYPOSX;
	MAPY = RAYPOSY;
	DELTADISTX = sqrt(1 + (RAYDIRY * RAYDIRY) / (RAYDIRX * RAYDIRX));
	DELTADISTY = sqrt(1 + (RAYDIRX * RAYDIRX) / (RAYDIRY * RAYDIRY));
	HIT = 0;
}

/*
** wolf_step calcul les SIDEDIST de notre position
** et donne une valeur a STEP.
*/

void		wolf_step(t_wolf *env)
{
	if (RAYDIRX < 0)
	{
		STEPX = -1;
		SIDEDISTX = (RAYPOSX - MAPX) * DELTADISTX;
	}
	else
	{
		STEPX = 1;
		SIDEDISTX = (MAPX + 1.0 - RAYPOSX) * DELTADISTX;
	}
	if (RAYDIRY < 0)
	{
		STEPY = -1;
		SIDEDISTY = (RAYPOSY - MAPY) * DELTADISTY;
	}
	else
	{
		STEPY = 1;
		SIDEDISTY = (MAPY + 1.0 - RAYPOSY) * DELTADISTY;
	}
}

/*
** ENFIN, l'algorithme dit DDA."Digital Differential Analysis"
** Il incremente le rayon de 1 carre a chaque fois tant qu'il
** touche pas de mur dans la direction x ou y.
** La variable SIDE nous indique si c'est un cote x ou y qui touche
** un mur.
*/

void		wolf_wall(t_wolf *env)
{
	while (HIT == 0)
	{
		if (SIDEDISTX < SIDEDISTY)
		{
			SIDEDISTX += DELTADISTX;
			MAPX += STEPX;
			SIDE = 0;
		}
		else
		{
			SIDEDISTY += DELTADISTY;
			MAPY += STEPY;
			SIDE = 1;
		}
		if (MAP[MAPX][MAPY] > 0)
			HIT = 1;
	}
}

/*
** wolf_stripe va nous calculer la distance du rayon jusqu'a l'impact.
** PERPWALLDIST est donc le nombre de carre que traverse le rayon.
** Maintenant on doit dessiner tout ca, LINEHEIGHT est la longueur
** des lignes a dessiner a l'ecran.
** On trouve ensuite le premier et dernier pixel a dessiner
** sur la bande actuelle.
*/

void		wolf_stripe(t_wolf *env)
{
	if (SIDE == 0)
		PERPWALLDIST = (MAPX - RAYPOSX + (1 - STEPX) / 2) / RAYDIRX;
	else
		PERPWALLDIST = (MAPY - RAYPOSY + (1 - STEPY) / 2) / RAYDIRY;
	LINEHEIGHT = (int)(HEIGHT / PERPWALLDIST);
	DRAWSTART = -LINEHEIGHT / 2 + HEIGHT / 2;
	if (DRAWSTART < 0)
		DRAWSTART = 0;
	DRAWEND = LINEHEIGHT / 2 + HEIGHT / 2;
	if (DRAWEND >= HEIGHT)
		DRAWEND = HEIGHT - 1;
}

/*
** wolf_draw va nous dessiner ce qu'il faut dessiner sur la bande
** pixel par pixel.
** TexY est la position y de la texture 128 et 256
** serait la pour eviter les floats.
*/

void		wolf_draw(t_wolf *env, int x)
{
	int		y;
	int		pixel;
	int		d;

	y = DRAWSTART;
	mlx_text_to_img(env);
	ID > 7 ? ID = 0 : 0;
	while (y < DRAWEND - 1)
	{
		d = y * 256 - HEIGHT * 128 + LINEHEIGHT * 128;
		if (env->info.vapormod == 1)
			TEXY = (((d * env->vapor[ID].imgv.hauteur) / LINEHEIGHT) / 256);
		else
		{
			TEXY = (((d * env->texture[ID].text.hauteur) / LINEHEIGHT) / 256);
		}
		pixel = get_texture_color(env, ID);
		mlx_pixel_to_image(x, y++, env, pixel);
	}
	if (env->info.vapormod == 1)
		put_floor_vapor(env, x, y);
	else
		put_floor(env, x, y);
}
