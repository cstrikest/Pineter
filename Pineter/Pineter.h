#pragma once

#include <QtWidgets/QMainWindow>
#include <QStandardPaths>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qpainter.h>
#include <qcolor.h>
#include <qpalette.h>
#include <qpixmap.h>
#include <qrgb.h>

#include "ui_Pineter.h"
#include "bmp.h"
#include "linear_rgb_24bit.h"
#include "image_func.h"

//宏定义
#define DEFAULT_WORK_PATH QStandardPaths::locate(QStandardPaths::DesktopLocation, "", QStandardPaths::LocateDirectory)
#define STATE_LABEL_NO_IMAGE "no image opened"
#define STATE_LABEL_IMAGE_OPENED "opened"
#define STATE_LABEL_IMAGE_CREATED "new image"
#define STATE_LABEL_IMAGE_CHANGED " * changed"
#define QRGB_COLOR_DEFALUT_GARY qRgb(100, 100, 100)

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
			void menuPineapple();

		private:
			//GUI
			Ui::PineterClass ui_;
			//正在打开的图片 为空指针则是没有打开的图片
			PRaw::LinearRgb24b* image_;
			//已打开文件的path 为空则是新建的文件 作为是否作为文件打开中的状态flag
			QString file_path_;
			//是否有新的改动
			bool is_changed_;

			void updateState();
			void refreshScreen();
			void grayOutScreen();
			void imageOpen();
			void imageSave();
			void imageSaveAs();
			void imageClose();

			virtual void resizeEvent(QResizeEvent* event) override;
		};
	}
}