/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 17:02:58 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/23 07:24:44 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			initgun(t_wolf *env)
{
	env->gun.vite = "VaporXPM/vitesse.xpm";
	env->gun.file = "pics/lgun.xpm";
	env->gun.file2 = "pics/rgun.xpm";
	env->gun.img = mlx_xpm_file_to_image(INIT, env->gun.file,
			&env->gun.largeur, &env->gun.hauteur);
	env->gun.img2 = mlx_xpm_file_to_image(INIT, env->gun.file2,
			&env->gun.l, &env->gun.h);
	env->gun.img_vi = mlx_xpm_file_to_image(INIT, env->gun.vite,
			&env->gun.l, &env->gun.h);
	return (1);
}

void		vape(t_wolf *env)
{
	int		i;

	i = 0;
	env->gun.fog = (env->gun.fog > 255 ? env->gun.fog - 255 : env->gun.fog);
	while (i < WIDTH * HEIGHT * 4)
	{
		if (i % 4 == 2)
			DATA[i] = (int)DATA[i] + env->gun.fog;
		if (i % 4 == 1)
			DATA[i] = (int)DATA[i] + env->gun.fog;
		if (i % 4 == 0)
			DATA[i] = (int)DATA[i] + env->gun.fog;
		if (i % 4 == 3)
			DATA[i] = (int)DATA[i] + env->gun.fog;
		i++;
	}
	mlx_put_image_to_window(INIT, WIN, IMG, 0, 0);
}

void		gun(t_wolf *env)
{
	mlx_put_image_to_window(INIT, WIN, env->gun.img, 0, 0 + env->gun.walk);
	mlx_put_image_to_window(INIT, WIN, env->gun.img2, 0, 0 + env->gun.walk1);
	if (env->info.sprint == 2)
	{
		mlx_put_image_to_window(INIT, WIN, env->gun.img_vi, 0, 0);
	}
	if (env->info.vari < 20)
	{
		env->gun.walk = env->gun.walk + 1 * env->info.sprint;
		env->gun.walk1 = env->gun.walk1 - 1 * env->info.sprint;
		env->info.vari = env->info.vari + env->info.sprint;
	}
	else if (env->info.vari < 40)
	{
		env->gun.walk1 = env->gun.walk1 + 1 * env->info.sprint;
		env->gun.walk = (unsigned int)env->gun.walk - 1 * env->info.sprint;
		env->info.vari = env->info.vari + 1 * env->info.sprint;
	}
	else if (env->info.vari >= 40)
		env->info.vari = 0;
}

void		cigs(t_wolf *env)
{
	mlx_put_image_to_window(INIT, WIN, env->cigs[1].text.img, 0,
			0 + env->gun.walk);
	if (env->info.vari < 20)
	{
		env->gun.walk = env->gun.walk + 1 * env->info.sprint;
		env->info.vari = env->info.vari + env->info.sprint;
	}
	else if (env->info.vari < 40)
	{
		env->gun.walk = (unsigned int)env->gun.walk - 1 * env->info.sprint;
		env->info.vari = env->info.vari + env->info.sprint;
	}
	else if (env->info.vari >= 40)
		env->info.vari = 0;
}
