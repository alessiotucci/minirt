/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 11:22:13 by atucci            #+#    #+#             */
/*   Updated: 2025/02/26 12:58:51 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 
 * return 0 == 0k!
 * return 1 == Ko!
*/

int	valid_vector(char *str)
{
	(void)str;
	return (error_msg("VALIDATE VECTOR: needs 4 parameters\n"), -1);
}

int	valid_for_atof(char *str)
{
	(void)str;
	return (error_msg("VALIDATE FOR ATOF: needs 4 parameters\n"), -1);
}

int	valid_color_string(char *str)
{
	(void)str;
	return (error_msg("VALIDATE COLOR STRING: needs 4 parameters\n"), -1);
}

int	valid_fov_atoi(char *str)
{
	(void)str;
	return (error_msg("VALIDATE FOV ATOI: needs 4 parameters\n"), -1);
}


