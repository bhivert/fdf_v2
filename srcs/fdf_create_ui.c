/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_ui.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/20 13:43:32 by bhivert           #+#    #+#             */
/*   Updated: 2016/06/15 19:37:58 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_exit(t_env *e)
{
	ft_set_content_destroy(e->file, (void(*)(void *))&ft_delete_container);
	ft_delete_container(&e->file);
	exit(EXIT_SUCCESS);
}

void		fdf_update_model(t_env *e, double **rot_x, double **rot_z)
{
	double	**tmp;

	if (rot_x)
	{
		e->up = vector_mult_matrix(&e->up, rot_x);
		tmp = matrix_mult(e->model, rot_x);
		free_matrix(e->model);
		e->model = tmp;
		free_matrix(rot_x);
	}
	if (rot_z)
	{
		e->rt = vector_mult_matrix(&e->rt, rot_z);
		tmp = matrix_mult(e->model, rot_z);
		free_matrix(e->model);
		e->model = tmp;
		free_matrix(rot_z);
	}
}

void		fdf_key_hook(void *param, int code, int type)
{
	t_env	*e;
	double	**tmp_rot_x;
	double	**tmp_rot_z;

	e = (t_env *)param;
	tmp_rot_x = NULL;
	tmp_rot_z = NULL;
	if (type == 2)
		return ;
	if (code == UI_KEY_ESC)
		fdf_exit(e);
	else if (code == UI_KEY_RIGHT || code == UI_KEY_PAD_6)
		tmp_rot_z = matrix_axis_rot(e->up.x, e->up.y, e->up.z, rad(10));
	else if (code == UI_KEY_LEFT || code == UI_KEY_PAD_4)
		tmp_rot_z = matrix_axis_rot(e->up.x, e->up.y, e->up.z, rad(-10));
	else if (code == UI_KEY_UP || code == UI_KEY_PAD_8)
		tmp_rot_x = matrix_axis_rot(e->rt.x, e->rt.y, e->rt.z, rad(-10));
	else if (code == UI_KEY_DOWN || code == UI_KEY_PAD_5)
		tmp_rot_x = matrix_axis_rot(e->rt.x, e->rt.y, e->rt.z, rad(10));
	else if (code == UI_KEY_PUP || code == UI_KEY_PAD_P)
		++e->scaling;
	else if (code == UI_KEY_PDW || code == UI_KEY_PAD_M)
		e->scaling -= (e->scaling > 1) ? 1 : 0;
	fdf_update_model(e, tmp_rot_x, tmp_rot_z);
}

int			fdf_create_ui(t_env *e)
{
	if (!(e->win = ui_new_window(e->av[0], 1200, 1200)))
	{
		ft_printf("%s unable to create windows.\n", e->av[0]);
		return (-1);
	}
	ui_window_set_color(e->win, 0x000000);
	e->img_id = ui_new_image(e->win, e->win->size.width, e->win->size.height);
	if (e->img_id == -1)
	{
		ft_printf("%s unable to create image.\n", e->av[0]);
		return (-1);
	}
	ui_widget_set_color(e->win, e->img_id, 0x000000);
	ui_window_set_key_hook(e->win, &fdf_key_hook, e);
	ui_widget_set_hook_param(e->win, e->img_id, e->img_id, e);
	ui_widget_set_refresh_hook(e->win, e->img_id, &fdf_draw);
	return (0);
}
