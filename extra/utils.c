/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 21:25:59 by atucci            #+#    #+#             */
/*   Updated: 2025/02/27 15:13:05 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//5
int	my_strcmp(const char *str1, const char *str2)
{
	size_t	count;

	count = 0;
	while (str1[count] != '\0' || str2[count] != '\0')
	{
		if (str1[count] > str2[count])
			return (1);
		else if (str1[count] < str2[count])
			return (-1);
		count++;
	}
	return (0);
}

//4
int	check_null_array(char **array)
{
	if (array == NULL)
	{
		ft_printf("%s NULL, SOMETHING IS WRONG%s\n", RED, RESET);
		return (1);
	}
	return (0);
}

//3) might add a parameter for clarity
void	print_string_array(char **array)
{
	int	i;

	i = 0;
	if (check_null_array(array))
		return ;
	ft_printf("[i] [string]\n");
	while (array[i] != NULL)
	{
		ft_printf("[%s%d%s][%s]   ", GREEN, i, RESET, array[i]);
		i++;
	}
	ft_printf("\n");
}

//2
int	free_string_array(char **array)
{
	int	count;

	count = 0;
	if (check_null_array(array))
		return (1);
	while (array[count])
	{
		free(array[count]);
		count++;
	}
	free(array);
	return (0);
}

/*1 */
int	lenght_string_array(char **array)
{
	int	count;

	count = 0;
	if (check_null_array(array))
		return (-1);
	while (array[count] != NULL)
		count++;
	return (count);
}
