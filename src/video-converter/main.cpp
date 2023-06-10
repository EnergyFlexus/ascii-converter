#include <fstream>
#include <cmath>

#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

char grayToSym(uchar gray)
{
	const char gradient[] = " .:-=+*#%@";
	double ratio = ((double)gray / 256);
	return gradient[(int)(ratio * 10)];
}

int main(int argc, char **argv)
{
	if (argc < 2)
		return -1;

#ifndef _DEBUG
	cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
#endif // _DEBUG

	cv::VideoCapture cap(argv[1]);
	std::ofstream fout(std::strcat(argv[1], ".txt"));

	int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	double fps = std::round(cap.get(cv::CAP_PROP_FPS));
	const double console_rescale = 0.8;

	int rescaled_width;
	if (argc > 2)
		rescaled_width = std::stoi(argv[2]);
	else
		rescaled_width = 80;

	int rescaled_heigt;
	if (argc > 3)
		rescaled_heigt = std::stoi(argv[3]);
	else
		rescaled_heigt = (double)height * ((double)rescaled_width / (double)width) * console_rescale;

	cv::Size rescaled_size(rescaled_width, rescaled_heigt);
	fout << fps << ' ' << rescaled_width << ' ' << rescaled_heigt << '\n';

	cv::Mat image;
	while (cap.read(image))
	{
		// resize
		cv::Mat image_resized;
		resize(image, image_resized, rescaled_size, 0, 0, cv::INTER_CUBIC);

		for (int i = 0; i < image_resized.rows; i++)
		{
			for (int j = 0; j < image_resized.cols; j++)
			{
				cv::Vec3b data = image_resized.at<cv::Vec3b>(i, j);
				uchar blue = data[0] * 0.3;
				uchar green = data[1] * 0.59;
				uchar red = data[2] * 0.11;
				uchar gray = (red + green + blue);
				fout << grayToSym(gray);
			}
			fout << '\n';
		}
	}
	return 0;
}
