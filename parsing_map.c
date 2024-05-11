/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:13 by atucci            #+#    #+#             */
/*   Updated: 2024/05/11 14:36:16 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

//TODO: 123 change the file locations
static void	split_line123(char **matrix, t_setting *set)
{
	(void)set;
	remove_new_line(matrix, ' ', '\n');
	count_elements(matrix, set);
	free_string_array(matrix);
}
//TODO: 123 change the file locations
static int counting_123(char *filename, t_setting *set)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		split_line123(ft_split(line, ' '), set);
		line = get_next_line(fd);
	}
	//close(fd);TODO fix it
	return (close(fd));
}

static void	split_line(char **matrix, t_setting *set)
{
	(void)set;
	remove_new_line(matrix, ' ', '\n');
	create_setting(matrix, set);
	free_string_array(matrix);
}

//4
static int parse_map(char *filename, t_setting *set)
{
	char	*line;
	int		fd;

	//first thing is counting right?
	counting_123(filename, set);
	ft_printf("%sfinished%s READING THE MAP 1 TIME\n", BG_GREEN, BG_RESET);
	struct_status(set);
	alloc_struct_elem(set);
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	//replace_me(line, ' ', '\n');
	while (line != NULL)
	{
		//replace_me(line, ' ', '\n');
		split_line(ft_split(line, ' '), set);
		line = get_next_line(fd);
	}
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
		//parse_map(fd, set);
		parse_map(filename, set);
		return (close(fd), 0);
	}
	
}

//2
static int	check_the_extension(char *filename, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(ext);
	j = ft_strlen(filename);
	if (i >= j)
		return (-1 * ft_printf("%sfilename too short%s\n", RED, RESET));
	while (i > 0)
	{
		if (ext[i] != filename[j])
			return (ft_printf("file doesn't have the '%s' extension\n", ext));
		i--;
		j--;
	}
	return (0 * ft_printf("%scorrect extension%s\n", GREEN, RESET));
}

//1
int	parsing_map(char *map, t_setting *set)
{
	if (check_the_extension(map, ".rt") == 0)
		return (open_map(map, set));
	else
		return (-1);
}
