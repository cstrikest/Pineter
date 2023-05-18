#pragma once
#include "image_bgr_24bit.h"

// 图像处理命名空间
// LinearRgb24b& (*)(LinearRgb24b&)类型的函数实现了>>重载，支持链式调用
// image>>horizontalFilp>>fillColor;
namespace image_func
{
	typedef LinearRgb24b& (*DIRECT_IMAGE_FUNC)(LinearRgb24b&);

	inline LinearRgb24b& operator>>(LinearRgb24b& img, DIRECT_IMAGE_FUNC f)
	{
		f(img);
		return img;
	}

	LinearRgb24b& randMagenta(LinearRgb24b& img);
	LinearRgb24b& chaos(LinearRgb24b& img);
	LinearRgb24b& verticalMosaic(LinearRgb24b& img);

	LinearRgb24b& horizontalFlip(LinearRgb24b& img);
	LinearRgb24b& verticalFlip(LinearRgb24b& img);
	LinearRgb24b& fullReverse(LinearRgb24b& img);
}