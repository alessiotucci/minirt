/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transformation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:25:33 by ftroise           #+#    #+#             */
/*   Updated: 2024/06/24 11:26:01 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"


t_ray transform(t_ray ray, double **matrix)
{
    t_ray transformed_ray;
    transformed_ray.origin = matrix_x_vector(matrix, ray.origin);
    transformed_ray.direction = matrix_x_vector(matrix, ray.direction);
    return transformed_ray;
}