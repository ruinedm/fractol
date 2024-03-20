/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:53:05 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/20 01:38:48 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ITERATIONS 100
#define CONVERGE -1
#define DESTROY_NOTIFY 17

enum				e_MOUSE_CODES
{
	ZOOM_OUT = 4,
	ZOOM_IN = 5,
};

enum				e_KEY_CODES
{
	ESC = 53,
	ENTER = 36,
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123,
	SPACE = 49
};

enum				e_ERROR_FALGS
{
	MLX_ERROR,
	INPUT_ERROR
};

enum				e_FRACTALS
{
	MANDELBROT,
	JULIA,
	TRICORN
};

typedef struct s_complex
{
	double			real;
	double			imaginary;
}					t_complex;

typedef struct s_fractal
{
	t_complex		start;
	t_complex		end;
	double			shift_x;
	double			shift_y;
	double			zoom_factor;
	double			julia_real;
	double			julia_imaginary;
	double			random_color;
	int				fractal_type;
	int				random_flag;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_fractal;

typedef struct s_trgb
{
	unsigned char	transparency;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_trgb;

// GENERAL UTILS
size_t				ft_strlen(char *str);
void				error_handler(int flag);
void				reset_struct(t_fractal *fractal);
int					ft_strcmp(const char *s1, const char *s2);

// STUDY UTILS
int					analyze_z(int x, int y, t_fractal *fractal);
void				convert_to_complex(int x, int y, t_complex *c,
						t_fractal *fractal);

// HOOK UTILS
int					key_hook(int keycode, t_fractal *fractal);
int					mouse_hook(int mousecode, int x, int y, t_fractal *fractal);
int					button_close(t_fractal *fractal);

// RENDER UTILS
void				render_fractal(t_fractal *fractal);

// CONVERSTION UTILS
double				ft_atof(char *str);

// COLOR UTILS
int					create_trgb(unsigned char t, unsigned char r,
						unsigned char g, unsigned char b);
unsigned char		get_t(int trgb);
unsigned char		get_r(int trgb);
unsigned char		get_g(int trgb);
unsigned char		get_b(int trgb);