/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftroise <ftroise@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 15:39:26 by atucci            #+#    #+#             */
/*   Updated: 2024/09/22 11:00:20 by ftroise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <time.h>
//1

/*
origianle
void	my_new_image(t_mlx *data)
{
	//ft_printf("%sgetting address in img_data%s\n", BG_YELLOW, RESET);
	printf("qui ci siamo \n");
    debug_print_data(data);
    printf("STAMPA DATA->MLX %d\n", data->width);
    printf("STAMPA DATA->MLX %d\n", data->height);
    data->img_pointer = mlx_new_image(data->mlx, data->width, data->height);// QUI SMINCHIA
	printf("qui ci siamo2 \n");
	data->img_string = mlx_get_data_addr(data->img_pointer, &(data->bits),
		&(data->lsize), &(data->endian));
	printf("qui ci siamo3 \n");
}*/
void	my_new_image(t_mlx *data)
{
    // Stampa di debug per indicare l'ingresso nella funzione
    printf(RED "\t\t\t siamo in my_new_image\n" RESET);

    // Stampa le dimensioni dell'immagine (larghezza e altezza)
    printf("STAMPA DATA->MLX %d\n", data->width);   // Stampa la larghezza senza colori
    printf("STAMPA DATA->MLX %d\n", data->height);  // Stampa l'altezza senza colori

    // Stampa dati di debug completi per `data` usando una funzione separata
    if(data->k > 0)
        debug_print_data(data);
    data->k++;
    // Creazione dell'immagine con mlx_new_image e controllo dello stato
    printf(YELLOW "Tentativo di creazione immagine con mlx_new_image...\n" RESET);

    data->img_pointer = mlx_new_image(data->mlx, data->width, data->height);  // Porcodioooooooooo
    if (data->img_pointer == NULL) {
        fprintf(stderr, RED "Errore: Creazione immagine fallita in mlx_new_image.\n" RESET);
        exit(1);  // Termina se la creazione fallisce
    }

    // Dopo la creazione dell'immagine
    printf(BLUE "Immagine creata con successo! Indirizzo img_pointer: %p\n" RESET, (void*)data->img_pointer);

    // Ottenere i dati dell'immagine
    data->img_string = mlx_get_data_addr(data->img_pointer, &(data->bits), &(data->lsize), &(data->endian));

    // Conferma dell'ottenimento dei dati dell'immagine
    printf(YELLOW "Dati dell'immagine ottenuti: bits = %d, lsize = %d, endian = %d\n" RESET, data->bits, data->lsize, data->endian);
    printf(BLUE "qui ci siamo3 \n" RESET);
}

//2
void my_mlx_pixel_put(t_mlx *data, int x, int y, int color) {
    char *dst;

    // Controllo per assicurarsi che x e y siano all'interno delle dimensioni della finestra
    if (x >= 0 && x < data->width && y >= 0 && y < data->height) {
        dst = data->img_string + (y * data->lsize + x * (data->bits / 8));
        *(unsigned int *)dst = color;
    }
}

//TODO: to be deleted
void	wallpaper(t_mlx *data)
{
	int			x;
	int			y;
	int		color;
	//int		ray;

	clock_t start_time = clock();
	y = 0;

	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			//color = (x * 255 / data->width) << 16 | (y * 255 / data->height) << 8;
			color = 0xFFFFLL;
			//TODO: here I supposed to cast a ray to see if there is a intersection
			my_mlx_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
	my_mlx_pixel_put(data, data->setting->camera->viewpoint.x, data->setting->camera->viewpoint.y, COLOR_BLACK);

	clock_t end_time = clock();
	double time_taken = ((double)end_time - start_time) / CLOCKS_PER_SEC;
	printf("\n\tThe while loop took %s%.2f seconds%s to execute.\n", YELLOW, time_taken, RESET);
}

//3
/* This function perfom a cleana close and then exit*/
static void	clean_close(t_mlx *project)
{
	ft_printf("%sdestroying the windows\n%s\n", RED, RESET);
	mlx_destroy_window(project->mlx, project->win);
	//TODO: free all the memory
	exit(0);
}

//4
//TODO: interesting function!
static void	test_function(t_mlx *info)
{
	char c[] = "camera : ";
	char *strx = ft_itoa((int)info->setting->camera->viewpoint.x);
	char *stry = ft_itoa((int)info->setting->camera->viewpoint.y);

	char *new_str = ft_strjoin(c, strx);
	new_str = ft_strjoin(new_str, "   ");
	new_str = ft_strjoin(new_str, stry);
	//TODO: The commented line would center the text
	//mlx_string_put(info->mlx, info->win, info->width / 2, info->height / 2, COLOR_WHITE, "camera: ");
	mlx_string_put(info->mlx, info->win, 10, info->height - 10, COLOR_RED, new_str);
	mlx_string_put(info->mlx, info->win, 10, 10, COLOR_RED, "selected obj: ");
}

static int	key_pressed(int keycode, void *param)
{
	t_mlx	*help;

	help = (t_mlx *) param;
	if (keycode == ESC)
		clean_close(help);
//	else if (keycode == PLUS)
//		test_function(help);
//	else if (keycode == MINUS)
//		test_function(help);
	else if (keycode == A)
		test_function(help);
	return (1);
}

int	window_close(void *param)
{
	t_mlx	*help;

	help = (t_mlx *)param;
	clean_close(help);
	return (0);
}



// Nuova funzione
t_vector screen_to_world(int x, int y, t_mlx *mlx)
{
    double aspect_ratio = (double)mlx->width / (double)mlx->height;
    double image_plane_x = ((double)x / (double)mlx->width - 0.5) * aspect_ratio;
    double image_plane_y = (0.5 - (double)y / (double)mlx->height);
    t_vector world_point = create_point(image_plane_x, image_plane_y, 0); // Coordinate nel piano z=0
    return world_point;
}

void print_intersection_data(t_intersection *intersection)
{
    printf(GREEN "Dati intersezione: t = %f, posizione: x = %f, y = %f, z = %f\n" RESET,
           intersection->t, intersection->position.x, intersection->position.y, intersection->position.z);
}



static void find_intersections(t_ray ray, t_mlx *mlx, t_intersection_list *intersections) {
    // Debug print
    printf(RED "\n\n\n\t\t\t\t siamo in find_intersections\n" RESET);

    t_intersection_list *sphere_intersections;
    int i;

    i = 0;
    // Debug print prima di entrare nel ciclo
    printf(GREEN "Numero di sfere da controllare: %d\n" RESET, mlx->setting->num_spheres);

    while (i < mlx->setting->num_spheres) {
        printf(BLUE "Verifica della sfera %d\n" RESET, i);

        // Intersezione con la sfera i-esima
        sphere_intersections = intersect_sphere(*mlx->setting->spheres[i], ray, mlx);
        if (sphere_intersections) {
            // Stampa se viene trovata un'intersezione
            printf(GREEN "Intersezione trovata per la sfera %d\n" RESET, i);

            // Aggiungi le intersezioni alla lista
            add_intersections_to_list(intersections, sphere_intersections);

            // Informazioni di debug
            printf(BLUE "Liberazione della memoria per sphere_intersections, indirizzo: %p\n" RESET, (void*)sphere_intersections);


            // Libera la sfera copiata in profondità
            for (int j = 0; j <= sphere_intersections->count; j++)
            {
                printf(GREEN"\n\n\t\t\t  VOGLIO VEDERE SE QUI ARRIVI\n\n\n\n");
                t_intersection *current_intersection = &(sphere_intersections->intersections[j]);
                printf(BLUE"\t\t\t\t\tTIPO OGGETTO%d\n\n\n\n",current_intersection->obj.type);
                if (current_intersection->obj.type == T_SPHERE)
                {
                    // Libera la sfera copiata in profondità
                    printf(GREEN"\n\n\t\t\t  STO CHIAMANDO FREE_SPHERE\n");
                    //free_sphere((t_sphere *)current_intersection->obj.address);
                }
            }

            // Libera la lista delle intersezioni stessa
            free(sphere_intersections->intersections);
            free(sphere_intersections);
        } else {
            // Stampa se non ci sono intersezioni
            printf(BLUE "Nessuna intersezione trovata per la sfera %d\n" RESET, i);
        }
        i++;
    }
    // Debug finale
    printf(GREEN "Uscita da find_intersections, controllate %d sfere\n" RESET, mlx->setting->num_spheres);
}
/*
void print_sphere_details(t_sphere *sphere) {
    printf("\033[1;32mDettagli della sfera selezionata:\033[0m\n");
    printf("\033[1;32mID: %s\033[0m\n", sphere->identifier);
    printf("\033[1;32mCentro: x = %f, y = %f, z = %f\033[0m\n", sphere->center.x, sphere->center.y, sphere->center.z);
    printf("\033[1;32mDiametro: %f\033[0m\n", sphere->diameter);
    printf("\033[1;32mColore: r = %f, g = %f, b = %f\033[0m\n", sphere->color.r, sphere->color.g, sphere->color.b);
}

static void debug_print_data(t_mlx *data) {
    if (data) {
        printf("\033[1;34mPuntatore data: %p\033[0m\n", (void *)data);
        printf("\033[1;34mContenuto data:\033[0m\n");
        printf("\033[1;34m  mlx: %p\033[0m\n", (void *)data->mlx);
        printf("\033[1;34m  win: %p\033[0m\n", (void *)data->win);
        printf("\033[1;34m  img_pointer: %p\033[0m\n", (void *)data->img_pointer);
        printf("\033[1;34m  img_string: %p\033[0m\n", (void *)data->img_string);
        printf("\033[1;34m  bits: %d\033[0m\n", data->bits);
        printf("\033[1;34m  lsize: %d\033[0m\n", data->lsize);
        printf("\033[1;34m  endian: %d\033[0m\n", data->endian);
        printf("\033[1;34m  width: %d\033[0m\n", data->width);
        printf("\033[1;34m  height: %d\033[0m\n", data->height);
        printf("\033[1;34m  setting: %p\033[0m\n", (void *)data->setting);
        printf("\033[1;34m  selected_object: %p\033[0m\n", (void *)data->selected_object);
        printf("\033[1;34m  is_object_selected: %d\033[0m\n", data->is_object_selected);
    } else {
        printf("\033[1;31mPuntatore data è NULL\033[0m\n");
    }
}



static void update_obj(t_mlx *mlx) {
    if (mlx->is_object_selected == 1) {
        printf("\033[1;32mIndirizzo dell'oggetto selezionato prima del free: %p\033[0m\n", mlx->selected_object);
        free(mlx->selected_object);
        mlx->selected_object = NULL;
    }

    printf("\033[1;33mIndirizzo immagine prima di distruggerla: %p\033[0m\n", mlx->img_pointer);
    mlx_destroy_image(mlx->mlx, mlx->img_pointer);
    printf("\033[1;33mImmagine distrutta\033[0m\n");

    printf("\t\t\t SECONDO PRINT DATA\n\n");
    debug_print_data(mlx);
    my_new_image(mlx);
    printf("\033[1;33mNuova immagine creata, indirizzo: %p\033[0m\n", mlx->img_pointer);

    //draw_scene(mlx);
    printf("\033[1;33mScena ridisegnata senza l'oggetto selezionato\033[0m\n");

    //mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_pointer, 0, 0);
    printf("\033[1;33mFinestra aggiornata\033[0m\n");
}


void selected_obj(int x, int y, t_mlx *mlx) {
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
    if (closest_intersection != NULL) {
        // Seleziona l'oggetto intersecato
        mlx->selected_object = malloc(sizeof(t_object));
        *(mlx->selected_object) = closest_intersection->obj; // Copia l'oggetto selezionato
        mlx->is_object_selected = 1; // Imposta lo stato di selezione
        printf("\033[1;32mOGGETTO SELEZIONATO: %s, indirizzo: %p\033[0m\n", ((t_sphere *)mlx->selected_object->address)->identifier, mlx->selected_object);
        print_sphere_details((t_sphere *)mlx->selected_object->address);
    }

    printf("\033[1;31mIndirizzo intersezioni prima del free: %p\033[0m\n", intersections->intersections);
    free(intersections->intersections);  // Libera la memoria per le intersezioni
    printf("\033[1;31mIntersezioni liberate\033[0m\n");
    printf("\033[1;31mIndirizzo lista intersezioni prima del free: %p\033[0m\n", intersections);
    free(intersections);  // Libera la memoria per la lista di intersezioni
    printf("\033[1;31mLista intersezioni liberata\033[0m\n");
}

static void print_object_details(t_object *obj) {
    if (obj == NULL) {
        printf("\033[1;31mOggetto è NULL\033[0m\n");
        return;
    }

    printf("\033[1;34mDettagli dell'oggetto:\033[0m\n");
    printf("\033[1;34mTipo: %d\033[0m\n", obj->type);
    printf("\033[1;34mIndirizzo: %p\033[0m\n", obj->address);

    if (obj->type == T_SPHERE) {
        print_sphere_details((t_sphere *)obj->address);
    }
    // Aggiungi ulteriori controlli se hai altri tipi di oggetti
}

int mouse_click(int button, int x, int y, t_mlx *mlx)
{
    if (button == LEFT) {
        t_vector click_point = screen_to_world(x, y, mlx);  // Conversione delle coordinate del clic
        printf("\033[1;33mCOORDINATE DEL CLIC: x: %f, y: %f\033[0m\n", click_point.x, click_point.y);
        printf("\t\t\tprimo print data\n\n");
        debug_print_data(mlx);
        if (mlx->is_object_selected == 1)
        {
            printf("\tproviamo a stampare la struttura object \n");
            // Riposiziona l'oggetto selezionato
            print_object_details(mlx->selected_object);
            t_sphere *sphere = (t_sphere *)mlx->selected_object->address;
            printf("vediamo se qui arriva");
            sphere->center = click_point;
            printf("\033[1;32mSFERA SPOSTATA: nuovo centro sfera coordinate x: %f, y: %f\033[0m\n", click_point.x, click_point.y);
            mlx->is_object_selected = 0;  // Deseleziona l'oggetto

            // Ridisegna la scena e aggiorna la finestra
            my_new_image(mlx);
            draw_scene(mlx);
            mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_pointer, 0, 0);
            printf("\033[1;31mFinestra aggiornata con la sfera riposizionata\033[0m\n");
        } else {
            // Seleziona un nuovo oggetto e rimuove l'oggetto selezionato
            selected_obj(x, y, mlx);
            if (mlx->is_object_selected) {
                update_obj(mlx);
            }
        }
    }
    printf("\033[1;33mMouse click: button %d, x = %d, y = %d\033[0m\n", button, x, y);
    return 0;
}

void manage_mlx(t_mlx *obj, t_setting *set)
{
    obj->mlx = mlx_init();
    ft_printf("%smlx_init has started%s\n", YELLOW, RESET);
    if (obj->mlx == NULL)
        return (ft_putstr_fd("mlx_init fail...\n", 2));
    obj->win = mlx_new_window(obj->mlx, obj->width, obj->height, obj->map_name);
    my_new_image(obj);
    draw_scene(obj);
    mlx_put_image_to_window(obj->mlx, obj->win, obj->img_pointer, 0, 0);
    mlx_mouse_hook(obj->win, mouse_click, obj);  // Hook per il clic del mouse
    mlx_hook(obj->win, 2, 1L << 0, key_pressed, obj);  // Hook per la pressione dei tasti
    mlx_hook(obj->win, 17, 0L, window_close, obj);  // Hook per la chiusura della finestra
    mlx_loop(obj->mlx);
    mlx_destroy_display(obj->mlx);
    mlx_destroy_window(obj->mlx, obj->win);
    //TODO: fix the leaks free();
    (void)set;  // Sopprime l'avviso di parametro non utilizzato
}*/

/*  QUESTO DOVREBBE RENDERE IL PUNTATORE OBJ NON NULLO*/
void print_sphere_details(t_sphere *sphere) {
    printf("\033[1;32mDettagli della sfera selezionata:\033[0m\n");
    printf("\033[1;32mID: %s\033[0m\n", sphere->identifier);
    printf("\033[1;32mCentro: x = %f, y = %f, z = %f\033[0m\n", sphere->center.x, sphere->center.y, sphere->center.z);
    printf("\033[1;32mDiametro: %f\033[0m\n", sphere->diameter);
    printf("\033[1;32mColore: r = %f, g = %f, b = %f\033[0m\n", sphere->color.r, sphere->color.g, sphere->color.b);
}
void debug_print_data(t_mlx *data) {
    if (data) {
        printf("\033[1;34mPuntatore data: %p\033[0m\n", (void *)data);
        printf("\033[1;34mContenuto data:\033[0m\n");

        if (data->mlx != NULL && data->mlx != 0) {
            printf("\033[1;34m  mlx: %p\033[0m\n", (void *)data->mlx);
        } else {
            printf("\033[1;31m  mlx non inizializzato!\033[0m\n");
        }

        if (data->win != NULL && data->win != 0) {
            printf("\033[1;34m  win: %p\033[0m\n", (void *)data->win);
        } else {
            printf("\033[1;31m  win non inizializzato!\033[0m\n");
        }

        if (data->img_pointer != NULL && data->img_pointer != 0)
        {
            printf("\033[1;34m  img_pointer: %p\033[0m\n", (void *)data->img_pointer);
        } else {
            printf("\033[1;31m  img_pointer non inizializzato!\033[0m\n");
        }

        if (data->img_string != NULL && data->img_string != 0) {
            printf("\033[1;34m  img_string: %p\033[0m\n", (void *)data->img_string);
        } else {
            printf("\033[1;31m  img_string non inizializzato!\033[0m\n");
        }

        if (data->bits >= 0) {
            printf("\033[1;34m  bits: %d\033[0m\n", data->bits);
        } else {
            printf("\033[1;31m  bits non inizializzato correttamente!\033[0m\n");
        }

        if (data->lsize >= 0) {
            printf("\033[1;34m  lsize: %d\033[0m\n", data->lsize);
        } else {
            printf("\033[1;31m  lsize non inizializzato correttamente!\033[0m\n");
        }

        if (data->endian >= 0) {
            printf("\033[1;34m  endian: %d\033[0m\n", data->endian);
        } else {
            printf("\033[1;31m  endian non inizializzato correttamente!\033[0m\n");
        }

        if (data->width > 0) {
            printf("\033[1;34m  width: %d\033[0m\n", data->width);
        } else {
            printf("\033[1;31m  width non inizializzato correttamente!\033[0m\n");
        }

        if (data->height > 0) {
            printf("\033[1;34m  height: %d\033[0m\n", data->height);
        } else {
            printf("\033[1;31m  height non inizializzato correttamente!\033[0m\n");
        }

        if (data->setting != NULL) {
            printf("\033[1;34m  setting: %p\033[0m\n", (void *)data->setting);
        } else {
            printf("\033[1;31m  setting non inizializzato!\033[0m\n");
        }

        if (data->selected_object != NULL && data->selected_object != 0) {
            printf("\033[1;34m  selected_object: %p\033[0m\n", (void *)data->selected_object);
        } else {
            printf("\033[1;31m  selected_object non inizializzato!\033[0m\n");
        }

        if (data->is_object_selected >= 0) {
            printf("\033[1;34m  is_object_selected: %d\033[0m\n", data->is_object_selected);
        } else {
            printf("\033[1;31m  is_object_selected non inizializzato correttamente!\033[0m\n");
        }

    } else {
        printf("\033[1;31mPuntatore data è NULL\033[0m\n");
    }
}
/*
static void update_obj(int x, int y, t_mlx *mlx, t_object obj)
{
    printf("\033[1;33mEntrato in update_obj con parametri x: %d, y: %d\033[0m\n", x, y);

    (void)x;
    (void)y;

    if (mlx->selected_object)
    {
        printf("\033[1;33mIndirizzo dell'oggetto selezionato prima del free: %p\033[0m\n", mlx->selected_object);
        free(mlx->selected_object);
        printf("\033[1;32mOggetto selezionato precedente liberato\033[0m\n");
    }

    mlx->selected_object = malloc(sizeof(t_object));
    if (!mlx->selected_object) {
        fprintf(stderr, "\033[1;31mErrore di allocazione memoria per l'oggetto selezionato\033[0m\n");
        exit(1);
    }
    printf("qui ci siamo dioporco\n");
    *(mlx->selected_object) = obj; // Copia l'oggetto selezionato

    printf("\033[1;32mNuovo oggetto selezionato, indirizzo: %p\033[0m\n", mlx->selected_object);
    printf("\033[1;34mSelected sphere: %s\033[0m\n", ((t_sphere *)mlx->selected_object->address)->identifier);

    printf("\033[1;33mIndirizzo immagine prima di distruggerla: %p\033[0m\n", mlx->img_pointer);
    mlx_destroy_image(mlx->mlx, mlx->img_pointer);
    printf("\033[1;32mImmagine distrutta\033[0m\n");

    my_new_image(mlx);
    printf("\033[1;32mNuova immagine creata, indirizzo: %p\033[0m\n", mlx->img_pointer);

    cast_rays(mlx);
    printf("\033[1;32mRay casting completato\033[0m\n");

    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_pointer, 0, 0);
    printf("\033[1;32mFinestra aggiornata con la nuova immagine\033[0m\n");
}*/

static void print_object_details(t_object *obj) {
    if (obj == NULL) {
        printf("\033[1;31mOggetto è NULL\033[0m\n");
        return;
    }

    printf("\033[1;34mDettagli dell'oggetto:\033[0m\n");
    printf("\033[1;34mTipo: %d\033[0m\n", obj->type);
    printf("\033[1;34mIndirizzo: %p\033[0m\n", obj->address);

    if (obj->type == T_SPHERE) {
        print_sphere_details((t_sphere *)obj->address);
    }
    // Aggiungi ulteriori controlli se hai altri tipi di oggetti
}


void update_obj(t_mlx *mlx) {
    printf(RED "\n\n\n\t\t\t\t siamo in update_obj\n" RESET);

    // Stampa l'indirizzo di img_pointer prima di qualsiasi operazione
    printf(BLUE "Indirizzo img_pointer prima dell'aggiornamento: %p\n" RESET, (void*)mlx->img_pointer);

    if (mlx->is_object_selected) {
        printf(GREEN "Oggetto selezionato, aggiornamento in corso...\n" RESET);

        // Dettagli sull'oggetto selezionato
        printf(WHITE "Oggetto selezionato, indirizzo: %p\n" RESET, (void*)mlx->selected_object);
        print_object_details(mlx->selected_object);

        // Esegui eventuali modifiche sull'oggetto selezionato (ad esempio la posizione)
        t_sphere *sphere = (t_sphere *)mlx->selected_object->address;  // Esempio per una sfera
        sphere->center.x += 1.0;  // Modifica la posizione della sfera (esempio)
        printf(WHITE "Nuova posizione della sfera: x = %f, y = %f, z = %f\n" RESET, sphere->center.x, sphere->center.y, sphere->center.z);

        // Dettagli aggiornati
        print_object_details(mlx->selected_object);

        // Crea una nuova immagine con l'oggetto aggiornato
        if (mlx->img_pointer != NULL) {
            printf(BLUE "Prima della distruzione, img_pointer indirizzo: %p\n" RESET, (void*)mlx->img_pointer);
            mlx_destroy_image(mlx->mlx, mlx->img_pointer);  // Distruggi l'immagine attuale
            mlx->img_pointer = 0;  // Imposta img_pointer a NULL
            printf(BLUE "Immagine distrutta. img_pointer ora è NULL.\n" RESET);
        }

        // Stampa dei parametri prima di creare la nuova immagine
        printf(WHITE "\n\nParametri passati a my_new_image:\n" RESET);
        printf(WHITE "mlx->width = %d\n" RESET, mlx->width);
        printf(WHITE "mlx->height = %d\n" RESET, mlx->height);
        printf(WHITE "mlx->mlx = %p\n" RESET, (void*)mlx->mlx);
        printf(WHITE "mlx->img_pointer = %p\n" RESET, (void*)mlx->img_pointer);

        // Crea una nuova immagine
        printf(WHITE "\nCreazione di una nuova immagine dopo l'aggiornamento dell'oggetto...\n" RESET);
        my_new_image(mlx);

        // Ridisegna la scena con i nuovi dati
        draw_scene(mlx);
        mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_pointer, 0, 0);
        printf(GREEN "Scena ridisegnata con il nuovo oggetto aggiornato.\n" RESET);

    } else {
        printf(RED "Nessun oggetto selezionato, nessuna necessità di aggiornare l'immagine.\n" RESET);
    }

    // Stampa l'indirizzo di img_pointer dopo l'aggiornamento
    printf(BLUE "Indirizzo img_pointer dopo l'aggiornamento: %p\n" RESET, (void*)mlx->img_pointer);

    printf(GREEN "Uscita da update_obj\n" RESET);
}


void selected_obj(int x, int y, t_mlx *mlx) {
    printf(RED "\n\n\n\t\t\t\t siamo in selected_obj\n" RESET);

    t_ray ray;
    t_intersection_list *intersections;
    t_intersection *closest_intersection;

    ray = create_ray_from_camera(mlx, x, y);  // Crea un raggio dal clic
    printf(GREEN "Ray creato\n" RESET);

    // Alloca memoria per le intersezioni
    intersections = malloc(sizeof(t_intersection_list));
    if (intersections == NULL) {
        fprintf(stderr, RED "Errore: Impossibile allocare memoria per la lista di intersezioni\n" RESET);
        return;
    }

    intersections->count = 0;
    intersections->intersections = malloc(sizeof(t_intersection) * mlx->setting->num_spheres * 2);
    if (intersections->intersections == NULL) {
        fprintf(stderr, RED "Errore: Impossibile allocare memoria per le intersezioni\n" RESET);
        free(intersections);
        return;
    }
    printf(GREEN "Allocazione memoria per le intersezioni completata\n" RESET);

    // Trova le intersezioni
    find_intersections(ray, mlx, intersections);
    printf(GREEN "Intersezioni trovate\n" RESET);


    closest_intersection = hit(intersections);  // Trova l'intersezione più vicina
    if (closest_intersection != NULL) {
        printf(GREEN "Oggetto intersecato trovato\n" RESET);

        // Controllo e debug della memoria precedente dell'oggetto selezionato
        if (mlx->selected_object != NULL) {
            printf(BLUE "\nLiberazione dell'oggetto selezionato precedente, indirizzo: %p\n" RESET, (void*)mlx->selected_object);
            print_object_details(mlx->selected_object);  // Stampa i dettagli dell'oggetto selezionato prima di liberarlo
            //free(mlx->selected_object);  // Libera l'oggetto precedente
            //printf(WHITE "Oggetto selezionato precedente liberato.\n" RESET);
        }

        // Copia sicura dell'oggetto selezionato
        printf(WHITE "\nCreazione della copia sicura dell'oggetto selezionato.\n" RESET);
        mlx->selected_object = malloc(sizeof(t_object));
        if (mlx->selected_object == NULL) {
            fprintf(stderr, RED "Errore: Allocazione fallita per selected_object\n" RESET);
            free(intersections->intersections);
            free(intersections);
            return;
        }

        *(mlx->selected_object) = closest_intersection->obj;  // Copia l'oggetto
        printf(WHITE "\nOggetto selezionato copiato in nuova memoria, indirizzo: %p\n" RESET, (void*)mlx->selected_object);
        print_object_details(mlx->selected_object);  // Stampa i dettagli dell'oggetto copiato

        // Aggiorna lo stato di selezione
        mlx->is_object_selected = 1;
        printf(GREEN "Oggetto selezionato correttamente e lo stato è stato aggiornato.\n" RESET);
    } else {
        printf(BLUE "Nessuna intersezione trovata\n" RESET);
    }

    // Liberazione della memoria per le intersezioni
    printf(BLUE "Liberazione della memoria delle intersezioni, indirizzo: %p\n" RESET, (void*)intersections->intersections);
    free(intersections->intersections);
    printf(WHITE "Memoria delle intersezioni liberata.\n" RESET);

    printf(BLUE "Liberazione della lista delle intersezioni, indirizzo: %p\n" RESET, (void*)intersections);
    free(intersections);
    printf(WHITE "Lista delle intersezioni liberata.\n" RESET);
}



int mouse_click(int button, int x, int y, t_mlx *mlx) {
    if (button == LEFT) {
        t_vector click_point = screen_to_world(x, y, mlx);  // Conversione delle coordinate del clic
        printf("\033[1;33mCOORDINATE DEL CLIC: x: %f, y: %f\033[0m\n", click_point.x, click_point.y);
        printf("\t\t\tprimo print data\n\n");
        debug_print_data(mlx);

        if (mlx->is_object_selected == 1) {
            printf("\tproviamo a stampare la struttura object \n");
            // Riposiziona l'oggetto selezionato
            print_object_details(mlx->selected_object);

            if (mlx->selected_object && mlx->selected_object->address) {
                t_sphere *sphere = (t_sphere *)mlx->selected_object->address;
                printf("vediamo se qui arriva\n");
                sphere->center = click_point;
                printf("\033[1;32mSFERA SPOSTATA: nuovo centro sfera coordinate x: %f, y: %f\033[0m\n", click_point.x, click_point.y);

                mlx->is_object_selected = 0;  // Deseleziona l'oggetto

                // Ridisegna la scena e aggiorna la finestra
                my_new_image(mlx);
                draw_scene(mlx);
                mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_pointer, 0, 0);
                printf("\033[1;31mFinestra aggiornata con la sfera riposizionata\033[0m\n");
            } else {
                printf("\033[1;31mErrore: selected_object o selected_object->address è NULL\033[0m\n");
            }
        } else {
            // Seleziona un nuovo oggetto e rimuove l'oggetto selezionato
            selected_obj(x, y, mlx);
            if (mlx->is_object_selected) {
                update_obj(mlx);
            }
        }
    }

    printf("\033[1;33mMouse click: button %d, x = %d, y = %d\033[0m\n", button, x, y);
    return 0;
}

void manage_mlx(t_mlx *obj, t_setting *set)
{
    printf("\n\n\t\t\t\t  ENTRATO IN MANAGE_MLX\n\n\n");

    obj->mlx = mlx_init();
    if (obj->mlx == NULL)
    {
        printf("Error: mlx_init failed\n");
        exit (-1);
    }
    ft_printf("%smlx_init has started%s\n", YELLOW, RESET);

    // Controlla se mlx_init ha avuto successo
    if (obj->mlx == NULL) {
        ft_putstr_fd("mlx_init fail...\n", 2);
        return;
    }

    // Inizializza width e height se non lo hai già fatto altrove
    if (obj->width <= 0 || obj->height <= 0) {
        obj->width = 800;   // Valori di default per la finestra
        obj->height = 600;
        printf("Dimensioni della finestra impostate di default (width: %d, height: %d)\n", obj->width, obj->height);
    }

    // Controlla che il nome della mappa (obj->map_name) sia valido prima di passarlo a mlx_new_window
    if (obj->map_name == NULL) {
        ft_putstr_fd("Errore: nome della mappa non definito\n", 2);
        return;
    }

    // Creazione della finestra
    obj->win = mlx_new_window(obj->mlx, obj->width, obj->height, obj->map_name);
    if (obj->win == NULL) {
        ft_putstr_fd("Creazione della finestra fallita\n", 2);
        return;
    }

    // Creazione dell'immagine
    my_new_image(obj);

    // Disegno della scena
    draw_scene(obj);

    // Mostra l'immagine nella finestra
    mlx_put_image_to_window(obj->mlx, obj->win, obj->img_pointer, 0, 0);

    // Gestione eventi
    mlx_mouse_hook(obj->win, mouse_click, obj);  // Hook per il clic del mouse
    mlx_hook(obj->win, 2, 1L << 0, key_pressed, obj);  // Hook per la pressione dei tasti
    mlx_hook(obj->win, 17, 0L, window_close, obj);  // Hook per la chiusura della finestra

    // Loop principale di MLX
    mlx_loop(obj->mlx);

    // Pulizia e chiusura
    mlx_destroy_display(obj->mlx);
    mlx_destroy_window(obj->mlx, obj->win);

    // TODO: fix the leaks
    (void)set;  // Sopprime l'avviso di parametro non utilizzato
}



/*
static void remove_selected_obj(t_mlx *mlx) {
    if (mlx->selected_object) {
        printf("\033[1;32mRimuovo l'oggetto selezionato: %p\033[0m\n", mlx->selected_object);
        t_sphere *sphere = (t_sphere *)mlx->selected_object->address;
        // Rimuove la sfera dalla lista delle sfere
        int i = 0;
        while (i < mlx->setting->num_spheres) {
            if (mlx->setting->spheres[i] == sphere) {
                mlx->setting->spheres[i] = NULL;
                break;
            }
            i++;
        }
        // Non liberiamo selected_object qui
    }

    printf("\033[1;33mIndirizzo immagine prima di distruggerla: %p\033[0m\n", mlx->img_pointer);
    mlx_destroy_image(mlx->mlx, mlx->img_pointer);
    printf("\033[1;33mImmagine distrutta\033[0m\n");

    my_new_image(mlx);
    printf("\033[1;33mNuova immagine creata, indirizzo: %p\033[0m\n", mlx->img_pointer);

    draw_scene(mlx);
    printf("\033[1;33mScena ridisegnata senza l'oggetto selezionato\033[0m\n");

    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_pointer, 0, 0);
    printf("\033[1;33mFinestra aggiornata\033[0m\n");
}

--------
static void remove_selected_obj(t_mlx *mlx) {
    if (mlx->selected_object) {
        printf("\033[1;32mRimuovo l'oggetto selezionato: %p\033[0m\n", mlx->selected_object);
        t_sphere *sphere = (t_sphere *)mlx->selected_object->address;
        // Rimuove la sfera dalla lista delle sfere
        int i = 0;
        while (i < mlx->setting->num_spheres) {
            if (mlx->setting->spheres[i] == sphere) {
                mlx->setting->spheres[i] = NULL;
                break;
            }
            i++;
        }
        free(mlx->selected_object);  // Libera l'oggetto selezionato
        mlx->selected_object = NULL;
    }

    printf("\033[1;33mIndirizzo immagine prima di distruggerla: %p\033[0m\n", mlx->img_pointer);
    mlx_destroy_image(mlx->mlx, mlx->img_pointer);
    printf("\033[1;33mImmagine distrutta\033[0m\n");

    my_new_image(mlx);
    printf("\033[1;33mNuova immagine creata, indirizzo: %p\033[0m\n", mlx->img_pointer);

    draw_scene(mlx);
    printf("\033[1;33mScena ridisegnata senza l'oggetto selezionato\033[0m\n");

    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img_pointer, 0, 0);
    printf("\033[1;33mFinestra aggiornata\033[0m\n");
}*/
