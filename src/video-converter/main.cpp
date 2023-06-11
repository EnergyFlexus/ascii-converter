#include "VideoConverter.h"

int main(int argc, char **argv)
{
	if (argc < 2)
		return -1;

	std::string filename(argv[1]);
	std::ofstream fout(std::strcat(argv[1], ".txt"));

	int width;
	if (argc > 2)
		width = std::stoi(argv[2]);
	else
		width = 80;

	int heigt;
	if (argc > 3)
		heigt = std::stoi(argv[3]);
	else
		heigt = 0;

	ascii::VideoConverter converter;

	// %
	converter.SetLog(true);

	// if height 0 - auto rescaling
	converter.Convert(filename, fout, width, heigt);
	return 0;
}
