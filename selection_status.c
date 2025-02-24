/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_status.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:06:40 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:13:27 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"
//5
//TODO: interesting function!
/* ---------------------- VECTOR FORMATTING ---------------------- */
static char	*vector_to_str(t_vector vec)
{
	char	*x;
	char	*y;
	char	*z;
	char	*temp;
	char	*temp2;

	x = ft_itoa((int)vec.x);
	y = ft_itoa((int)vec.y);
	z = ft_itoa((int)vec.z);
	temp = ft_strjoin(x, " ");
	temp2 = ft_strjoin(temp, y);
	free(temp);
	temp = ft_strjoin(temp2, " ");
	free(temp2);
	temp2 = ft_strjoin(temp, z);
	free(temp);
	free(x);
	free(y);
	free(z);
	return (temp2);
}

//4
static char	*vector_to_labeled_str(char *label, t_vector vec)
{
	char	*vec_str;
	char	*full_str;

	vec_str = vector_to_str(vec);
	full_str = ft_strjoin(label, vec_str);
	free(vec_str);
	return (full_str);
}

//3
/* ---------------------- CAMERA INFO FORMATTING ---------------------- */
char	*camera_info_str(t_camera *cam)
{
	char	*view_str;
	char	*fov_str;
	char	*orient_str;
	char	*temp;
	char	*final;

	view_str = vector_to_labeled_str("Camera: ", cam->viewpoint);
	fov_str = ft_strjoin("FOV: ", ft_itoa(cam->fov));
	orient_str = vector_to_labeled_str("| ", cam->orientation);
	final = ft_strjoin(view_str, fov_str);
	free(view_str);
	free(fov_str);
	temp = ft_strjoin(final, orient_str);
	free(final);
	free(orient_str);
	return (temp);
}

//2
void	my_sprintf(char *buffer, char *key, char *old_value, char *new_value)
{
	int	bufflen;

	bufflen = ft_strlen(buffer);
	ft_strlcpy(buffer, key, ft_strlen(key) + 1);
	ft_strlcat(buffer, "=", bufflen + 2);
	if (old_value != NULL)
		ft_strlcat(buffer, old_value, ft_strlen(old_value) + bufflen + 1);
	ft_strlcat(buffer, new_value, ft_strlen(new_value) + bufflen + 1);
}

//1
/* ---------------------- SELECTION STATUS FORMATTING ---------------------- */
char	*get_selection_status(t_selected_obj selected)
{
	const char	*type_str;
	char		*buffer;
	char		*full_str;

	if (is_selected_null(&selected))
		return (ft_strdup("Selected obj: NULL"));
	type_str = type_to_string(selected.type);
	full_str = ft_strjoin("Selected: ", type_str);
	if (!full_str)
		return (ft_strdup("Selection error"));
	buffer = malloc(ft_strlen(full_str) + 1);
	if (!buffer)
		return (free(full_str), ft_strdup("Selection error"));
	my_sprintf(buffer, full_str, "", "");
	free(full_str);
	return (buffer);
}
