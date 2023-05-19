#pragma once
#include "raw.h"

//图像RAW数据类，线性储存各个像素BGR值
//左上角为原点，坐标从0开始
class LinearRgb24b : public Raw
{
public:
	TripleRGB* data_ = nullptr;

	LinearRgb24b(const unsigned int& width, const unsigned int& height);
	inline virtual ~LinearRgb24b() { delete[] data_; }
	LinearRgb24b(const LinearRgb24b&);
	LinearRgb24b(LinearRgb24b&&) noexcept;
	LinearRgb24b& operator=(const LinearRgb24b&);
	LinearRgb24b& operator=(LinearRgb24b&&) noexcept;

	inline int getPixelNum() const { return width_ * height_; }
	inline int getSize() const { return width_ * height_ * sizeof(TripleRGB); }

	//指定像素坐标，返回TripleRGB
	TripleRGB* operator()(const unsigned int x, const unsigned int y) override;
	//深复制到data_，根据长宽截断溢出数据
	void setData(TripleRGB* rawdata) override;
};

