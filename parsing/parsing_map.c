/* ************************************************************************** */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:13 by atucci            #+#    #+#             */
/*   Updated: 2025/02/25 17:19:11 by atucci           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

//7
static int	count_elements_wrap(char **matrix, t_setting *set)
{
	remove_new_line(matrix, ' ', '\n');
	if (count_elements(matrix, set))
		return (free_string_array(matrix), 1);
	return (free_string_array(matrix), 0);
}

static void	clear_gnl_buffer(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
	}
}

static int	open_and_count(char *filename, t_setting *set)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (count_elements_wrap(ft_split(line, ' '), set) == 1)
		{
			i = -42;
			clear_gnl_buffer(fd);
			break ;
		}
		free(line);
	}
	free(line);
	return (close(fd), i);
}

static int	create_from_line(char **matrix, t_setting *set)
{
	int	result;

	remove_new_line(matrix, ' ', '\n');
	result = create_setting(matrix, set);
	free_string_array(matrix);
	if (result == -1)
	{
		ft_printf("%screate_from_line FAILED:%s\t", RED, RESET);
		free_struct(set);
		return (-42);
	}
	return (0);
}

//4
//free bc there is get_next_line
/*		if (count_elements_wrap(ft_split(line, ' '), set) == 1)
		{
			i = -42;
			clear_gnl_buffer(fd);
			break ;
*/
static int	parse_map(char *filename, t_setting *set)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	if (open_and_count(filename, set) == -42)
		return (-42);
	ft_printf("%sfinished%s READING THE MAP 1 TIME\n", BG_GREEN, BG_RESET);
	struct_status(set);
	if (missing_elem(set) == -42)
		return (-42);
	alloc_struct_elem(set);
	fd = open(filename, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (create_from_line(ft_split(line, ' '), set) == -42)
		{
			i = -42;
			clear_gnl_buffer(fd);
			break ;
		}
		free(line);
	}
	free(line);
	return (close(fd), i);
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
		if (parse_map(filename, set) == -42)
			return (close(fd), -1);
		return (close(fd), 0);
	}
}
