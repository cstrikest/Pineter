#include "bmp.h"
#include "colors.h"

std::pair<int, int> Bmp::readBmpSize(const char* path)
{
	std::ifstream ifs(path, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) throw BmpFileNotExistException();
	BmpInfoHeader i;
	ifs.read((char*)&i, sizeof(BmpFileHeader));
	if (ifs.fail()) throw std::runtime_error("Failed to read Bmp header.");
	ifs.read((char*)&i, sizeof(BmpInfoHeader));
	if (ifs.fail()) throw std::runtime_error("Failed to read Bmp info.");
	return std::make_pair(i.biWidth, i.biHeight);
}

Bmp::Bmp(BF_TYPE type, int w, int h) : ImageBgr24b(w, h)
{
	header_.bfType = type;
	width_ = w;
	height_ = h;
	info_.biWidth = width_;
	info_.biHeight = height_;

	setRowOffset();

	header_.bfSize = (width_ * 3 + row_offset_) * height_ + header_.bfOffBits;
	info_.biSizeImage = (width_ * 3 + row_offset_) * height_;
	std::cout << "new bmp" << std::endl;
}

//从BMP文件读
Bmp::Bmp(const char* path) : ImageBgr24b(readBmpSize(path).first, readBmpSize(path).second)
{
	std::ifstream ifs(path, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) throw BmpFileNotExistException();
	ifs.read((char*)&header_, sizeof(BmpFileHeader));
	if (ifs.fail()) throw std::runtime_error("Failed to read Bmp header.");
	ifs.read((char*)&info_, sizeof(BmpInfoHeader));
	if (ifs.fail()) throw std::runtime_error("Failed to read Bmp info.");

	verifyIntegrity();
	setRowOffset();

	char sink = ' ';

	for (int row = 0; row < height_; row++)
	{
		for (int column = 0; column < width_; column++)
		{
			ifs.read((char*)(data_ + (row * width_ + column)), sizeof(TripleBGR));
		}
		//埋掉占位符
		ifs.read(&sink, row_offset_);
	}
	ifs.close();
	std::cout << "new bmp" << std::endl;
}

//从RAW创建
Bmp::Bmp(BF_TYPE type, const ImageBgr24b& i) : ImageBgr24b(i.width_, i.height_)
{
	header_.bfType = type;
	info_.biWidth = i.width_;
	info_.biHeight = i.height_;
	setRowOffset();
	header_.bfSize = (width_ * 3 + row_offset_) * height_ + header_.bfOffBits;
	info_.biSizeImage = (width_ * 3 + row_offset_) * height_;
	memcpy(data_, i.data_, getArea());
}

//根据width与4的模计算行偏移量
void Bmp::setRowOffset()
{
	row_offset_ = (width_ * 3) % 4;
	if (row_offset_ != 0) row_offset_ = 4 - row_offset_;
}

//写BMP文件
void Bmp::save(const char* path)
{
	std::ofstream ofs(path, std::ios::binary | std::ios::out);
	if (!ofs.is_open()) throw BmpFileNotCantWrite(path);
	ofs.write((char*)&header_, sizeof(BmpFileHeader));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp header.");
	ofs.write((char*)&info_, sizeof(BmpInfoHeader));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp info.");
	for (int row = 0; row < height_; row++)
	{
		for (int column = 0; column < width_; column++)
		{
			ofs.write((char*)(data_ + (row * width_ + column)), 3);
		}
		for (int t = row_offset_; t > 0; t--)
		{
			ofs.write(ZERO_CHAR, 1);
		}
		if (ofs.fail()) throw std::runtime_error("Failed to write Bmp image data.");
	}
	ofs.flush();
	ofs.close();
}

void Bmp::verifyIntegrity()
{
	if (header_.bfType != 0x4d42 ||
		header_.bfReserved1 != 0x00 ||
		header_.bfReserved2 != 0x00 ||
		info_.biWidth == 0 ||
		info_.biHeight == 0) throw IllegalBmpFileException();
}
