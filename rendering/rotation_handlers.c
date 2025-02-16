/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_handlers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:06:36 by atucci            #+#    #+#             */
/*   Updated: 2025/02/14 18:19:19 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#define DIAMETER_DELTA 1.0
#define HEIGHT_DELTA 2.0
#define ANGLE_DELTA (M_PI / 36)  // 5 degrees in radians
// Increase the diameter (for spheres and cylinders)
void increase_object_diameter(t_mlx *data)
{
    if (data->selected.type == T_SPHERE)
    {
        t_sphere *sp = data->setting->spheres[data->selected.index];
        sp->diameter += DIAMETER_DELTA;
        printf("%sIncreased sphere diameter to: %lf%s\n", YELLOW, sp->diameter, RESET);
    }
    else if (data->selected.type == T_CYLINDER)
    {
        t_cylinder *cy = data->setting->cylinders[data->selected.index];
        cy->diameter += DIAMETER_DELTA;
        printf("%sIncreased cylinder diameter to: %lf%s\n", YELLOW, cy->diameter, RESET);
    }
    else
    {
        printf("increase_object_diameter applicable only to spheres and cylinders.\n");
    }
}

// Decrease the diameter (for spheres and cylinders)
void decrease_object_diameter(t_mlx *data)
{
    if (data->selected.type == T_SPHERE)
    {
        t_sphere *sp = data->setting->spheres[data->selected.index];
        sp->diameter -= DIAMETER_DELTA;
        if (sp->diameter <= 1)
            sp->diameter = 1;
        printf("%sDecreased sphere diameter to: %lf%s\n", YELLOW, sp->diameter, RESET);
    }
    else if (data->selected.type == T_CYLINDER)
    {
        t_cylinder *cy = data->setting->cylinders[data->selected.index];
        cy->diameter -= DIAMETER_DELTA;
        if (cy->diameter <= 1)
            cy->diameter = 1;
        printf("%sDecreased cylinder diameter to: %lf%s\n", YELLOW, cy->diameter, RESET);
    }
    else
    {
        printf("decrease_object_diameter applicable only to spheres and cylinders.\n");
    }
}

// Increase the height of a cylinder.
void increase_cylinder_height(t_mlx *data)
{
    if (data->selected.type == T_CYLINDER)
    {
        t_cylinder *cy = data->setting->cylinders[data->selected.index];
        cy->height += HEIGHT_DELTA;
		update_cylinder(cy);
        printf("Increased cylinder height to: %lf\n", cy->height);
    }
    else
    {
        printf("increase_cylinder_height applicable only to cylinders.\n");
    }
}

// Decrease the height of a cylinder.
void decrease_cylinder_height(t_mlx *data)
{
    if (data->selected.type == T_CYLINDER)
    {
        t_cylinder *cy = data->setting->cylinders[data->selected.index];
        cy->height -= HEIGHT_DELTA;
		update_cylinder(cy);
        if (cy->height < 1.0)
            cy->height = 1.0;
        printf("Decreased cylinder height to: %lf\n", cy->height);
    }
    else
    {
        printf("decrease_cylinder_height applicable only to cylinders.\n");
    }
}

// Rotate the object's axis or normal positively (about the X axis for example).
void rotate_object_axis_positive(t_mlx *data)
{
    if (data->selected.type == T_PLANE)
    {
        t_plane *pl = data->setting->planes[data->selected.index];
        pl->normal = rotation_x(pl->normal, ANGLE_DELTA);
        printf("Rotated plane normal positively to: (%lf, %lf, %lf)\n",
               pl->normal.x, pl->normal.y, pl->normal.z);
    }
    else if (data->selected.type == T_CYLINDER)
    {
        t_cylinder *cy = data->setting->cylinders[data->selected.index];
        cy->axis = rotation_x(cy->axis, ANGLE_DELTA);
        printf("Rotated cylinder axis positively to: (%lf, %lf, %lf)\n",
               cy->axis.x, cy->axis.y, cy->axis.z);
    }
    else
    {
        printf("rotate_object_axis_positive applicable only to planes and cylinders.\n");
    }
}

// Rotate the object's axis or normal negatively (about the X axis for example).
void rotate_object_axis_negative(t_mlx *data)
{
    if (data->selected.type == T_PLANE)
    {
        t_plane *pl = data->setting->planes[data->selected.index];
        pl->normal = rotation_x(pl->normal, -ANGLE_DELTA);
        printf("Rotated plane normal negatively to: (%lf, %lf, %lf)\n",
               pl->normal.x, pl->normal.y, pl->normal.z);
    }
    else if (data->selected.type == T_CYLINDER)
    {
        t_cylinder *cy = data->setting->cylinders[data->selected.index];
        cy->axis = rotation_x(cy->axis, -ANGLE_DELTA);
        printf("Rotated cylinder axis negatively to: (%lf, %lf, %lf)\n",
               cy->axis.x, cy->axis.y, cy->axis.z);
    }
    else
    {
        printf("rotate_object_axis_negative applicable only to planes and cylinders.\n");
    }
}

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
