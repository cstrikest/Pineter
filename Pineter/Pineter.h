#pragma once

#include <QtWidgets/QMainWindow>
#include <QStandardPaths>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qcolor.h>


#include "ui_Pineter.h"
#include "bmp.h"
#include "linear_rgb_24bit.h"
#include "image_func.h"

namespace Pineter
{
	namespace Program
	{
#define DEFAULT_WORK_PATH QStandardPaths::locate(QStandardPaths::DesktopLocation, "", QStandardPaths::LocateDirectory)
		class Pineter : public QMainWindow
		{
			Q_OBJECT

		public:
			Pineter(QWidget* parent = nullptr);
			inline ~Pineter() { delete image_; }

		private slots:
			//菜单槽
			//File
			void menuOpen();
			void menuSave();
			void menuSaveAs();
			void menuClose();
			void menuQuit();

			void menuEVF();
			void menuEHF();
			void menuERM();
			void menuEC();
			void menuEVM();
			void menuEFR();
			//void menuPineapple();
			

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
			void refreshImage();

			void imageOpen();
			void imageSave();
			void imageSaveAs();
			void imageClose();
		};
	}
}