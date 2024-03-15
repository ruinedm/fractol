/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:53:05 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/15 05:49:48 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
#include <unistd.h>

# define MAX_ITERATIONS 150
# define CONVERGE -1
# define DestroyNotify 17

enum e_FRACTALS
{
	MANDELBROT,
	JULIA,
	TRICORN
};

typedef struct s_complex
{
	double real;
	double imaginary;
} t_complex;



typedef struct	s_fractal
{
	double	shift_x;
	double	shift_y;
	int		fractal_type;
	double	zoom_factor;
	double	shift_margin;
	double	julia_real;
	double	julia_imaginary;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_fractal;

enum e_MOUSE_CODES
{
	ZOOM_OUT=4,
	ZOOM_IN=5,
};

enum e_KEY_CODES
{
	ESC=53,
	ENTER=36,
	UP=126,
	DOWN=125,
	RIGHT=124,
	LEFT=123,
	PLUS=24,
	MINUS=27
};

enum e_ERROR_FALGS
{
	MLX_ERROR,
	INPUT_ERROR
};

typedef struct s_trgb
{
	unsigned char transparency;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} t_trgb;

// GENERAL UTILS
void	error_handler(int flag);

int analyze_z(int x, int y, t_fractal *fractal);

// STR UTILS
int	ft_strcmp(const char *s1, const char *s2);

// HOOK UTILS
int	key_hook(int keycode, t_fractal *fractal); 
int mouse_hook(int mousecode, int x, int y, t_fractal *fractal);
int button_close(t_fractal *fractal);

//RENDER UTILS
void render_fractal(t_fractal *fractal);

// COLOR UTILS
int create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);
