/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:13 by atucci            #+#    #+#             */
/*   Updated: 2025/02/19 10:03:29 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//7
static void	count_elements_wrap(char **matrix, t_setting *set)
{
	remove_new_line(matrix, ' ', '\n');
	count_elements(matrix, set);
	free_string_array(matrix);
}

//6
static int	open_and_count(char *filename, t_setting *set)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count_elements_wrap(ft_split(line, ' '), set);
		free(line);
	}
	free(line);
	return (close(fd));
}

//5
static void	create_from_line(char **matrix, t_setting *set)
{
	remove_new_line(matrix, ' ', '\n');
	create_setting(matrix, set);
	free_string_array(matrix);
}

//4
//free bc there is get_next_line
static int	parse_map(char *filename, t_setting *set)
{
	char	*line;
	int		fd;

	open_and_count(filename, set);
	ft_printf("%sfinished%s READING THE MAP 1 TIME\n", BG_GREEN, BG_RESET);
	struct_status(set);
	alloc_struct_elem(set);
	fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		create_from_line(ft_split(line, ' '), set);
		free(line);
	}
	free(line);
	return (close(fd));
}

//3 
int	open_map(char *filename, t_setting *set)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_printf("%sError map: %s%s\n", RED, filename, RESET));
	else
	{
		parse_map(filename, set);
		return (close(fd), 0);
	}
}
