/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_me.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 09:58:09 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 15:11:28 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
/* TODO: let's see if we can get rid of the \n char */
void	replace_me(char *str, char replacement, char to_replace)
{
	int		i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		if (str[i] == to_replace)
			str[i] = replacement;
		i++;
	}
}

//6
void	remove_new_line(char **matrix, char replacement, char to_replace)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		replace_me(matrix[i], replacement, to_replace);
		i++;
	}
}
