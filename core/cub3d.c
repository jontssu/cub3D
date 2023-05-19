#include "cub3d.h"

int main(int argc, char **argv) 
{
	if (argc != 2)
		return (error_argument_count());
	parser(argv[1]);
	return (0);
}