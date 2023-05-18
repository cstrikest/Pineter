#include "bmp.h"

Bmp::Bmp(const unsigned int& width, const unsigned int& height)
{
	info_.biWidth = width;
	info_.biHeight = height;

	setRowOffset();

	header_.bfSize = (width * 3 + row_offset_) * height + header_.bfOffBits;
	info_.biSizeImage = (width * 3 + row_offset_) * height;

	bmpBinary = new char[info_.biSizeImage];
}

Bmp::Bmp(const char* path)
{
	std::ifstream ifs(path, std::ios::binary | std::ios::in);
	if (!ifs.is_open()) throw FileNotExistException();
	else
	{
		while (ifs >> bmpBinary);
	}
	ifs.close();

	memcpy((char*)&header_, bmpBinary, sizeof(BmpFileHeader));
	memcpy((char*)&info_, bmpBinary+ sizeof(BmpFileHeader), sizeof(BmpInfoHeader));

	verifyIntegrity();
	setRowOffset();
}

void Bmp::verifyIntegrity()
{
	if (header_.bfType != 0x4d42 ||
		header_.bfReserved1 != 0x00 ||
		header_.bfReserved2 != 0x00 ||
		info_.biWidth == 0 ||
		info_.biHeight == 0) throw IllegalBmpFileException();
}

void Bmp::toRaw(Raw& raw)
{
	char sink = ' ';
	for (int by = 0; by < info_.biHeight; by++)
	{
		for (int bx = 0; bx < info_.biWidth; bx++)
		{
			memcpy(raw(bx, raw.height_ - by - 1), 
				(bmpBinary + row_offset_ * by) + (by * info_.biWidth + bx), 3);
		}
	}
}

void Bmp::setRowOffset()
{
	row_offset_ = (info_.biWidth * 3) % 4;
	if (row_offset_ != 0) row_offset_ = 4 - row_offset_;
}

void Bmp::save(const char* path, Raw& raw)
{
	std::ofstream ofs(path, std::ios::binary | std::ios::out);
	if (!ofs.is_open()) throw FileNotCantWrite(path);
	//while (ofs << bmpBinary);
	//ofs.flush();
	//ofs.close();

	ofs.write((char*)&header_, sizeof(BmpFileHeader));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp header.");
	ofs.write((char*)&info_, sizeof(BmpInfoHeader));
	if (ofs.fail()) throw std::runtime_error("Failed to write Bmp info.");
	for (int by = 0; by < info_.biHeight; by++)
	{
		for (int bx = 0; bx < info_.biWidth; bx++)
		{
			ofs.write(toBmpBinary(bx, by));
			//ofs.write((char*)(data_ + (by * info_.biWidth + bx)), 3);
		}
		//for (int t = row_offset_; t > 0; t--)
		//{
		//	ofs.write("", 1);
		//}
		//if (ofs.fail()) throw std::runtime_error("Failed to write Bmp image data.");
	}
	ofs.flush();
	ofs.close();
}

int Bmp::toImageData(int b_x, int b_y) 
{
	int rowBytes = ((info_.biWidth * 3) + 3) & ~3;  // 计算每行像素数据的字节数（补0对齐）
	int y = info_.biHeight - 1 - b_y;  // 转换坐标
	int offset = y * rowBytes + b_x * 3;  // 计算偏移量
	return offset;
}

int Bmp::toBmpBinary(int x, int y) {
	int rowBytes = ((info_.biWidth * 3) + 3) & ~3;  // 计算每行像素数据的字节数（补0对齐）
	int offset = (info_.biHeight - 1 - y) * rowBytes + x * 3;  // 计算偏移量
	return offset;
}