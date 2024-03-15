/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:48:45 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/15 05:50:29 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../fractol.h"

void	error_handler(int flag)
{
	if(flag == MLX_ERROR)
		printf("MiniLibX Error, please try again\n");
	else if (flag == INPUT_ERROR)
		printf("Incorrect input\n");
	exit(EXIT_FAILURE);
}
