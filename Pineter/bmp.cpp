#include "bmp.h"

Bmp::Bmp(Raw& raw)
{
	info_.biWidth = raw.width_;
	info_.biHeight = raw.height_;

	row_offset_ = getRowOffset(info_.biWidth);

	header_.bfSize = (info_.biWidth * 3 + row_offset_) * info_.biHeight + header_.bfOffBits;
	info_.biSizeImage = (info_.biWidth * 3 + row_offset_) * info_.biHeight;

	bmp_binary_ = new char[header_.bfSize];

	//不含头的BMP格式二进制图像数据
	char* image_data = toBmpBinary(raw);
	memcpy(bmp_binary_, &header_, sizeof(BmpFileHeader));
	memcpy(bmp_binary_ + sizeof(BmpFileHeader), &info_, sizeof(BmpInfoHeader));
	memcpy(bmp_binary_ + sizeof(BmpFileHeader) + sizeof(BmpInfoHeader), image_data, info_.biSizeImage);
	delete[] image_data;
}

Bmp::Bmp(const char* path)
{
	//文件指针初始位置定位到文件尾  std::ios::ate
	std::ifstream ifs(path, std::ios::binary | std::ios::ate);

	if (!ifs.is_open()) throw FileNotExistException();

	//获取文件大小
	std::streamsize size = ifs.tellg();
	//指回文件头
	ifs.seekg(0, std::ios::beg);
	//创建临时内存
	char* buffer = new char[size];
	if (!ifs.read(buffer, size)) throw FileNotCantWrite(QString(path));
	ifs.close();

	memcpy((char*)&header_, buffer, sizeof(BmpFileHeader));
	memcpy((char*)&info_, buffer + sizeof(BmpFileHeader), sizeof(BmpInfoHeader));

	bmp_binary_ = new char[header_.bfSize];

	memcpy(bmp_binary_, buffer, header_.bfSize);
	delete[] buffer;

	row_offset_ = getRowOffset(info_.biWidth);
	verifyIntegrity();
}

void Bmp::verifyIntegrity()
{
	if (header_.bfType != 0x4d42 ||
		header_.bfReserved1 != 0x00 ||
		header_.bfReserved2 != 0x00 ||
		info_.biWidth == 0 ||
		info_.biHeight == 0 ||
		header_.bfSize != (info_.biWidth * 3 + row_offset_) * info_.biHeight + header_.bfOffBits ||
		info_.biSizeImage != (info_.biWidth * 3 + row_offset_) * info_.biHeight)
		throw IllegalBmpFileException();
}

char* Bmp::toBmpBinary(Raw& raw)
{
	int offset = getRowOffset(raw.width_);
	int size = (raw.width_ * 3 + offset) * raw.height_;
	char* data = new char[size];

	unsigned int cursor = 0;
	//BMP像素顺序从左下开始 所以反转y轴坐标开始遍历
	for (int j = raw.height_ - 1; j >= 0; --j)
	{
		for (int i = 0; i < raw.width_; ++i)
		{
			//B G R顺序写3字节
			data[cursor++] = raw(i, j)->b;
			data[cursor++] = raw(i, j)->g;
			data[cursor++] = raw(i, j)->r;
			;
		}
		for (int o = 0; o < offset; ++o) data[cursor++] = 0;
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

	int cursor = header_.bfOffBits;

	//这里循环的是左下角为原点的BMP格式坐标
	for (int y = 0; y < info_.biHeight; ++y)
	{
		for (int x = 0; x < info_.biWidth; ++x)
		{
			//每行有width*3+row_offset_个字节
			//单像素BGR数据 B位
			temp.b = bmp_binary_[cursor++];
			temp.g = bmp_binary_[cursor++];
			temp.r = bmp_binary_[cursor++];

			*((*image)(x, info_.biHeight - y - 1)) = temp;
		}
		for (int o = 0; o < row_offset_; ++o) cursor++;
		//info_.biWidth * 3 + row_offset_;
	}
	return image;
}

unsigned int Bmp::getRowOffset(const unsigned int& width) const
{
	return ((width * 3) % 4) != 0 ? 4 - ((width * 3) % 4) : 0;
}

void Bmp::save(const char* path) const
{
	std::ofstream ofs(path, std::ios::binary | std::ios::out);
	if (!ofs.is_open()) throw FileNotCantWrite(path);
	ofs.write(bmp_binary_, header_.bfSize);
	/*ofs.write((char*)&header_, sizeof(BmpFileHeader));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp header.");
	ofs.write((char*)&info_, sizeof(BmpInfoHeader));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp info.");
	ofs.write(bmp_binary_, sizeof(info_.biSizeImage));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp image data.");*/

	ofs.flush();
	ofs.close();
}