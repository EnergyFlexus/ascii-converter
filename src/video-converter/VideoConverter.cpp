#include <iostream>

#include "VideoConverter.h"

namespace ascii
{
	char VideoConverter::GrayToAscii(uchar gray)
	{
		double ratio = ((double)gray / 256);
		return m_gradient[(int)(ratio * m_gradient.size())];
	}
	void VideoConverter::SetGradient(const std::string &gradient)
	{
		m_gradient = gradient;
	}
	void VideoConverter::SetConsoleCoefficient(double consoleCoefficient)
	{
		m_consoleCoefficient = consoleCoefficient;
	}
	void VideoConverter::SetLog(bool log)
	{
		m_log = log;
	}
	
	void VideoConverter::Convert(const std::string &filename, std::ostream &output, short asciiWidth, short asciiHeight)
	{
#ifndef _DEBUG
		cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
#endif // _DEBUG

		cv::VideoCapture cap(filename);

		int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
		int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
		int frame_count = cap.get(cv::CAP_PROP_FRAME_COUNT);
		double fps = std::round(cap.get(cv::CAP_PROP_FPS));
		const double console_rescale = 0.8;

		if (asciiHeight == 0)
			asciiHeight = (double)height * ((double)asciiWidth / (double)width) * console_rescale;

		cv::Size rescaled_size(asciiWidth, asciiHeight);
		output << fps << ' ' << asciiWidth << ' ' << asciiHeight << '\n';

		cv::Mat image;
		size_t count = 0;
		short last_percent = 0;
		while (cap.read(image))
		{
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
					output << GrayToAscii(gray);
				}
				output << '\n';
			}

			// progress in %
			short curr_percent = (++count) * 100 / frame_count;
			if (m_log && last_percent != curr_percent)
			{
				std::cout << '\r';
				for (size_t i = 0; i < 4; i++)
					std::cout << ' ';
				std::cout << '\r' << curr_percent << '%';
			}
		}
	}
} // ascii
