#include "parsing.h"

int main(int argc, char **argv) 
{
	t_parser	elements;
	if (argc != 2)
		return (error_argument_count());
	parser(argv[1], &elements);
	return (0);
}