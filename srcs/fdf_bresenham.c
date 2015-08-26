
#include "fdf.h"

static void	fdf_bresenham_vertical_octant(t_img *img, t_bresenham *b, \
				t_vertex *v0, t_vertex *v1)
{
	int		x;
	int		y;
	t_color	color;
	t_color	color_inc;

	x = v0->x;
	y = v0->y;
	color = v0->color;
	color_inc = color_sub(&v0->color, &v1->color);
	color_inc = color_mult(&color_inc, 1 / ft_abs(v0->y - v1->y));
	while (y != v1->y)
	{
		ui_put_pixel_to_img(img, x, y, color.hex);
		color = color_add(&color, &color_inc);
		if ((b->err += b->err_inc) >= 0)
		{
			x += b->X_inc;
			b->err += b->err_dec;
		}
		y += b->Y_inc;
	}
	ui_put_pixel_to_img(img, x, y, color.hex);
}

static void	fdf_bresenham_horizontal_octant(t_img *img, t_bresenham *b, \
				t_vertex *v0, t_vertex *v1)
{
	int		x;
	int		y;
	t_color	color;
	t_color	color_inc;

	x = v0->x;
	y = v0->y;
	color = v0->color;
	color_inc = color_sub(&v0->color, &v1->color);
	color_inc = color_mult(&color_inc, 1 / ft_abs(v0->x - v1->x));
	while (x != v1->x)
	{
		ui_put_pixel_to_img(img, x, y, color.hex);
		color = color_add(&color, &color_inc);
		if ((b->err += b->err_inc) >= 0)
		{
			y += b->Y_inc;
			b->err += b->err_dec;
		}
		x += b->X_inc;
	}
	ui_put_pixel_to_img(img, x, y, color.hex);
}

void		fdf_bresenham(t_img *img, t_vertex *v0, t_vertex *v1)
{
	t_bresenham	b;

	b.dX = v1->x - v0->x;
	b.dY = v1->y - v0->y;
	b.X_inc = (b.dX > 0) ? 1 : -1;
	b.Y_inc = (b.dY > 0) ? 1 : -1;
	if (ft_abs(b.dX) >= ft_abs(b.dY))
	{
		b.err = -ft_abs(b.dX);
		b.err_inc = ft_abs(b.dY) + ft_abs(b.dY);
		b.err_dec = -(ft_abs(b.dX) + ft_abs(b.dX));
		fdf_bresenham_horizontal_octant(img, &b, v0, v1);
	}
	else
	{
		b.err = -ft_abs(b.dY);
		b.err_inc = ft_abs(b.dX) + ft_abs(b.dX);
		b.err_dec = -(ft_abs(b.dY) + ft_abs(b.dY));
		fdf_bresenham_vertical_octant(img, &b, v0, v1);
	}
}
