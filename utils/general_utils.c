/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:48:45 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/15 22:03:43 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../fractol.h"

size_t ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	error_handler(int flag)
{
	if (flag == MLX_ERROR)
		printf("MiniLibX Error, please try again\n");
	else if (flag == INPUT_ERROR)
		printf("Incorrect input\n");
	exit(EXIT_FAILURE);
}
