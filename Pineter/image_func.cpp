#include "image_func.h"
#include <cmath>
#include <algorithm>

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
					img(x, y).b = (int)(pow(x, rand())) % 255;
					img(x, y).r = (int)(pow(y, rand())) % 255;
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
					img(x, y).b = (int)(tan(x % (img.height_ - y)) * y) % 255;
					img(x, y).g = (int)(sin(x % (y + 1)) * 255) % 255;
					img(x, y).r = (int)(cos(y % (img.width_ - x)) * x) % 255;
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
						if (i % 3 == 0) img(i, j) = colors::RED;
						else if (i % 4 == 0) img(i, j) = colors::BLUE;
						else img(i, j) = colors::GREEN;
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
					std::swap(img(x, y), img(img.width_ - 1 - x, y));
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
					std::swap(img(x, y), img(x, img.height_ - 1 - y));
				}
			}
			return img;
		}

		PRaw::LinearRgb24b& fullReverse(PRaw::LinearRgb24b& img)
		{
			return img >> horizontalFlip >> verticalFlip;
		}

		PRaw::LinearRgb24b* resizeBilinear(PRaw::LinearRgb24b* src, unsigned int targetWidth, unsigned int targetHeight)
		{
			PRaw::LinearRgb24b* dst = new PRaw::LinearRgb24b(targetWidth, targetHeight);

			float x_ratio = ((float)((*src).width_ - 1)) / targetWidth;
			float y_ratio = ((float)((*src).height_ - 1)) / targetHeight;

			for (int y = 0; y < targetHeight; y++) 
			{
				for (int x = 0; x < targetWidth; x++) 
				{
					unsigned int x1 = (int)(x_ratio * x);
					unsigned int y1 = (int)(y_ratio * y);
					float x_diff = (x_ratio * x) - x1;
					float y_diff = (y_ratio * y) - y1;

					PRaw::TripleRGB& topLeft = (*src)(x1, y1);
					PRaw::TripleRGB& topRight = (*src)(std::min(x1 + 1, (*src).width_ - 1), y1);
					PRaw::TripleRGB& bottomLeft = (*src)(x1, std::min(y1 + 1, (*src).height_ - 1));
					PRaw::TripleRGB& bottomRight = (*src)(std::min(x1 + 1, (*src).width_ - 1), std::min(y1 + 1, (*src).height_ - 1));

					(*dst)(x, y).r = (unsigned char)(
						topLeft.r * (1 - x_diff) * (1 - y_diff) +
						topRight.r * x_diff * (1 - y_diff) +
						bottomLeft.r * y_diff * (1 - x_diff) +
						bottomRight.r * x_diff * y_diff
						);

					(*dst)(x, y).g = (unsigned char)(
						topLeft.g * (1 - x_diff) * (1 - y_diff) +
						topRight.g * x_diff * (1 - y_diff) +
						bottomLeft.g * y_diff * (1 - x_diff) +
						bottomRight.g * x_diff * y_diff
						);

					(*dst)(x, y).b = (unsigned char)(
						topLeft.b * (1 - x_diff) * (1 - y_diff) +
						topRight.b * x_diff * (1 - y_diff) +
						bottomLeft.b * y_diff * (1 - x_diff) +
						bottomRight.b * x_diff * y_diff
						);
				}
			}
			delete src;
			return dst;
		}
	}
}