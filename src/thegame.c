/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thegame.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 02:16:34 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/23 03:41:05 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		lauchgame(t_wolf *env)
{
	if (env->game.game == 1)
	{
		mlx_put_image_to_window(INIT, env->bomb.win, env->bomb.img, 0, 0);
		mlx_string_put(INIT, env->bomb.win, 95, 50, 0xA5260A,
				ft_strjoin("00:00:", ft_itoa(env->game.chrono)));
		if (env->game.start == 1)
		{
			if (env->game.time_wait != time(NULL) && time(NULL)
					< env->game.time_end)
			{
				env->game.chrono--;
				env->game.time_wait = time(NULL);
			}
			else if (time(NULL) >= env->game.time_end)
			{
				set_game(env);
				env->game.start = 0;
			}
		}
	}
	return (0);
}

void	set_game(t_wolf *env)
{
	POSX = 3.5;
	POSY = 3.5;
	if (env->game.start == 1)
	{
		env->game.time_start = time(NULL);
		env->game.time_end = env->game.time_start + 60;
		env->game.time_wait = env->game.time_start;
		env->game.chrono = 60;
	}
}

void	menu_game(t_wolf *env)
{
	env->game.file = "pics/menu.xpm";
	env->game.img = mlx_xpm_file_to_image(INIT, env->game.file,
			&env->game.largeur, &env->game.hauteur);
	env->game.win = mlx_new_window(INIT, env->game.largeur,
			env->game.hauteur, "RUN 4 UR LIF");
	mlx_put_image_to_window(INIT, env->game.win,
			env->game.img, 0, 0);
	mlx_expose_hook(env->game.win, gere_expose2, env);
	mlx_hook(env->game.win, 17, 0, escape, env);
}

void	bomb_win(t_wolf *env)
{
	env->bomb.file = "pics/bomb.xpm";
	env->bomb.img = mlx_xpm_file_to_image(INIT, env->bomb.file,
			&env->bomb.largeur, &env->bomb.hauteur);
	env->bomb.win = mlx_new_window(INIT, env->bomb.largeur,
			env->bomb.hauteur, "TIC TAC");
	mlx_put_image_to_window(INIT, env->bomb.win,
			env->bomb.img, 0, 0);
	mlx_expose_hook(env->bomb.win, gere_expose3, env);
}

int		gere_expose2(t_wolf *env)
{
	mlx_put_image_to_window(INIT, env->game.win, env->game.img, 0, 0);
	return (0);
}
