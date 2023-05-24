#pragma once
#include <string>
#include <iostream>
namespace Pineter
{
	namespace PRaw
	{
		//最大可容许字节数
#define MAX_DATA_SIZE (32768 * 32768)

//单像素结构
		struct TripleRGB
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
		};

		//图像数据基础类
		class Raw
		{
		public:
			inline Raw(const unsigned int& width, const unsigned int& height) : width_(width), height_(height) {}

			//指定像素重载纯虚函数 括号有点不好读，想用多重方括弧。但是好麻烦
			virtual TripleRGB& operator()(unsigned int x, unsigned int y) = 0;
			unsigned int width_;
			unsigned int height_;
		};

		//多维数组模板结构
		//Matrix<int, a, b, c, d>::type mat;
		//mat[i][j][k][m] = 0;
		template <typename T, size_t R, size_t... C>
		struct Matrix
		{
			using Col = typename Matrix<T, C...>::type;
			using type = std::array<Col, R>;
		};

		template <typename T, size_t R>
		struct Matrix<T, R>
		{
			using type = std::array<T, R>;
		};
	}

	namespace colors
	{\
		//定义颜色
		constexpr PRaw::TripleRGB BLUE = { 0, 0, 255 };
		constexpr PRaw::TripleRGB GREEN = { 0, 255, 0 };
		constexpr PRaw::TripleRGB RED = { 255, 0, 8 };
		constexpr PRaw::TripleRGB NAVY_BLUE = { 0, 0, 128 };
		constexpr PRaw::TripleRGB BLACK = { 0,0,0 };
		constexpr PRaw::TripleRGB WHITE = { 255, 255, 255 };
	}
}