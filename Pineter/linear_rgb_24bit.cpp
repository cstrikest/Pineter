#include "linear_rgb_24bit.h"
#include "pineter_exception.h"

LinearRgb24b::LinearRgb24b(const unsigned int& width, const unsigned int& height) : Raw(width, height)
{
	int size = width * height * 3;
	if (size > MAX_DATA_SIZE)
		throw TooBigToLoadException(size, MAX_DATA_SIZE);
	data_ = new TripleRGB[getPixelNum()];
}

LinearRgb24b::LinearRgb24b(const LinearRgb24b& i) : Raw(i.width_, i.height_)
{
	data_ = new TripleRGB[getPixelNum()];
	memcpy(data_, i.data_, getSize());
}

LinearRgb24b::LinearRgb24b(LinearRgb24b&& i) noexcept : Raw(i.width_, i.height_)
{
	data_ = new TripleRGB[getPixelNum()];
	data_ = i.data_;
	i.data_ = nullptr;
}

//指定像素坐标，返回TripleRGB
TripleRGB* LinearRgb24b::operator()(const unsigned int x, const unsigned int y)
{
	if (x < 0 || y < 0 || x >= width_ || y >= height_) throw InvalidIndexException(x, y);
	return data_ + (y * width_ + x);
}
