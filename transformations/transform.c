/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:27:11 by ftroise           #+#    #+#             */
/*   Updated: 2024/06/24 16:04:06 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void set_transform(t_sphere *sphere, double **matrix)
{
    // Deallochiamo  la matrice di trasformazione esistente se gia presente cosi evitiamo le leccate di palle 
    if (sphere->transform != NULL)
        free_heap_matrix(sphere->transform, 4);
    sphere->transform = copy_matrix(4, 4, matrix);
}

void init_identity_matrix(int rows, int cols, double **matrix)
{
    int i;
    int j;
    
    i = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            if (i == j)
                matrix[i][j] = 1.0;  // Diagonal elements set to 1
            else 
                matrix[i][j] = 0.0;  // Non-diagonal elements set to 0
            j++;
        }
        i++;
    }
}

void transform_sphere(t_sphere *sphere, double **matrix)
{
    t_vector center = sphere->center;
    t_vector new_center;

    new_center.x = matrix[0][0] * center.x + matrix[0][1] * center.y + matrix[0][2] * center.z + matrix[0][3] * center.w;
    new_center.y = matrix[1][0] * center.x + matrix[1][1] * center.y + matrix[1][2] * center.z + matrix[1][3] * center.w;
    new_center.z = matrix[2][0] * center.x + matrix[2][1] * center.y + matrix[2][2] * center.z + matrix[2][3] * center.w;
    new_center.w = matrix[3][0] * center.x + matrix[3][1] * center.y + matrix[3][2] * center.z + matrix[3][3] * center.w;

    sphere->center = new_center;
}



void sphere_test(t_sphere *sphere, double **translation_matrix)
{
    // Creazione della matrice di trasformazione desiderata
    init_identity_matrix(4, 4, translation_matrix);
    translation_matrix[0][3] = 1.0; // Esempio di traslazione lungo l'asse x

    // Applicazione della trasformazione alla sfera
    set_transform(sphere, translation_matrix);
    transform_sphere(sphere, sphere->transform);

    // Esempio di output dei nuovi attributi della sfera dopo la trasformazione
    printf("Transformed sphere center: (%f, %f, %f)\n", sphere->center.x, sphere->center.y, sphere->center.z);

    // Liberazione della memoria della matrice di trasformazione
    if (sphere->transform != NULL)
        free_heap_matrix(sphere->transform, 4);
    free_heap_matrix(translation_matrix, 4);
}
