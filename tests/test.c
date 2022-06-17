#include "../include/get_next_line.h"
#include <fcntl.h>

int	main()
{
	int	fd;
	char	*line;

	fd = open("tests/base", O_RDONLY);
	while ()
	{
		line = get_next_line(fd);
		printf("%s", line);
		if (line == NULL)
			break;
		free(line);
	}
	return (0);
}
