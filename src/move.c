/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 07:24:56 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/23 07:25:49 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** On fait une rotation du plan et de la direction
** de la camera soit DIR et PLANE
** Cos et sin donnent ce mouvement circulaire.
*/

static void		left_right(t_wolf *env, int keycode)
{
	if (keycode == LEFT)
	{
		OLDDIRX = DIRX;
		DIRX = DIRX * cos(ROTSPEED) - DIRY * sin(ROTSPEED);
		DIRY = OLDDIRX * sin(ROTSPEED) + DIRY * cos(ROTSPEED);
		OLDPLANEX = PLANEX;
		PLANEX = PLANEX * cos(ROTSPEED) - PLANEY * sin(ROTSPEED);
		PLANEY = OLDPLANEX * sin(ROTSPEED) + PLANEY * cos(ROTSPEED);
	}
	else
	{
		OLDDIRX = DIRX;
		DIRX = DIRX * cos(-ROTSPEED) - DIRY * sin(-ROTSPEED);
		DIRY = OLDDIRX * sin(-ROTSPEED) + DIRY * cos(-ROTSPEED);
		OLDPLANEX = PLANEX;
		PLANEX = PLANEX * cos(-ROTSPEED) - PLANEY * sin(-ROTSPEED);
		PLANEY = OLDPLANEX * sin(-ROTSPEED) + PLANEY * cos(-ROTSPEED);
	}
}

/*
** On regarde si il y a un mur devant nous. Et on augmente le POSX dans la
** direction par la vitesse.
*/

static void		updown(t_wolf *env, int keycode)
{
	if (env->info.sprint == 2)
		MOVESPEED = 0.2;
	else
		MOVESPEED = 0.07;
	if (keycode == UP)
	{
		if (!MAP[(int)(POSX + DIRX * MOVESPEED)][(int)(POSY)] ||
			NOCLIP == 1)
			POSX += DIRX * MOVESPEED;
		if (!MAP[(int)(POSX)][(int)(POSY + DIRY * MOVESPEED)] ||
			NOCLIP == 1)
			POSY += DIRY * MOVESPEED;
	}
	else
	{
		if (!MAP[(int)(POSX - DIRX * MOVESPEED)][(int)(POSY)] ||
			NOCLIP == 1)
			POSX -= DIRX * MOVESPEED;
		if (!MAP[(int)(POSX)][(int)(POSY - DIRY * MOVESPEED)] ||
				NOCLIP == 1)
			POSY -= DIRY * MOVESPEED;
	}
}

/*
** NOCLIP sert a se deplacer librement. sans collision
** Il y a aussi une fonction pour retourner au SPAWN
** ou se teleporter dans la memoire.
*/

int				key_hook(int keycode, t_wolf *env)
{
	if (keycode == 35)
	{
		set_game(env);
		env->game.game = (env->game.game == 1 ? 0 : 1);
		if (env->game.game == 1)
		{
			menu_game(env);
			bomb_win(env);
		}
		else
		{
			mlx_destroy_window(INIT, env->game.win);
			mlx_destroy_window(INIT, env->bomb.win);
			env->game.start = 0;
		}
	}
	else if (keycode == 37 && env->info.vapormod)
		env->info.smoke = 1;
	else if (env->game.game == 1 && keycode == 36)
		env->game.start = (env->game.start == 1 ? 0 : 1);
	else
		return (0);
	lauchfactory(env);
	return (0);
}

int				k_hook(int keycode, t_wolf *env)
{
	k_hook2(keycode, env);
	if (keycode == 76)
		env->info.sprint = (env->info.sprint == 1 ? 2 : 1);
	if ((keycode == LEFT || keycode == RIGHT) && env->info.smoke == 0)
		left_right(env, keycode);
	else if ((keycode == UP || keycode == DOWN) &&
			env->game.game == env->game.start && env->info.smoke == 0)
		updown(env, keycode);
	else
		return (0);
	if ((int)POSX == 17 && (int)POSY == 20)
	{
		POSX = 2;
		POSY = 20;
		env->game.game = 0;
		env->game.start = 0;
	}
	mlx_destroy_image(INIT, IMG);
	lauchfactory(env);
	return (0);
}
