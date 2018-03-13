/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 04:54:58 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/23 06:30:16 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** On stock les textures dans mon tableau file.
** Ce sera plus simple d'aller les chercher.
*/

void		init_file(t_wolf *env)
{
	env->texture->file[0] = "pics/wdriv1.xpm";
	env->texture->file[1] = "pics/kstone2.xpm";
	env->texture->file[2] = "pics/kbrickl1.xpm";
	env->texture->file[3] = "pics/kgr2_p.xpm";
	env->texture->file[4] = "pics/r3_128srqw.xpm";
	env->texture->file[5] = "pics/pvsepblu.xpm";
	env->texture->file[6] = "pics/shelf.xpm";
	env->texture->file[7] = "pics/minion.xpm";
}

/*
** L'initialisation, je creer une image pour chaque texture que je stock
** dans mon tableau texture !
*/

int			init_text(t_wolf *env)
{
	int		i;

	i = 0;
	env->texture = malloc(sizeof(t_text) * 8);
	env->texture->file = malloc(sizeof(char *) * 9);
	init_file(env);
	while (i < 8)
	{
		env->texture[i].text.img = mlx_xpm_file_to_image(INIT,
				env->texture->file[i], &env->texture[i].text.largeur,
				&env->texture[i].text.hauteur);
		if (env->texture[i].text.img == NULL)
			return (0);
		env->texture[i].text.data = mlx_get_data_addr(env->texture[i].text.img,
				&env->texture[i].text.bpp, &env->texture[i].text.sizel,
				&env->texture[i].text.endian);
		i++;
	}
	return (1);
}

/*
** Je fais cherche ici la valeur du pixel et
** recupere sa position et sa couleur.
** Pour ensuite la dessiner grace a put_pixel_to_image !
*/

int			get_texture_color(t_wolf *env, int id)
{
	int		index_text;
	int		ptr;

	if (env->info.vapormod == 1)
	{
		index_text = (TEXY * env->vapor[id].imgv.largeur) + (TEXX);
		ptr = ((int *)env->vapor[id].imgv.data)[index_text];
	}
	else
	{
		index_text = (TEXY * env->texture[id].text.largeur) + (TEXX);
		ptr = ((int *)env->texture[id].text.data)[index_text];
	}
	return (ptr);
}

/*
** Ici nous avons la selection de la texture en fonction des infos sur la carte.
** On calcule ensuite la valeur de wallX, ou le mur a ete touche.
** TexX est la coordonne en x de la tecture.
** Il depend du cote touche et dessiner
** la direction du rayon. On connait la coordonne en X de la texture ainsi.
*/

void		mlx_text_to_img(t_wolf *env)
{
	ID = MAP[MAPX][MAPY];
	if (ID >= 8)
		ID = 0;
	if (SIDE == 0)
		WALLX = RAYPOSY + PERPWALLDIST * RAYDIRY;
	else
		WALLX = RAYPOSX + PERPWALLDIST * RAYDIRX;
	WALLX -= (int)(WALLX);
	TEXX = WALLX * env->texture[ID].text.largeur;
	if (env->info.vapormod == 1)
	{
		if (SIDE == 0 && RAYDIRX > 0)
			TEXX = env->vapor[ID].imgv.largeur - TEXX - 1;
		if (SIDE == 1 && RAYDIRY < 0)
			TEXX = env->vapor[ID].imgv.largeur - TEXX - 1;
	}
	else
	{
		if (SIDE == 0 && RAYDIRX > 0)
			TEXX = env->texture[ID].text.largeur - TEXX - 1;
		if (SIDE == 1 && RAYDIRY < 0)
			TEXX = env->texture[ID].text.largeur - TEXX - 1;
	}
}

void		hud(t_wolf *env)
{
	char	*px;
	char	*py;
	char	*fog;

	fog = ft_itoa(env->gun.fog);
	px = ft_itoa((int)POSX);
	py = ft_itoa((int)POSY);
	if (env->game.game == 1 && env->game.start == 0)
		mlx_string_put(INIT, WIN, WIDTH / 2, HEIGHT / 2, 0xA5260A,
				"PAUSE");
	mlx_string_put(INIT, WIN, 50, 50, 0xFFFFFF, "X/Y :");
	mlx_string_put(INIT, WIN, 50, 100, 0xFFFFFF, px);
	mlx_string_put(INIT, WIN, 50, 150, 0xFFFFFF, py);
	mlx_string_put(INIT, WIN, 50, 200, 0xFFFFFF, "SPAWN : +");
	mlx_string_put(INIT, WIN, 50, 250, 0xFFFFFF, fog);
	free(py);
	free(px);
}
