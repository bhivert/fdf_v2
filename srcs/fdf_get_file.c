
#include "fdf.h"

int		fdf_get_file(t_env *e)
{
	int			fd;
	char		*line;
	int			value;
	t_container	*tmp;
	int			out;

	if ((fd = open(e->av[1], O_RDONLY)) == -1)
		return (ft_printf("%s unable to open %s.\n", e->av[0], e->av[1]), -1);
	if (!(e->file = ft_new_container(VECTOR, sizeof(t_container *))))
		return (-1);
	while (ft_gnl(fd, &line) > 0)
	{
		tmp = ft_new_container(VECTOR, sizeof(int));
		ft_push_back(e->file, &tmp);
		while ((out = ft_sscanf(line, "%d %s", &value, line)))
		{
			ft_push_back(*(t_container **)ft_at_index(e->file, \
						ft_size(e->file) - 1), &value);
			if (out == 1)
				break ;
		}
		free(line);
	}
	close(fd);
	return (0);
}