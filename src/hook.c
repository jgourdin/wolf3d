/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 21:14:47 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/23 07:19:13 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		k_hook2(int keycode, t_wolf *env)
{
	if (keycode == 53)
	{
		system("killall sh | killall afplay");
		exit(42);
	}
	else if (keycode == 9)
	{
		env->info.vapormod = (env->info.vapormod == 1 ? 0 : 1);
		env->info.sprint = 1;
		env->info.vari = 0;
		env->gun.walk = 0;
		env->gun.walk1 = 20;
		env->gun.fog = 0;
	}
	else if (keycode == NOCLIPON || keycode == NOCLIPOFF)
		NOCLIP = (keycode == NOCLIPON ? 1 : 0);
	else if (keycode == MINUS || keycode == PLUS)
	{
		POSX = (keycode == MINUS ? -400 : 10);
		POSY = (keycode == MINUS ? -400 : 10);
	}
	else if (keycode == 12)
		do_sound(env);
}
