/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 15:06:37 by atucci            #+#    #+#             */
/*   Updated: 2024/09/16 09:42:24 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

double	**matrix_rotation_x(double radians)
{
	double	**matrix;

	matrix = malloc_matrix(4, 4);
	create_identity_matrix(matrix);
	matrix[1][1] = cos(radians);
	matrix[1][2] = -1 * sin(radians);
	matrix[2][1] = sin(radians);
	matrix[2][2] = cos(radians);
	return (matrix);
}

double	**matrix_rotation_y(double radians)
{
	double	**matrix;

	matrix = malloc_matrix(4, 4);
	create_identity_matrix(matrix);
	matrix[0][0] = cos(radians);
	matrix[0][2] = sin(radians);
	matrix[2][0] = -1 * sin(radians);
	matrix[2][2] = cos(radians);
	return (matrix);
}

double	**matrix_rotation_z(double radians)
{
	double	**matrix;

	matrix = malloc_matrix(4, 4);
	create_identity_matrix(matrix);
	matrix[0][0] = cos(radians);
	matrix[0][1] = -1 * sin(radians);
	matrix[1][0] = sin(radians);
	matrix[1][1] = cos(radians);
	return (matrix);
}
