#include "image_bgr_24bit.h"
#include "bmp.h"
#include "colors.h"

ImageBgr24b::ImageBgr24b(int width, int height): width_(width), height_(height)
{
	if (getArea() > MAX_DATA_SIZE)
		throw TooBigToLoadException(getArea(), MAX_DATA_SIZE);
	data_ = new TripleBGR[getArea()];
	std::cout << "new image" << std::endl;
}

ImageBgr24b::ImageBgr24b(const ImageBgr24b& i): width_(i.width_), height_(i.height_)
{
	data_ = new TripleBGR[getArea()];
	memcpy(data_, i.data_, getArea());
	std::cout << "copy image" << std::endl;
}

ImageBgr24b::ImageBgr24b(ImageBgr24b&& i) noexcept
{
	data_ = new TripleBGR[getArea()];
	data_ = i.data_;
	i.data_ = nullptr;
	std::cout << "move image" << std::endl;
}

ImageBgr24b& ImageBgr24b::operator=(const ImageBgr24b& i)
{
	if (this != &i)
	{
		width_ = i.width_;
		height_ = i.height_;
		delete[] data_;
		data_ = new TripleBGR[getArea()];
		memcpy(data_, i.data_, getArea());
	}
	std::cout << "=copy image" << std::endl;
	return *this;
}

ImageBgr24b& ImageBgr24b::operator=(ImageBgr24b&& i) noexcept
{
	if (this != &i)
	{
		width_ = i.width_;
		height_ = i.height_;
		delete[] data_;
		data_ = new TripleBGR[getArea()];
		data_ = i.data_;
		i.data_ = nullptr;
	}
	std::cout << "=move image" << std::endl;
	return *this;
}

void ImageBgr24b::setColor(Color c)
{
	for (int row = 0; row < height_; row++)
	{
		for (int column = 0; column < width_; column++)
		{
			*(data_ + (row * width_ + column)) = c;
		}
	}
}

//指定像素重载，从0开始
TripleBGR* ImageBgr24b::operator()(int x, int y)
{
	if (x < 0 || y < 0 || x >= width_ || y >= height_) throw BmpInvalidIndexException(x, y);
	return data_ + ((height_ - y - 1) * width_ + x);
}
