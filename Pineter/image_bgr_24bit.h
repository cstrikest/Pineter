#pragma once
#include <exception>
#include <string>
#include <iostream>

//最大可容许面积
constexpr int MAX_DATA_SIZE = 32768 * 32768;

//单像素结构
struct TripleBGR
{
	unsigned char			b;
	unsigned char			g;
	unsigned char			r;
};

typedef TripleBGR Color;

//图像RAW数据类，线性储存各个像素BGR值
class ImageBgr24b
{
public:
	int width_;
	int height_;
	TripleBGR* data_;

	ImageBgr24b(int width, int height);
	inline virtual ~ImageBgr24b() { delete[] data_; std::cout << "del image" << std::endl;}
	ImageBgr24b(const ImageBgr24b&);
	ImageBgr24b(ImageBgr24b&&) noexcept;
	ImageBgr24b& operator=(const ImageBgr24b&);
	ImageBgr24b& operator=(ImageBgr24b&&) noexcept;

	inline int getArea() const { return width_ * height_; }

	//重写颜色
	void setColor(Color c);
	//指定像素重载 括号有点不好读，想用多重方括弧。但是好麻烦
	TripleBGR* operator()(int, int);
};

//图片面积过大异常
class TooBigToLoadException : public std::exception
{
public:
	inline TooBigToLoadException(int actualSize, int maxSize)
		: std::exception(("Image too big to load. Actual size: " +
			std::to_string(actualSize) + ", Max size: " +
			std::to_string(maxSize)).c_str()) {}
};
