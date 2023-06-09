﻿#pragma once
#include "raw.h"

namespace Pineter
{
	namespace PRaw
	{
		//图像RAW数据类，线性储存各个像素RGB值
		//左上角为原点，坐标从0开始
		class LinearRgb24b : public Raw
		{
		public:
			TripleRGB* data_ = nullptr;

			LinearRgb24b(const unsigned int& width, const unsigned int& height);
			inline virtual ~LinearRgb24b() { delete[] data_; }
			LinearRgb24b(const LinearRgb24b&);
			LinearRgb24b(LinearRgb24b&&) noexcept;

			inline int getPixelNum() const { return width_ * height_; }
			inline int getSize() const { return width_ * height_ * sizeof(TripleRGB); }

			//指定像素坐标，返回TripleRGB
			TripleRGB& operator()(unsigned int x, unsigned int y) override;
		};
	}
}