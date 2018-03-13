/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgourdin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 23:51:24 by jgourdin          #+#    #+#             */
/*   Updated: 2017/10/23 07:17:09 by jgourdin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "mlx.h"
# include "libft.h"
# include <time.h>
# include <pthread.h>

# define INIT env->mlx.init
# define WIN env->mlx.window
# define IMG env->mlx.image
# define BPP env->mlx.bpp
# define DATA env->mlx.data
# define SIZE env->mlx.size_line
# define ENDIAN env->mlx.endian
# define MAP env->map.map
# define FD env->map.fd
# define YMAX env->info.ymax
# define XMAX env->info.xmax
# define HEIGHT env->info.hauteur
# define WIDTH env->info.largeur
# define POSX env->info.posx
# define POSY env->info.posy
# define PLANEX env->info.planex
# define PLANEY env->info.planey
# define TIME env->info.time
# define OLDTIME env->info.oldtime
# define DIRX env->info.dirx
# define DIRY env->info.diry
# define CAMERAX env->calc.camerax
# define RAYPOSX env->calc.rayposx
# define RAYPOSY env->calc.rayposy
# define RAYDIRY env->calc.raydiry
# define RAYDIRX env->calc.raydirx
# define DELTADISTX env->calc.deltadistx
# define DELTADISTY env->calc.deltadisty
# define MAPX env->calc.mapx
# define MAPY env->calc.mapy
# define HIT env->calc.hit
# define STEPX env->calc.stepx
# define STEPY env->calc.stepy
# define SIDEDISTX env->calc.sidedistx
# define SIDEDISTY env->calc.sidedisty
# define SIDE env->info.side
# define PERPWALLDIST env->calc.perpwalldist
# define HAU env->info.hau
# define DRAWSTART env->info.drawstart
# define DRAWEND env->info.drawend
# define LINEHEIGHT env->info.lineheight
# define ID env->info.id
# define TEXY env->info.texy
# define TEXTURE env->info.texture
# define TEXX env->info.texx
# define WALLX env->info.wallx
# define OLDDIRX env->info.olddirx
# define OLDPLANEX env->info.oldplanex
# define OLDDIRY env->info.olddiry
# define OLDPLANEY env->info.oldplaney
# define ROTSPEED env->info.rotspeed
# define MOVESPEED env->info.movespeed
# define NOCLIP env->info.noclip
# define FLOORXWALL env->floorwall.floorxwall
# define FLOORYWALL env->floorwall.floorywall
# define WEIGHT env->floorwall.weight
# define DISTWALL env->floorwall.distwall
# define DISTPLAYER env->floorwall.distplayer
# define CURRENTDIST env->floorwall.currentdist
# define CURRENTFLOORX env->floorwall.currentfloorx
# define CURRENTFLOORY env->floorwall.currentfloory
# define FLOORTEXX env->floorwall.floortexx
# define FLOORTEXY env->floorwall.floortexy
# define UP 13
# define DOWN 1
# define LEFT 0
# define RIGHT 2
# define NOCLIPON 75
# define NOCLIPOFF 67
# define MINUS 78
# define PLUS 69

typedef struct			s_mlx
{
	void				*init;
	void				*window;
	void				*image;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_mlx;

typedef struct			s_floorwall
{
	double				floorxwall;
	double				floorywall;
	double				distwall;
	double				distplayer;
	double				currentdist;
	double				weight;
	int					floortexx;
	int					floortexy;
	double				currentfloorx;
	double				currentfloory;
}						t_floorwall;

typedef struct			s_map
{
	int					nbr_lines;
	int					fd;
	int					(*map)[22];
}						t_map;

typedef struct			s_gun
{
	int					fog;
	void				*img_vi;
	char				*vite;
	int					h;
	int					l;
	void				*img;
	char				*file;
	void				*img2;
	char				*file2;
	int					hauteur;
	int					largeur;
	int					walk;
	int					walk1;
}						t_gun;

typedef struct			s_info
{
	int					vari;
	int					music;
	int					l;
	int					i;
	int					j;
	int					k;
	int					fog1;
	int					smoke;
	int					vavit;
	int					largeur;
	int					hauteur;
	double				posx;
	double				posy;
	double				dirx;
	double				olddirx;
	double				diry;
	double				olddiry;
	double				planex;
	double				oldplanex;
	double				planey;
	double				oldplaney;
	double				time;
	int					side;
	int					lineheight;
	int					hau;
	int					drawstart;
	int					drawend;
	double				oldtime;
	int					id;
	double				rotspeed;
	int					texy;
	int					texx;
	double				wallx;
	double				movespeed;
	double				noclip;
	int					sound;
	int					texmod;
	int					vapormod;
	int					sprint;
}						t_info;

typedef struct			s_img
{
	void				*img;
	char				*data;
	int					bpp;
	int					sizel;
	int					endian;
	int					largeur;
	int					hauteur;
}						t_img;

typedef struct			s_text
{
	t_img				text;
	char				**file;
	int					current;
}						t_text;

typedef struct			s_imgc
{
	void				*img;
	int					largeur;
	int					hauteur;
}						t_imgc;

typedef struct			s_cigs
{
	t_imgc				text;
	char				**file;
	int					current;
}						t_cigs;

typedef struct			s_imgv
{
	void				*img;
	char				*data;
	int					bpp;
	int					sizel;
	int					endian;
	int					largeur;
	int					hauteur;
}						t_imgv;

typedef struct			s_vapor
{
	t_imgv				imgv;
	char				**file;
	int					current;
}						t_vapor;

typedef struct			s_calc
{
	double				camerax;
	double				rayposx;
	double				rayposy;
	double				raydiry;
	double				raydirx;
	double				deltadistx;
	double				deltadisty;
	int					mapx;
	int					mapy;
	int					hit;
	int					stepx;
	int					stepy;
	double				sidedisty;
	double				sidedistx;
	double				perpwalldist;
}						t_calc;

typedef struct			s_game
{
	int					game;
	time_t				time_start;
	time_t				time_end;
	time_t				time_wait;
	int					chrono;
	void				*img;
	void				*win;
	int					bpp;
	char				*file;
	int					sizel;
	int					endian;
	int					hauteur;
	int					largeur;
	int					start;
}						t_game;

typedef struct			s_bomb
{
	void				*img;
	void				*win;
	int					hauteur;
	int					largeur;
	char				*file;
}						t_bomb;

typedef struct			s_wolf
{
	t_mlx				mlx;
	t_info				info;
	t_calc				calc;
	t_map				map;
	t_text				*texture;
	t_floorwall			floorwall;
	t_game				game;
	t_bomb				bomb;
	t_gun				gun;
	t_vapor				*vapor;
	t_cigs				*cigs;
}						t_wolf;

void					cigs_suite(t_wolf *env);
void					cigs(t_wolf *env);
int						initcigs(t_wolf *env);
void					cigs_animation(t_wolf *env);
int						k_hook3(int keycode, t_wolf *env);
void					k_hook2(int keycode, t_wolf *env);
void					do_sound(t_wolf *env);
int						key_hook(int keycode, t_wolf *env);
int						loop_hook(t_wolf *env);
int						lauchgame(t_wolf *env);
void					set_game(t_wolf *env);
void					mlx_pixel_to_image(int x, int y,
		t_wolf *env, int color);
int						lauchfactory(t_wolf *env);
int						init(t_wolf *env);
void					init_file(t_wolf *env);
int						init_text(t_wolf *env);
int						get_texture_color(t_wolf *env, int id);
void					mlx_text_to_img(t_wolf *env);
void					hud(t_wolf *env);
int						k_hook(int keycode, t_wolf *env);
void					*map(void);
void					wolf_init(t_wolf *env, int x);
void					wolf_step(t_wolf *env);
int						get_floor_color(t_wolf *env, int id);
void					wolf_wall(t_wolf *env);
void					wolf_stripe(t_wolf *env);
int						escape(t_wolf *env);
void					wolf_draw(t_wolf *env, int x);
void					put_floor(t_wolf *env, int x, int y);
void					draw_floor(t_wolf *env, int x, int y);
void					menu_game(t_wolf *env);
int						gere_expose2(t_wolf *env);
int						gere_expose(t_wolf *env);
void					bomb_win(t_wolf *env);
int						gere_expose3(t_wolf *env);
void					gun(t_wolf *env);
int						initgun(t_wolf *env);
int						init_vapor_text(t_wolf *env);
void					draw_floor_vapor(t_wolf *env, int x, int y);
void					vape(t_wolf *env);
void					put_floor_vapor(t_wolf *env, int x, int y);
int						init_modif(t_wolf *env);

#endif
