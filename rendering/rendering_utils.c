/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:49:04 by atucci            #+#    #+#             */
/*   Updated: 2025/02/24 17:15:29 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//7
// Key codes are defined in your header.
// For example: ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN, PLUS, MINUS
void	select_light(t_selected_obj *selected)
{
	printf("%sSELECT light!%s\n", YELLOW, RESET);
	selected->index = 0;
	selected->type = T_LIGHT;
}

/* 6! move to another file */
int	cast_mouse_ray(int x, int y, t_mlx *mlx, t_setting *set)
{
	t_ray				ray;
	t_list_intersect	*all_intersections;
	t_intersection		*ht;

	printf("CAST_MOUSE_RAY!\n");
	ray = create_ray_from_camera2(mlx, x, y);
	all_intersections = intersect_world(set, ray);
	ht = hit_v2(all_intersections);
	if (ht != NULL)
	{
		mlx->selected = find_original(set, ht->obj.original_addr, ht->obj.type);
		ft_printf("Selected object: %p\n", ht->obj.original_addr);
	}
	else
	{
		reset_selected_object(&mlx->selected);
		ft_printf("Missed ray :(\n");
	}
	free_list(&all_intersections);
	return (0);
}
