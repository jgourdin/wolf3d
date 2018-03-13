/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 18:54:05 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/23 06:39:37 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		do_sound(t_wolf *env)
{
	if (env->info.sprint == 2)
		env->info.music = 2;
	else if (env->info.vapormod == 1)
		env->info.music = 3;
	else if (env->info.vapormod == 0)
		env->info.music = 1;
	env->info.sound = (env->info.sound > 0 ? 0 : env->info.music);
	if (env->info.sound != 0)
	{
		system("killall sh | killall afplay");
		if (env->info.sound == 1)
			system("while :; do afplay sound/Synth.mp3 ;done &>/dev/null &");
		else if (env->info.sound == 2)
			system("while :; do afplay sound/DEJAVU.mp3 ;done &>/dev/null &");
		else if (env->info.sound == 3)
			system("while :; do afplay sound/vapor.mp3 ;done &>/dev/null &");\
	}
	else
		system("killall sh | killall afplay");
}

void		init_file_cigs(t_wolf *env)
{
	env->cigs->file[0] = "vapexpm/1.xpm";
	env->cigs->file[1] = "vapexpm/2.xpm";
	env->cigs->file[2] = "vapexpm/3.xpm";
	env->cigs->file[3] = "vapexpm/4.xpm";
	env->cigs->file[4] = "vapexpm/5.xpm";
	env->cigs->file[5] = "vapexpm/6.xpm";
	env->cigs->file[6] = "vapexpm/7.xpm";
	env->cigs->file[7] = "vapexpm/8.xpm";
	env->cigs->file[8] = "vapexpm/9.xpm";
	env->cigs->file[9] = "vapexpm/10.xpm";
	env->cigs->file[10] = "vapexpm/11.xpm";
	env->cigs->file[11] = "vapexpm/12.xpm";
	env->cigs->file[12] = "vapexpm/13.xpm";
	env->cigs->file[13] = "vapexpm/14.xpm";
	env->cigs->file[14] = "vapexpm/15.xpm";
	env->cigs->file[15] = "vapexpm/16.xpm";
	env->cigs->file[16] = "vapexpm/smoke.xpm";
}

int			initcigs(t_wolf *env)
{
	int		i;

	i = 0;
	env->cigs = malloc(sizeof(t_text) * 17);
	env->cigs->file = malloc(sizeof(char *) * 18);
	init_file_cigs(env);
	while (i < 17)
	{
		env->cigs[i].text.img = mlx_xpm_file_to_image(INIT,
				env->cigs->file[i], &env->cigs[i].text.largeur,
				&env->cigs[i].text.hauteur);
		if (env->cigs[i].text.img == NULL)
			return (0);
		i++;
	}
	return (1);
}

void		cigs_animation(t_wolf *env)
{
	if (env->info.l == 1)
	{
		lauchfactory(env);
		env->info.l = 0;
	}
	if (env->info.i < 6 && env->info.i >= 0)
	{
		env->info.i++;
		mlx_put_image_to_window(INIT, WIN,
				env->cigs[env->info.j].text.img, 0, 0);
	}
	else if (env->info.i >= 6 && env->info.i > 0 && env->info.j < 15)
	{
		env->info.j++;
		env->info.i = 0;
		env->info.l = 1;
	}
	else if (env->info.j == 15)
	{
		env->info.j = 15;
		env->info.i = -1;
		env->gun.fog = env->gun.fog + 75;
	}
	cigs_suite(env);
}

void		cigs_suite(t_wolf *env)
{
	if (env->info.k < 6 && env->info.i < env->info.j)
	{
		env->info.k++;
		mlx_put_image_to_window(INIT, WIN,
				env->cigs[env->info.j].text.img, 0, 0);
	}
	else if (env->info.k >= 6 && env->info.i < 0)
	{
		env->info.j--;
		env->info.l = 1;
		env->info.k = 0;
	}
	else if (env->info.j <= 0 && env->info.i == -1)
	{
		env->info.i = 0;
		env->info.k = 0;
		env->info.j = 0;
		env->info.smoke = 0;
		mlx_put_image_to_window(INIT, WIN, env->cigs[0].text.img, 0, 0);
	}
}
