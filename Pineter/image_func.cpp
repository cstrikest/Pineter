#include "image_func.h"
#include "colors.h"
#include <cmath>

namespace image_func
{
	LinearRgb24b& randMagenta(LinearRgb24b& img)
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

	LinearRgb24b& chaos(LinearRgb24b& img)
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

	LinearRgb24b& verticalMosaic(LinearRgb24b& img)
	{
		for (int i = img.width_ - 1; i >= 0; --i)
		{
			if (i % 2 == 0)
			{
				for (int j = img.height_ - 1; j >= 0; --j)
				{
					if (i % 3 == 0) *img(i, j) = Colors::RED;
					else if (i % 4 == 0) *img(i, j) = Colors::BLUE;
					else *img(i, j) = Colors::GREEN;
				}
			}
		}
		return img;
	}

	LinearRgb24b& horizontalFlip(LinearRgb24b& img)
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

	LinearRgb24b& verticalFlip(LinearRgb24b& img)
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

	LinearRgb24b& fullReverse(LinearRgb24b& img)
	{
		return img >> horizontalFlip >> verticalFlip;
	}
}