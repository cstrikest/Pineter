#pragma once
#include <exception>
#include <qstring.h>
namespace Pineter
{
	namespace PException
	{
		//Pineter异常类
		class PineterException : public std::exception
		{
		public: inline PineterException(QString msg) : std::exception(msg.toLatin1().data()) {}
		};

		//图片面积过大异常
		class TooBigToLoadException : public PineterException
		{
		public: inline TooBigToLoadException(const int& actualSize, const int& maxSize) :
			PineterException("Image too big to load. Actual size: " +
				QString::number(actualSize) +
				", Max size: " +
				QString::number(maxSize)) {}
		};

		//非法坐标索引异常
		class InvalidIndexException : public PineterException
		{
		public: inline InvalidIndexException(const int& x, const int& y) :
			PineterException("Invalid pixel index. x:" +
				QString::number(x) +
				", y: " +
				QString::number(y)) {}
		};

		//图片不存在异常
		class FileNotExistException : public PineterException
		{
		public:
			inline FileNotExistException() : PineterException("File not exist.") {}
		};

		//图片写入异常
		class FileNotCantWrite : public PineterException
		{
		public:
			inline FileNotCantWrite(QString file_path) :
				PineterException("Can't write image to " + file_path) {}
		};

		//非法BMP格式异常
		class IllegalBmpFileException : public PineterException
		{
		public:
			inline IllegalBmpFileException() : PineterException("Illegal bmp file deceted.") {}
		};

		//加载文件失败异常
		class LoadImageFailedException : public PineterException
		{
		public:
			inline LoadImageFailedException() : PineterException("Can't load image.") {}
		};

		//没有活动中的图片对象
		class NoActiveImageFoundException : public std::exception
		{
		public: NoActiveImageFoundException() : std::exception("Opening image not found.") {}
		};
	}
}