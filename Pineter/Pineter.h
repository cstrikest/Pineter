#pragma once

#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qcolor.h>

#include "ui_Pineter.h"
#include "bmp.h"
#include "linear_rgb_24bit.h"
namespace Pineter
{
	namespace Program
	{
		class Pineter : public QMainWindow
		{
			Q_OBJECT

		public:
			Pineter(QWidget* parent = nullptr);
			inline ~Pineter() { delete image_; }

		private slots:
			//菜单槽
			//File
			void fileOpen();
			void fileSave();
			void fileSaveAs();
			void fileClose();
			//void fileQuit();
			//
			////Edit 自动生成项
			//void edit(const char* editFunc);

			////About
			//void aboutPineapple();

		private:
			Ui::PineterClass ui_;
			//正在打开的图片
			//为空则是没有打开的图片
			PRaw::LinearRgb24b* image_;
			//已打开文件的path
			//为空则是新建的文件 作为是否作为文件打开中的状态flag
			QString file_path_;
			//是否有新的改动
			bool is_changed_;

			//void paintEvent(QPaintEvent* event);
			//更新状态
			//·菜单项目可用状态
			void updateState();
		};
	}
}