#include "cub3D.h"

int main(int argc, char **argv) 
{
	if (argc != 2)
		return (return_error());
	parser(argv[1]);
	return (0);
}