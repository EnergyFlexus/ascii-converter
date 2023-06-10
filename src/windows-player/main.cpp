#include <windows.h>
#include <fstream>
#include <ctime>
#include <chrono>
#include <thread>

int main(int argc, char **argv)
{
	if (argc != 2)
		return -1;

	std::ifstream fin(argv[1]);

	if (!fin.is_open())
		return -1;

	SHORT fps, width, height;
	fin >> fps >> width >> height;
	fin.get();

	// resize window
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT DisplayArea = {0, 0, width, height};
	SetConsoleWindowInfo(h, TRUE, &DisplayArea);

	// clear screen
	DWORD buff;
	CONSOLE_SCREEN_BUFFER_INFO screen;
	GetConsoleScreenBufferInfo(h, &screen);
	FillConsoleOutputCharacterA(h, ' ', screen.dwSize.X * screen.dwSize.Y, {0, 0}, &buff);

	std::chrono::microseconds total_delay{1000000 / fps};
	std::string to_write = "";

	auto start = std::chrono::steady_clock::now();
	while (!fin.eof())
	{
		auto curr = std::chrono::steady_clock::now();
		if (curr - start >= total_delay)
		{
			start = std::chrono::steady_clock::now();
			for (int i = 0; i < height; i++)
			{
				std::getline(fin, to_write, '\n');
				to_write += '\n';
				WriteConsole(h, to_write.c_str(), width + 1, &buff, NULL);
			}
			SetConsoleCursorPosition(h, {0, 0});
		}
	}
	return 0;
}