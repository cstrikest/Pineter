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
#include "image_bgr_24bit.h"

//0x00指针
constexpr const char* ZERO_CHAR = "";

//BMP文件标识符
enum BF_TYPE
{
	BM = 0x4d42,	//Windows3+ ,NT
	BA = 0x4142,	//OS/2	Bitmap Array
	CI = 0x4943,	//		Color Icon
	CP = 0x5043,	//		Color pointer
	IC = 0x4349,	//		Icon
	PT = 0x5450		//		Pointer
};


//按照n字节对齐
//不对齐的话bfSize会落到0x04上，文件头就会变成16字节，无法读取
#pragma pack(2)
//BMP文件头 定义了文件标识符 文件大小等											14bytes
struct BmpFileHeader
{
	unsigned short			bfType;					//标识符，一般是BM			2
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

class Bmp : public ImageBgr24b
{
private:
	//BMP文件头
	BmpFileHeader header_;
	//BMP信息头
	BmpInfoHeader info_;
	//补0行偏移量
	unsigned int row_offset_;
	//读bmp文件长宽
	static std::pair<int, int> readBmpSize(const char*);

public:
	//创建空对象
	Bmp(BF_TYPE type, int width, int height);
	//从BMP文件读
	Bmp(const char* path);
	//从RAW创建
	Bmp(BF_TYPE, const ImageBgr24b&);

	inline virtual ~Bmp() { std::cout << "del bmp" << std::endl; }
	inline Bmp(const Bmp& bmp) :
		ImageBgr24b(bmp),
		header_(bmp.header_),
		info_(bmp.info_),
		row_offset_(bmp.row_offset_) {
		std::cout << "copy image" << std::endl;
	}
	inline Bmp(Bmp&& bmp) noexcept :
		ImageBgr24b(bmp),
		header_(bmp.header_),
		info_(bmp.info_),
		row_offset_(bmp.row_offset_) {
		std::cout << "move image" << std::endl;
	}

	inline int getImgSize() const { return info_.biWidth * info_.biHeight * 3; }
	inline int getPixelNumber() const { return info_.biWidth * info_.biHeight; }
	inline int getBfSize() const { return header_.bfSize; }
	inline int getBiSize() const { return info_.biSize; }
	inline int getWidth() const { return info_.biWidth; }
	inline int getHeight() const { return info_.biHeight; }
	inline int getRowOffset() const { return row_offset_; }
	inline ImageBgr24b getImageBgr24b() { return *this; }

	//根据width与4的模计算行偏移量
	void setRowOffset();

	//写BMP文件
	void save(const char* path);

};

//异常类定义
class BmpInvalidIndexException : public std::invalid_argument
{
public:
	inline BmpInvalidIndexException(int x, int y)
		: std::invalid_argument("Invalid pixel index. x: " +
			std::to_string(x) + " y: " + std::to_string(y)) {}
};

class BmpFileNotExistException : public std::exception
{
public:
	inline BmpFileNotExistException() : exception("File not exist.") {}
};

class BmpFileNotCantWrite : public std::exception
{
public:
	inline BmpFileNotCantWrite(std::string file_path) : exception((std::string("Can't write image to ") + file_path).c_str()) {}
};