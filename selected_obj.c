/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selected_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:53:10 by atucci            #+#    #+#             */
/*   Updated: 2025/02/13 15:50:40 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minirt.h"

int	is_selected_null(t_selected_obj obj)
{
	return (obj.index == -1 || obj.type == T_NULL);
}

void	reset_selected_object(t_selected_obj selected)
{
	selected.index = -1;
	selected.type = T_NULL;
}

