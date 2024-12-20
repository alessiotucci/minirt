/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:59:25 by atucci            #+#    #+#             */
/*   Updated: 2024/12/18 14:31:40 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*static void	*ft_free_null(char **buf, char **ptr, char **other_ptr) ORIGINALE
{
	if ((*buf) == NULL)
		(*buf) = NULL;
	else
		free((*buf));
	(*buf) = NULL;
	if (ptr != NULL)
	{
		if ((*ptr) == NULL)
			(*ptr) = NULL;
		else
			free((*ptr));
		(*ptr) = NULL;
	}
	if (other_ptr != NULL)
	{
		if ((*other_ptr) == NULL)
			(*other_ptr) = NULL;
		else
			free((*other_ptr));
		(*other_ptr) = NULL;
	}
	return (NULL);
}*/

static void *ft_free_null(char **buf, char **ptr, char **other_ptr)
{
    if (buf && *buf) {
        free(*buf);
        *buf = NULL;
    }
    if (ptr && *ptr) {
        free(*ptr);
        *ptr = NULL;
    }
    if (other_ptr && *other_ptr) {
        free(*other_ptr);
        *other_ptr = NULL;
    }
    return NULL;
}


static ssize_t	get_length(char *buf, int kind_of_calculation)
{
	ssize_t	length;

	length = 0;
	if (buf == NULL)
		return (0);
	while ((buf[length]) && (buf[length] != 10))
		length++;
	if ((kind_of_calculation == 1) && (buf[length] == 10))
		return (1);
	if ((kind_of_calculation == 1) && (buf[length] != 10))
		return (0);
	if ((kind_of_calculation == 2) && (buf[length] == 10))
		return (length + 1);
	while ((buf[length]))
		length++;
	return (length);
}


static char	*get_realloc(char **buf, int kind_of_alloc)
{
	char	*new_buf;
	ssize_t	counter;

	counter = 0;
	if (kind_of_alloc == 0)
		new_buf = (char *)malloc(get_length((*buf), 0) + BUFFER_SIZE + 1);
	else if (kind_of_alloc == 3)
	{
		if (((*buf)[0]) != 0)
			return (*buf);
		else
			return (ft_free_null(buf, NULL, NULL));
	}
	else
		new_buf = (char *)malloc(get_length((*buf), 0) + 1);
	if (new_buf == NULL)
		return (ft_free_null(buf, NULL, NULL));
	while (((*buf) != NULL) && ((*buf)[counter]))
	{
		new_buf[counter] = ((*buf)[counter]);
		counter++;
	}
	new_buf[counter] = 0;
	(*buf) = ft_free_null(buf, NULL, NULL);
	return (new_buf);
}

/*static char *get_realloc(char **buf, int kind_of_alloc) possibile modifica
{
    char *new_buf;
    ssize_t counter = 0;
    ssize_t new_size;

    // Determina la dimensione del nuovo buffer
    if (kind_of_alloc == 0) {
        new_size = get_length(*buf, 0) + BUFFER_SIZE + 1;
    } else if (kind_of_alloc == 3) {
        if (*buf && (*buf)[0] != '\0') {
            return *buf; // Ritorna direttamente se il buffer esiste e non è vuoto
        } else {
            return ft_free_null(buf, NULL, NULL); // Libera se il buffer è vuoto o NULL
        }
    } else {
        new_size = get_length(*buf, 0) + 1;
    }

    // Alloca memoria per il nuovo buffer
    new_buf = (char *)malloc(new_size);
    if (new_buf == NULL)
        return ft_free_null(buf, NULL, NULL); // Libera il buffer precedente in caso di errore

    // Copia i dati dal vecchio buffer al nuovo buffer
    while ((*buf != NULL) && ((*buf)[counter]) && (counter < new_size - 1)) {
        new_buf[counter] = (*buf)[counter];
        counter++;
    }

    // Aggiungi il terminatore di stringa al nuovo buffer
    new_buf[counter] = '\0';

    // Libera il vecchio buffer solo se non è NULL
    if (*buf) {
        ft_free_null(buf, NULL, NULL);
    }

    return new_buf;
}*/



static char	*get_return(char **buf)
{
	char	*line;
	char	*temp;
	ssize_t	counter;
	ssize_t	line_length;

	line_length = get_length((*buf), 2);
	line = (char *)malloc(line_length + 1);
	temp = (char *)malloc(get_length((*buf), 0) - line_length + 1);
	if ((line == NULL) || (temp == NULL) || ((*buf) == NULL))
		return (ft_free_null(buf, &line, &temp));
	counter = 0;
	while (counter < line_length)
	{
		line[counter] = ((*buf)[counter]);
		counter++;
	}
	line[counter] = 0;
	counter = 0;
	while (((*buf)[line_length]) != 0)
		temp[counter++] = ((*buf)[line_length++]);
	temp[counter] = 0;
	(*buf) = ft_free_null(buf, NULL, NULL);
	(*buf) = get_realloc(&temp, 3);
	return (get_realloc(&line, 3));
}


/*static char *get_return(char **buf) modifica potenziale
{
    char *line = NULL;
    char *temp = NULL;
    ssize_t counter;
    ssize_t line_length;

    line_length = get_length((*buf), 2);
    line = (char *)malloc(line_length + 1);
    temp = (char *)malloc(get_length((*buf), 0) - line_length + 1);
    if (line == NULL || temp == NULL || *buf == NULL) {
        ft_free_null(buf, &line, &temp);
        return NULL;
    }

    // Copia i dati in `line` e `temp`
    for (counter = 0; counter < line_length; counter++)
        line[counter] = (*buf)[counter];
    line[counter] = '\0';

    counter = 0;
    while ((*buf)[line_length])
        temp[counter++] = (*buf)[line_length++];
    temp[counter] = '\0';

    // Libera `(*buf)` e assegna il risultato di `get_realloc`
    free(*buf);
    *buf = get_realloc(&temp, 3);
    if (*buf == NULL) {
        free(line);
        return NULL;
    }

    // Riassegna e restituisce il risultato di `get_realloc`
    char *result = get_realloc(&line, 3);
    if (result == NULL) {
        free(*buf);
        return NULL;
    }
    return result;
}*/



char	*get_next_line(int fd)
{
	static char	*buf;
	ssize_t		size;
	ssize_t		count;

	if ((fd < 0) || (fd > 4096) || (BUFFER_SIZE <= 0))
		return (NULL);
	size = get_length(buf, 0);
	count = 1;
	while ((!(get_length(buf, 1))) && (count > 0))
	{
		buf = get_realloc(&buf, 0);
		if (buf == NULL)
			return (NULL);
		count = read(fd, &(buf[size]), BUFFER_SIZE);
		if (count < 0)
			return (ft_free_null(&buf, NULL, NULL));
		size = (size + count);
		if (count != 0)
			buf[size] = 0;
		if ((count < BUFFER_SIZE) || (count == 0))
			break ;
	}
	if ((count < BUFFER_SIZE) || (count == 0))
		buf = get_realloc(&buf, 1);
	return (get_return(&buf));
}
