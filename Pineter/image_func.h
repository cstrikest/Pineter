#pragma once
#include "linear_rgb_24bit.h"

// 图像处理命名空间
// LinearRgb24b& (*)(LinearRgb24b&)类型的函数实现了>>重载，支持链式调用
// image>>horizontalFilp>>fillColor;
namespace Pineter
{
	namespace PImageFunctions
	{
		typedef PRaw::LinearRgb24b& (*DIRECT_IMAGE_FUNC)(PRaw::LinearRgb24b&);

		inline PRaw::LinearRgb24b& operator>>(PRaw::LinearRgb24b& img, DIRECT_IMAGE_FUNC f)
		{
			f(img);
			return img;
		}

		PRaw::LinearRgb24b& randMagenta(PRaw::LinearRgb24b& img);
		PRaw::LinearRgb24b& chaos(PRaw::LinearRgb24b& img);
		PRaw::LinearRgb24b& verticalMosaic(PRaw::LinearRgb24b& img);

		PRaw::LinearRgb24b& horizontalFlip(PRaw::LinearRgb24b& img);
		PRaw::LinearRgb24b& verticalFlip(PRaw::LinearRgb24b& img);
		PRaw::LinearRgb24b& fullReverse(PRaw::LinearRgb24b& img);
	}
}