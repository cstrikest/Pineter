﻿#include "bmp.h"

Bmp::Bmp(Raw& raw)
{
	info_.biWidth = raw.width_;
	info_.biHeight = raw.height_;

	row_offset_ = getRowOffset(info_.biWidth);

	header_.bfSize = (info_.biWidth * 3 + row_offset_) * info_.biHeight + header_.bfOffBits;
	info_.biSizeImage = (info_.biWidth * 3 + row_offset_) * info_.biHeight;

	bmp_binary_ = new char[header_.bfOffBits + info_.biSizeImage];
	char* image_data = toBmpBinary(raw);
	memcpy(bmp_binary_, &header_, sizeof(BmpFileHeader));
	memcpy(bmp_binary_ + sizeof(BmpFileHeader), &info_, sizeof(BmpInfoHeader));
	memcpy(bmp_binary_ + sizeof(BmpFileHeader) + sizeof(BmpInfoHeader), image_data, info_.biSizeImage);
	delete[] image_data;
}

Bmp::Bmp(const char* path)
{

	std::ifstream ifs(path, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) throw FileNotExistException();
	else while (ifs >> bmp_binary_);
	ifs.close();

	memcpy((char*)&header_, bmp_binary_, sizeof(BmpFileHeader));
	memcpy((char*)&info_, bmp_binary_ + sizeof(BmpFileHeader), sizeof(BmpInfoHeader));

	bmp_binary_ = new char[info_.biSizeImage];

	verifyIntegrity();
	row_offset_ = getRowOffset(info_.biWidth);
}

void Bmp::verifyIntegrity()
{
	if (header_.bfType != 0x4d42 ||
		header_.bfReserved1 != 0x00 ||
		header_.bfReserved2 != 0x00 ||
		info_.biWidth != 0 ||
		info_.biHeight != 0 ||
		header_.bfSize != (info_.biWidth * 3 + row_offset_) * info_.biHeight + header_.bfOffBits ||
		info_.biSizeImage != (info_.biWidth * 3 + row_offset_) * info_.biHeight)
		throw IllegalBmpFileException();
}

char* Bmp::toBmpBinary(Raw& raw)
{
	int offset = getRowOffset(raw.width_);
	int size = (raw.width_ * 3 + offset) * raw.height_;
	char* data = new char[size];
	unsigned int index = 0;
	//BMP像素顺序从左下开始 所以反转y轴坐标开始遍历
	for (int j = raw.height_ - 1; j >= 0; --j)
	{
		for (int i = 0; i < raw.width_; ++i)
		{
			//B G R顺序写3字节
			data[index++] = raw(i, j)->b;
			data[index++] = raw(i, j)->g;
			data[index++] = raw(i, j)->r;
	;	}
		for (int o = 0; o < offset; ++o)
		{
			data[index++] = '\0';
		}
	}
	return data;
}

//需要delete
LinearRgb24b* Bmp::toLinearRgb24b() const
{
	char sink = ' ';
	LinearRgb24b* image = new LinearRgb24b(info_.biWidth, info_.biHeight);

	int each_pixel_start_index = 0;
	TripleRGB temp{ 0, 0, 0 };
	//这里循环的是左下角为原点的BMP格式坐标
	for (int y = 0; y < info_.biHeight; ++y)
	{
		for (int x = 0; x < info_.biWidth; ++x)
		{
			//每行有width*3+row_offset_个字节
			//单像素BGR数据 B位
			each_pixel_start_index = y * (info_.biWidth * 3 + row_offset_) + x * 3;

			temp.b = bmp_binary_[each_pixel_start_index];
			temp.g = bmp_binary_[each_pixel_start_index + 1];
			temp.r = bmp_binary_[each_pixel_start_index + 2];

			*((*image)(x, info_.biHeight - y - 1)) = temp;
		}
	}
	return image;
}

//void Bmp::toRaw(Raw& raw)
//{
//	char sink = ' ';
//	for (int by = 0; by < info_.biHeight; by++)
//	{
//		for (int bx = 0; bx < info_.biWidth; bx++)
//		{
//			memcpy(raw(bx, raw.height_ - by - 1),
//				(bmp_binary_ + row_offset_ * by) + (by * info_.biWidth + bx), 3);
//		}
//	}
//}

unsigned int Bmp::getRowOffset(const unsigned int& width) const
{
	return ((width * 3) % 4) != 0 ? 4 - ((width * 3) % 4) : 0;
}

void Bmp::save(const char* path) const
{
	std::ofstream ofs(path, std::ios::binary | std::ios::out);
	if (!ofs.is_open()) throw FileNotCantWrite(path);

	while (ofs << bmp_binary_);
	/*ofs.write((char*)&header_, sizeof(BmpFileHeader));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp header.");
	ofs.write((char*)&info_, sizeof(BmpInfoHeader));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp info.");
	ofs.write(bmp_binary_, sizeof(info_.biSizeImage));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp image data.");*/

	ofs.flush();
	ofs.close();
}