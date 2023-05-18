#pragma once
#include <exception>
#include <qstring.h>

//图片面积过大异常
class TooBigToLoadException : public std::exception
{
public: inline TooBigToLoadException(const int& actualSize, const int& maxSize) :
	std::exception(("Image too big to load. Actual size: " +
		QString::number(actualSize) +
		", Max size: " +
		QString::number(maxSize)).toLatin1().data()) {}
};

//图片坐标索引异常
class InvalidIndexException : public std::exception
{
public: inline InvalidIndexException(const int& x, const int& y) :
	std::exception(("Invalid pixel index. x:" +
		QString::number(x) +
		", y: " +
		QString::number(y)).toLatin1().data()) {}
};

//图片不存在异常
class FileNotExistException : public std::exception
{
public:
	inline FileNotExistException() : exception("File not exist.") {}
};

//图片写入异常
class FileNotCantWrite : public std::exception
{
public:
	inline FileNotCantWrite(QString file_path) : 
		exception((QString("Can't write image to ") + file_path).toLatin1().data()) {}
};

//非法BMP格式异常
class IllegalBmpFileException : public std::exception
{
public:
	inline IllegalBmpFileException() : exception("Illegal bmp file deceted.") {}
};