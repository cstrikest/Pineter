#pragma once
#include "image_bgr_24bit.h"

// 图像处理命名空间
// ImageBgr24b& (*)(ImageBgr24b&)类型的函数实现了>>重载，支持链式调用
// image>>horizontalFilp>>fillColor;
namespace image_func
{
	typedef ImageBgr24b& (*DIRECT_IMAGE_FUNC)(ImageBgr24b&);

	inline ImageBgr24b& operator>>(ImageBgr24b& img, DIRECT_IMAGE_FUNC f)
	{
		f(img);
		return img;
	}

	ImageBgr24b& randMagenta(ImageBgr24b& img);
	ImageBgr24b& chaos(ImageBgr24b& img);
	ImageBgr24b& verticalMosaic(ImageBgr24b& img);

	ImageBgr24b& horizontalFlip(ImageBgr24b& img);
	ImageBgr24b& verticalFlip(ImageBgr24b& img);
	ImageBgr24b& fullReverse(ImageBgr24b& img);
}