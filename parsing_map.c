/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atucci <atucci@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:13 by atucci            #+#    #+#             */
/*   Updated: 2024/05/11 10:05:04 by atucci           ###   ########.fr       */
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

/* Helper function, I will delete this later on */
static void struct_status(t_setting *set)
{
	ft_printf("\n\n------STRUCT STATUS -------\n");
	ft_printf("struct has [%d] lights\t  |\n", set->num_lights);
	ft_printf("struct has [%d] spheres \t  |\n", set->num_spheres);
	ft_printf("struct has [%d] planes \t  |\n", set->num_planes);
	ft_printf("struct has [%d] cylinders  |\n", set->num_cylinders);
	ft_printf("struct has [%d] cones bonus|\n", set->num_cones);
	ft_printf("---------------------------\n\n");
}

//TODO: 123 change the file locations
static void	split_line123(char **matrix, t_setting *set)
{
	(void)set;
	remove_new_line(matrix, ' ', '\n');
	count_elements(matrix, set);
	//create_setting(matrix, set);
	free_string_array(matrix);
}
//TODO: 123 change the file locations
static void	counting_123(int fd, t_setting *set)
{
	char	*line;
	
	line = get_next_line(fd);
	//replace_me(line, ' ', '\n');
	while (line != NULL)
	{
		//replace_me(line, ' ', '\n');
		split_line123(ft_split(line, ' '), set);
		line = get_next_line(fd);
	}
	return ;
}

static void	split_line(char **matrix, t_setting *set)
{
	(void)set;
	remove_new_line(matrix, ' ', '\n');
	//count_elements(matrix, set);
	struct_status(set);
	create_setting(matrix, set);
	free_string_array(matrix);
}
//4
static void	parse_map(int fd, t_setting *set)
{
	char	*line;
	
	//first thing is counting right?
	counting_123(fd, set);
	line = get_next_line(fd);
	//replace_me(line, ' ', '\n');
	while (line != NULL)
	{
		//replace_me(line, ' ', '\n');
		split_line(ft_split(line, ' '), set);
		line = get_next_line(fd);
	}
	struct_status(set);
	return ;
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
		parse_map(fd, set);
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
