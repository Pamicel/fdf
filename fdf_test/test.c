#include <mlx.h>
#include <math.h>
#include <stdio.h>

typedef struct	s_data
{
	double		pol[2];
	int			canvas[2];
	void		*mlx;
	void		*win;
}				t_data;

int		loop_hook(t_data *data)
{
	int x;
	int y;

//	x = -1;
//	while (++x < data->canvas[0])
//	{
//		y = -1;
//		while (++y < data->canvas[1])
//			mlx_pixel_put(data->mlx, data->win, x, y, 0);
//	}
	mlx_clear_window(data->mlx, data->win);
	mlx_pixel_put(data->mlx, \
					data->win, \
					data->pol[1] * cos(data->pol[0]) + data->canvas[0] / 2, \
					data->pol[1] * sin(data->pol[0]) + data->canvas[1] / 2, \
					0x0);
	data->pol[0] = fmod((data->pol[0] + 0.01), (M_PI*2));
	mlx_pixel_put(data->mlx, \
					data->win, \
					data->pol[1] * cos(data->pol[0]) + data->canvas[0] / 2, \
					data->pol[1] * sin(data->pol[0]) + data->canvas[1] / 2, \
					0xFFFFFF);
	printf("%f\n", data->pol[0]);
	return (0);
}

int		main(void)
{
	t_data		*data;
	t_data		data_struct;

	data = &data_struct;
	data->canvas[0] = 600;
	data->canvas[1] = 400;
	data->pol[0] = 0;
	data->pol[1] = 50;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->canvas[0], data->canvas[1], "hello world");
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
