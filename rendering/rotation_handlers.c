/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:06:36 by atucci            #+#    #+#             */
/*   Updated: 2025/02/11 18:46:05 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
// Rotation handlers

// Helper function to apply transformation matrix to an object
// sicuro va in segfault
void change_size(t_object *obj, int flag)
{
    if (obj->type == T_CYLINDER)
    {
        t_cylinder *cyl = (t_cylinder *)obj->address;
        if (flag)
        {
            // Increase both diameter and height
            cyl->diameter += 1.0;
            cyl->height += 1.0;
        }
        else
        {
            // Decrease with minimum size protection
            if (cyl->diameter > 1.0)
                cyl->diameter -= 1.0;
            if (cyl->height > 1.0)
                cyl->height -= 1.0;
        }
        // Update cylinder bounds if needed
        cyl->min = -cyl->height/2;
        cyl->max = cyl->height/2;
    }
    else if (obj->type == T_SPHERE)
    {
        t_sphere *sphere = (t_sphere *)obj->address;
        if (flag)
        {
            sphere->diameter += 1.0;
        }
        else
        {
            if (sphere->diameter > 1.0)
                sphere->diameter -= 1.0;
        }
    }
    else if (obj->type == T_PLANE)
    {
        // Planes are infinite, but we could scale a pattern if they have one
        printf("Planes cannot be resized in this implementation\n");
    }
    else
    {
		type_to_string(obj->type);
        printf("%sUnsupported object type for resizing%s\n", RED, RESET);
    }
}

static void	apply_transformation(t_object *obj, double **new_transform)
{
	void	*original;
	double	**old_matrix;

	if (obj->type == T_CYLINDER)
	{
		original = ((t_cylinder *)obj->address);
		old_matrix = ((t_cylinder *)original)->transform;
		((t_cylinder *)original)->transform = multiply_matrix(4, 4, new_transform, old_matrix);
		free_heap_matrix(old_matrix, 4);
	}
	else if (obj->type == T_SPHERE)
	{
		original = ((t_sphere *)obj->address);
		old_matrix = ((t_sphere *)original)->transform;
		((t_sphere *)original)->transform = multiply_matrix(4, 4, new_transform, old_matrix);
		free_heap_matrix(old_matrix, 4);
		// Similar implementation for spheres
	}
	else if (obj->type == T_PLANE)
	{
		original = ((t_plane *)obj->address);
		old_matrix = ((t_plane *)original)->transform;
		((t_plane *)original)->transform = multiply_matrix(4, 4, new_transform, old_matrix);
		free_heap_matrix(old_matrix, 4);
		// Similar implementation for planes
	}
	free_heap_matrix(new_transform, 4);
}

void	handle_x_rotation(t_mlx *data, int direction)
{
	double	**rotation;
	double	angle;

	angle = M_PI/16 * direction; // 22.5 degree steps
	rotation = matrix_rotation_x(angle);
	apply_transformation(data->selected_object, rotation);
}

void	handle_y_rotation(t_mlx *data, int direction)
{
	double	**rotation;
	double	angle;

	angle = M_PI/16 * direction;
	rotation = matrix_rotation_y(angle);
	apply_transformation(data->selected_object, rotation);
}

void	handle_z_rotation(t_mlx *data, int direction)
{
	double	**rotation;
	double	angle;

	angle = M_PI/16 * direction;
	rotation = matrix_rotation_z(angle);
	apply_transformation(data->selected_object, rotation);
}
