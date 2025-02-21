/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shearing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 13:41:57 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:08:59 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//TODO: check the leaks with this command
// valgrind   --leak-check=full --show-leak-kinds=all ./a.out
t_vector	shearing(t_vector origin, double value[6])
{
	double		**matrix;
	t_vector	result;

	matrix = malloc_matrix(4, 4);
	create_identity_matrix(matrix);
	matrix[0][1] = value[0];
	matrix[0][2] = value[1];
	matrix[1][0] = value[2];
	matrix[1][2] = value[3];
	matrix[2][0] = value[4];
	matrix[2][1] = value[5];
	result = matrix_x_vector(matrix, origin);
	return (free_heap_matrix(matrix, 4), result);
}
