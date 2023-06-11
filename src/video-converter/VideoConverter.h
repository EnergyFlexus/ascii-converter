#ifndef VIDEO_CONVERTER
#define VIDEO_CONVERTER

#include <fstream>
#include <cmath>

#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>

namespace ascii
{
	class VideoConverter
	{
	public:
		VideoConverter() = default;
		~VideoConverter() = default;

		void SetGradient(const std::string& gradient);
		void SetConsoleCoefficient(double consoleCoefficient);
		void SetLog(bool log);

		// auto asciiHeight rescaling if 0
		void Convert(const std::string& filename, std::ostream &output, short asciiWidth = 80, short asciiHeight = 0);

	private:
		std::string m_gradient = " .:-=+*#%@";
		double m_consoleCoefficient = 0.8;
		bool m_log = false;

		char GrayToAscii(uchar gray);
	};
} // ascii

#endif // VIDEO_CONVERTER