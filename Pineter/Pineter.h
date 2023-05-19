#pragma once

#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qcolor.h>

#include "ui_Pineter.h"
#include "bmp.h"
#include "linear_rgb_24bit.h"

class Pineter : public QMainWindow
{
	Q_OBJECT

public:
	Pineter(QWidget* parent = nullptr);
	~Pineter();


private slots:
	//菜单槽
	//File
	void fileOpen();
	void fileSave();
	void fileSaveAs();
	//void fileClose();
	//void fileQuit();
	//
	////Edit 自动生成项
	//void edit(const char* editFunc);

	////About
	//void aboutPineapple();

private:
	Ui::PineterClass ui_;
	LinearRgb24b* image_;
	//已打开文件的path，新建的文件则为空
	QString file_path_;
	//void paintEvent(QPaintEvent* event);
};

class NoActiveImageFoundException : public std::exception
{
public: NoActiveImageFoundException() : std::exception("Opening image not found.") {}
};