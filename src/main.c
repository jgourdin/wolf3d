/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 02:01:06 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/23 07:23:44 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** On utilise le decallage binaire pour dessiner sur le DATA
*/

void		mlx_pixel_to_image(int x, int y, t_wolf *env, int color)
{
	long	pos;

	pos = (x * BPP / 8) + (y * SIZE);
	if (pos < 0)
		pos = -pos;
	DATA[pos] = color;
	DATA[pos + 1] = color >> 8;
	DATA[pos + 2] = color >> 16;
}

/*
** Pour tous les x on envoit l'algo dit DDA, et j'envoie le tout
** sur la fenetre puis finalement les informations.
*/

int			lauchfactory(t_wolf *env)
{
	int		x;

	IMG = mlx_new_image(INIT, WIDTH, HEIGHT);
	DATA = mlx_get_data_addr(IMG, &BPP, &SIZE, &ENDIAN);
	x = 0;
	while (x < WIDTH - 1)
	{
		wolf_init(env, x);
		wolf_step(env);
		wolf_wall(env);
		wolf_wall(env);
		wolf_stripe(env);
		wolf_wall(env);
		wolf_draw(env, x);
		x++;
	}
	if (env->info.vapormod == 1)
		vape(env);
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
	if (env->info.vapormod == 1 && env->info.smoke == 0)
		cigs(env);
	else if (env->info.vapormod == 0)
		gun(env);
	hud(env);
	return (0);
}

/*
** On set ici toutes les valeurs initiales pour
** les variables de departs.
*/

int			init(t_wolf *env)
{
	env->info.vari = 0;
	env->info.i = 0;
	env->info.l = 0;
	env->info.k = 0;
	env->info.j = 0;
	env->game.start = 0;
	env->gun.walk1 = 20;
	env->gun.walk = 0;
	env->gun.fog = 0;
	env->info.smoke = 0;
	env->info.vapormod = 0;
	env->info.sound = 0;
	env->game.game = 0;
	env->info.sprint = 1;
	MOVESPEED = 0.07;
	ROTSPEED = 0.1;
	NOCLIP = 0;
	return (1);
}

int			init_suite(t_wolf *env)
{
	INIT = mlx_init();
	initgun(env);
	HEIGHT = env->gun.hauteur;
	WIDTH = env->gun.largeur;
	WIN = mlx_new_window(INIT, WIDTH, HEIGHT, "Wolf3D");
	POSX = 10;
	POSY = 10;
	DIRX = -1;
	DIRY = 0;
	PLANEY = 1.2;
	PLANEX = 0;
	TIME = 1;
	if (!(MAP = map()) || !init_text(env) ||
			!init_vapor_text(env) || !initcigs(env))
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_wolf	*env;

	if (argc == 1 && argv)
	{
		if (!(env = malloc(sizeof(t_wolf))))
			return (0);
		if (!init(env) || !init_suite(env))
			return (0);
		lauchfactory(env);
		mlx_expose_hook(WIN, gere_expose, env);
		mlx_key_hook(WIN, key_hook, env);
		mlx_loop_hook(INIT, loop_hook, env);
		mlx_hook(WIN, 17, 0, escape, env);
		mlx_hook(WIN, 2, 0, k_hook, env);
		mlx_loop(INIT);
	}
	return (0);
}
