/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:53:05 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/13 22:44:32 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define MAX_ITERATIONS 200
# define CONVERGE -1

enum e_FRACTALS
{
	MANDELBROT,
	JULIA
};

typedef struct s_complex
{
	double real;
	double imaginary;
} t_complex;



typedef struct	s_fractal
{
	int		fractal_type;
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	zoom_factor;
}				t_fractal;

enum e_MOUSE_CODES
{
	ZOOM_OUT=4,
	ZOOM_IN=5,
};

enum e_KEY_CODES
{
	ESC=53,
	ENTER=36
};

typedef struct s_trgb
{
	unsigned char transparency;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} t_trgb;

int analyze_z(int x, int y, int fractal_type, int zoom_factor);

// COLOR UTILS
int create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);
