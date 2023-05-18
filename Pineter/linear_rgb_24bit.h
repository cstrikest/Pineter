#pragma once
#include "raw.h"

//图像RAW数据类，线性储存各个像素BGR值
//左上角为原点，坐标从0开始
class LinearRgb24b : public Raw
{
public:
	TripleRGB* data_;

	LinearRgb24b(int& width, int& height);
	inline virtual ~LinearRgb24b() { delete[] data_; }
	LinearRgb24b(const LinearRgb24b&);
	LinearRgb24b(LinearRgb24b&&) noexcept;
	LinearRgb24b& operator=(const LinearRgb24b&);
	LinearRgb24b& operator=(LinearRgb24b&&) noexcept;

	inline int getPixelNum() const { return width_ * height_; }
	inline int getSize() const { return width_ * height_ * sizeof(TripleRGB); }

	//指定像素重载 括号有点不好读，想用多重方括弧。但是好麻烦
	TripleRGB* operator()(const int x, const int y) const;
};

