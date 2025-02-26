/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 10:08:09 by atucci            #+#    #+#             */
/*   Updated: 2025/02/27 15:18:44 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*1) for the sphere, validating sphere */
int	validate_sphere(char **details)
{
	if (lenght_string_array(details) != 4)
	{
		print_string_array(details);
		return (error_msg("VALIDATE SPHERE: needs 4 parameters\n"), -1);
	}
	if (valid_vector(details[1]))
		return (error_msg("VALIDATE SPHERE: Invalid sphere center\n"), -1);
	if (valid_for_atof(details[2]))
		return (error_msg("VALIDATE SPHERE: Invalid sphere diameter\n"), -1);
	if (valid_color_string(details[3]))
		return (error_msg("VALIDATE SPHERE: Invalid sphere color"), -1);
	return (0);
}

///*2) for the plane, validating the plane */
int	validate_plane(char **details)
{
	if (lenght_string_array(details) != 4)
	{
		print_string_array(details);
		return (error_msg("VALIDATE PLANE: needs 4 parameters"), -1);
	}
	if (valid_vector(details[1]))
		return (error_msg("VALIDATE PLANE: Invalid plane point\n"), -1);
	if (valid_vector(details[2]) && valid_normal_vector(details[2]))
		return (error_msg("VALIDATE PLANE: Invalid plane normal\n"), -1);
	if (valid_color_string(details[3]))
		return (error_msg("VALIDATE PLANE: Invalid plane color\n"), -1);
	return (0);
}

///*3) for the cylinder, validating the field*/
int	validate_cylinder(char **details)
{
	if (lenght_string_array(details) != 6)
	{
		print_string_array(details);
		return (error_msg("VALIDATE CYLINDER: needs 4 parameters\n"), -1);
	}
	if (valid_vector(details[1]) || valid_vector(details[2]))
		return (error_msg("VALIDATE CYLINDER: Invalid center or axis\n"), -1);
	if (valid_for_atof(details[3]) || valid_for_atof(details[4]))
		return (error_msg("VALIDATE CYLINDER: Invalid diameter/height\n"), -1);
	if (valid_color_string(details[5]))
		return (error_msg("VALIDATE CYLINDER: Invalid color\n"), -1);
	return (0);
}

//4) for validate the camera, validating the field
//TODO: implement additional check
int	validate_camera(char **details)
{
	if (lenght_string_array(details) != 4)
	{
		print_string_array(details);
		return (error_msg("VALIDATE CAMERA: needs 4 parameters\n"), -1);
	}
	if (valid_vector(details[1]))
		return (error_msg("VALIDATE CAMERA: Invalid viewpoint\n"), -1);
	if (valid_vector(details[2]) || valid_normal_vector(details[2]))
		return (error_msg("VALIDATE CAMERA: Invalid orientation\n"), -1);
	if (valid_fov_atoi(details[3]) && valid_fov(details[3]))
		return (error_msg("VALIDATE CAMERA: Invalid FOV\n"), -1);
	return (0);
}

//5) for validate the light
//TODO: implement additional check
int	validate_light(char **details)
{
	if (lenght_string_array(details) != 4)
	{
		print_string_array(details);
		return (error_msg("VALIDATE LIGHT: light needs 4 parameters\n"), -1);
	}
	if (valid_vector(details[1]))
		return (error_msg("VALIDATE LIGHT: Invalid light position\n"), -1);
	if (valid_for_atof(details[2]) || valid_ratio(details[2]))
		return (error_msg("VALIDATE LIGHT: Invalid light brightness\n"), -1);
	if (valid_color_string(details[3]))
		return (error_msg("VALIDATE LIGHT: Invalid light color\n"), -1);
	return (0);
}

//6) for validate the amb_light
//TODO: implement additional check
int	validate_amb_light(char **details)
{
	if (lenght_string_array(details) != 3)
	{
		print_string_array(details);
		return (error_msg("VALIDATE AMB_LIGHT: needs 3 parameters\n"), -1);
	}
	if (valid_for_atof(details[1]) || valid_ratio(details[1]))
		return (error_msg("VALIDATE AMB_LIGHT: Invalid amb_light ratio\n"), -1);
	if (valid_color_string(details[2]))
		return (error_msg("VALIDATE AMB_LIGHT: Invalid amb_light color\n"), -1);
	return (0);
}
