#include "image_func.h"
#include <cmath>

namespace Pineter
{
	namespace PImageFunctions
	{
		PRaw::LinearRgb24b& randMagenta(PRaw::LinearRgb24b& img)
		{
			for (int x = img.width_ - 1; x >= 0; --x)
			{
				for (int y = img.height_ - 1; y >= 0; --y)
				{
					img(x, y)->b = (int)(pow(x, rand())) % 255;
					img(x, y)->r = (int)(pow(y, rand())) % 255;
				}
			}
			return img;
		}

		PRaw::LinearRgb24b& chaos(PRaw::LinearRgb24b& img)
		{
			for (int x = img.width_ - 1; x >= 0; --x)
			{
				for (int y = img.height_ - 1; y >= 0; --y)
				{
					img(x, y)->b = (int)(tan(x % (img.height_ - y)) * y) % 255;
					img(x, y)->g = (int)(sin(x % (y + 1)) * 255) % 255;
					img(x, y)->r = (int)(cos(y % (img.width_ - x)) * x) % 255;
				}
			}
			return img;
		}

		PRaw::LinearRgb24b& verticalMosaic(PRaw::LinearRgb24b& img)
		{
			for (int i = img.width_ - 1; i >= 0; --i)
			{
				if (i % 2 == 0)
				{
					for (int j = img.height_ - 1; j >= 0; --j)
					{
						if (i % 3 == 0) *img(i, j) = colors::RED;
						else if (i % 4 == 0) *img(i, j) = colors::BLUE;
						else *img(i, j) = colors::GREEN;
					}
				}
			}
			return img;
		}

		PRaw::LinearRgb24b& horizontalFlip(PRaw::LinearRgb24b& img)
		{
			for (int y = 0; y < img.height_; y++)
			{
				for (int x = 0; x < img.width_ / 2; x++)
				{
					std::swap(*img(x, y), *img(img.width_ - 1 - x, y));
				}
			}
			return img;
		}

		PRaw::LinearRgb24b& verticalFlip(PRaw::LinearRgb24b& img)
		{
			for (int x = 0; x < img.width_; x++)
			{
				for (int y = 0; y < img.height_ / 2; y++)
				{
					std::swap(*img(x, y), *img(x, img.height_ - 1 - y));
				}
			}
			return img;
		}

		PRaw::LinearRgb24b& fullReverse(PRaw::LinearRgb24b& img)
		{
			return img >> horizontalFlip >> verticalFlip;
		}
	}
}