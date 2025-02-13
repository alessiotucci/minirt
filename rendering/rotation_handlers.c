/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:06:36 by atucci            #+#    #+#             */
/*   Updated: 2025/02/13 15:09:19 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
// Rotation handlers

// Helper function to apply transformation matrix to an object

void	handle_x_rotation(t_mlx *data, int direction)
{
	double	**rotation;(void)rotation;(void)data;
	double	angle;(void)angle;

	angle = M_PI/16 * direction; // 22.5 degree steps
	rotation = matrix_rotation_x(angle);
}

void	handle_y_rotation(t_mlx *data, int direction)
{
	double	**rotation;(void)rotation;(void)data;
	double	angle;(void)angle;

	angle = M_PI/16 * direction;
	rotation = matrix_rotation_y(angle);
}

void	handle_z_rotation(t_mlx *data, int direction)
{
	double	**rotation;(void)rotation;(void)data;
	double	angle;(void)angle;

	angle = M_PI/16 * direction;
	rotation = matrix_rotation_z(angle);
}
