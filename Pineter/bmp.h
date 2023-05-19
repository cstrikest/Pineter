#pragma once
//#pragma once 和 #ifndef #define 的作用确实是防止一个头文件在同一个源文件中被多次包含。
//然而，这并不能解决链接时的重复符号问题，因为这个问题是由多个源文件包含同一个头文件导致的。
//在这种情况下，虽然每个源文件都只包含一份头文件的内容，但是当链接器将所有源文件链接在一起时，
//它会发现有多个相同的符号定义，从而导致重复符号错误。

//各种防止重复包含的方法是防止同一个源文件包含多个相同的头文件（间接重复包含）
//不是防止多个源文件包含同一个。毕竟头文件用途就是为了让多个源文件去包含他。
//所以在头文件定义了非成员函数之后，会出现符号错误。

//bmp.h
//BMP文件操作类 定义BMP文件结构与读写函数
//使用包含RGB三个颜色数据的结构代表每个像素（RAW数据)

#include <fstream>
#include "linear_rgb_24bit.h"
#include "pineter_exception.h"

//0x00
#define ZERO_CHAR  ""

//BMP文件标识符，目前仅支持BM
#define BITMAP_BM 0x4d42	//Windows3+,NT	Bitmap
#define BITMAP_BA 0x4142	//OS/2			Bitmap Array
#define BITMAP_CI 0x4943	//				Color Icon
#define BITMAP_CP 0x5043	//				Color pointer
#define BITMAP_IC 0x4349	//				Icon
#define BITMAP_PT 0x5450	//				Pointer

//按照n字节对齐
//不对齐的话bfSize会落到0x04上，文件头就会变成16字节，无法读取
#pragma pack(2)
//BMP文件头 定义了文件标识符 文件大小等											14bytes
struct BmpFileHeader
{
	unsigned short			bfType = BITMAP_BM;		//位图标识符				2
	unsigned int			bfSize;					//文件大小				4
	const unsigned short	bfReserved1 = 0x00;		//固定置0位				2
	const unsigned short	bfReserved2 = 0x00;		//固定置0位				2
	const unsigned int		bfOffBits = 0x36;		//图片信息偏移量			4
};

//这里按min(SIZE,MAX_SIZE)对齐正好，所以恢复默认
#pragma pack()
//BMP信息头 定义了图片具体信息													40bytes
struct BmpInfoHeader
{
	const unsigned int		biSize = 40;			//信息头长度				4
	int						biWidth;				//宽 为负则是翻转			4
	int						biHeight;				//高						4
	const unsigned short	biPlanes = 1;			//面数 都是平面图所以置1	2
	const unsigned short	biBitCount = 24;		//像素位数 3原色8bit分解能	2
	const unsigned int		biCompression = 0;		//压缩方式 0不压缩			4
	unsigned int			biSizeImage;			//图像信息大小			4
	const int				biXPelsPerMeter = 300;	//横向PPI				4
	const int				biYPelsPerMeter = 300;	//纵向PPI				4
	const unsigned int		biClrUsed = 0;			//彩色表中的颜色索引数		4
	const unsigned int		biClrImportant = 0;		//重要颜色索引数 0为都重要	4
};

class Bmp
{
private:
	//BMP文件头
	BmpFileHeader header_;
	//BMP信息头
	BmpInfoHeader info_;
	//BMP二进制数据
	char* bmp_binary_ = nullptr;
	//补0行偏移量
	unsigned int row_offset_;
	//读bmp文件长宽
	static std::pair<int, int> readBmpSize(const char*);
	//验证合法性，不合法抛出异常
	void verifyIntegrity();
	//根据width与4的模计算行偏移量
	unsigned int getRowOffset(const unsigned int& width) const;

public:
	//从Raw新建Bmp对象
	Bmp(Raw& raw);
	//从BMP文件新建对象
	Bmp(const char* path);
	inline ~Bmp() { delete[] bmp_binary_; }

	inline int getBfSize() const { return header_.bfSize; }
	inline int getBiSize() const { return info_.biSize; }
	inline int getRowOffset() const { return row_offset_; }

	//转换到BMP二进制数据(不包含文件头和信息头)
	char* toBmpBinary(Raw& raw);
	//写数据到LinearRgb24b类
	LinearRgb24b* toLinearRgb24b() const;
	//从Raw类写BMP文件
	void save(const char* path) const;

};
