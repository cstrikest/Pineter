#pragma once
#include <string>
#include <iostream>

//最大可容许面积
constexpr int MAX_DATA_SIZE = 32768 * 32768;

//单像素结构
struct TripleRGB
{
	unsigned char			r;
	unsigned char			g;
	unsigned char			b;
};

//定义颜色
constexpr TripleRGB BLUE = { 0, 0, 255 };
constexpr TripleRGB GREEN = { 0, 255, 0 };
constexpr TripleRGB RED = { 255, 0, 8 };
constexpr TripleRGB NAVY_BLUE = { 0, 0, 128 };
constexpr TripleRGB BLACK = { 0,0,0 };
constexpr TripleRGB WHITE = { 255, 255, 255 };

//图像数据基础类
class Raw
{
public:
	inline Raw(const int& width, const int& height) : width_(width), height_(height) {}

	unsigned int width_;
	unsigned int height_;
};