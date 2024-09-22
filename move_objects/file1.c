/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:32:44 by ftroise           #+#    #+#             */
/*   Updated: 2024/09/22 10:08:26 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

/*(partenza)static void find_intersections(t_ray ray, t_mlx *mlx, t_intersection_list *intersections)
{
    t_intersection_list *sphere_intersections;
    int                                     i;

    i = 0;
    while (i < mlx->setting->num_spheres)
    {
        sphere_intersections = intersect_sphere(*mlx->setting->spheres[i], ray);
        if (sphere_intersections)
        {
            add_intersections_to_list(intersections, sphere_intersections);
            free(sphere_intersections->intersections);
            free(sphere_intersections);
        }
        i++;
    }
}*/

 static void find_intersections(t_ray ray, t_mlx *mlx, t_intersection_list *intersections)
{

    printf(RED"\t\t\t\tPROVA TECNICA QUI CI 6\n\n\n");
    t_intersection_list *sphere_intersections;
    int i;

    i = 0;
    while (i < mlx->setting->num_spheres)
    {
        sphere_intersections = intersect_sphere(*mlx->setting->spheres[i], ray);
        if (sphere_intersections)
        {
            add_intersections_to_list(intersections, sphere_intersections);
            free(sphere_intersections->intersections);
            free(sphere_intersections);
        }
        i++;
    }
}



/*originalestatic void update_obj(int x, int y, t_mlx *mlx, t_object obj)
{
    (void)x;
    (void)y;
    *(mlx->selected_object) = obj; // Copia l'oggetto selezionato
    printf("Selected sphere: %s\n", ((t_sphere *)mlx->selected_object->address)->identifier);
    mlx_destroy_image(mlx->mlx, mlx->img_pointer);
    my_new_image(mlx);
    //cast_rays(mlx);
    my_mlx_pixel_put(mlx, x, y, COLOR_GREEN);
    //mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_pointer, 0, 0);



}*/
static void update_obj(int x, int y, t_mlx *mlx, t_object obj)
{

    (void)x;
    (void)y;
    if (mlx->selected_object)
    {
        free(mlx->selected_object);
    }
    mlx->selected_object = malloc(sizeof(t_object));
    *(mlx->selected_object) = obj; // Copia l'oggetto selezionato

    printf("Selected sphere: %s\n", ((t_sphere *)mlx->selected_object->address)->identifier);

    mlx_destroy_image(mlx->mlx, mlx->img_pointer);
    my_new_image(mlx);
    cast_rays(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_pointer, 0, 0);
}

/*originalevoid selected_obj(int x, int y, t_mlx *mlx)
{
    t_ray ray;
    t_intersection_list *intersections;
    t_intersection *closest_intersection;

    ray = create_ray_from_camera(mlx, x, y); // Crea un raggio dal clic

    // Interseca il raggio con tutte le sfere
    intersections = malloc(sizeof(t_intersection_list));
    intersections->count = 0;
    intersections->intersections = malloc(sizeof(t_intersection) * mlx->setting->num_spheres * 2);

    find_intersections(ray, mlx, intersections);

    closest_intersection = hit(intersections); // Trova l'intersezione più vicina
    if (closest_intersection != NULL)
    {
        // Seleziona l'oggetto intersecato
        if (mlx->selected_object)
        {
            free(mlx->selected_object);
        }

        mlx->selected_object = malloc(sizeof(t_object));
        *(mlx->selected_object) = closest_intersection->obj; // Copia l'oggetto selezionato
        printf("SELECTED OBJ\n");
        update_obj(x, y, mlx, closest_intersection->obj);
    }

    free(intersections->intersections);
    free(intersections);
}*/

/*
void selected_obj(int x, int y, t_mlx *mlx)
{
    t_ray ray;
    t_intersection_list *intersections;
    t_intersection *closest_intersection;

    ray = create_ray_from_camera(mlx, x, y); // Crea un raggio dal clic

    // Interseca il raggio con tutte le sfere
    intersections = malloc(sizeof(t_intersection_list));
    intersections->count = 0;
    intersections->intersections = malloc(sizeof(t_intersection) * mlx->setting->num_spheres * 2);

    find_intersections(ray, mlx, intersections);

    closest_intersection = hit(intersections);// Trova l'intersezione più vicina
    if (closest_intersection != NULL)
        // Seleziona l'oggetto intersecato
        update_obj(x, y, mlx, closest_intersection->obj);
    free (intersections->intersections);
    free (intersections);
}*/

void selected_obj(int x, int y, t_mlx *mlx)
{
    t_ray ray;
    t_intersection_list *intersections;
    t_intersection *closest_intersection;

    ray = create_ray_from_camera(mlx, x, y); // Crea un raggio dal clic

    // Interseca il raggio con tutte le sfere
    intersections = malloc(sizeof(t_intersection_list));
    intersections->count = 0;
    intersections->intersections = malloc(sizeof(t_intersection) * mlx->setting->num_spheres * 2);

    find_intersections(ray, mlx, intersections);

    closest_intersection = hit(intersections); // Trova l'intersezione più vicina
    if (closest_intersection != NULL)
    {
        // Seleziona l'oggetto intersecato
        if (mlx->selected_object)
        {
            free(mlx->selected_object);
        }

        mlx->selected_object = malloc(sizeof(t_object));
        *(mlx->selected_object) = closest_intersection->obj; // Copia l'oggetto selezionato
        printf("SELECTED OBJ\n");
        update_obj(x, y, mlx, closest_intersection->obj);
    }

    free(intersections->intersections);
    free(intersections);
}
