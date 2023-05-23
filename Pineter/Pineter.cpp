#include "Pineter.h"

namespace Pineter
{
	namespace Program
	{
		Pineter::Pineter(QWidget* parent) : QMainWindow(parent)
		{
			ui_.setupUi(this);

			//绑定信号槽
			connect(ui_.action_Open, &QAction::triggered, this, &Pineter::menuOpen);
			connect(ui_.action_Save, &QAction::triggered, this, &Pineter::menuSave);
			connect(ui_.actionSave_as, &QAction::triggered, this, &Pineter::menuSaveAs);
			connect(ui_.action_Close, &QAction::triggered, this, &Pineter::menuClose);
			connect(ui_.action_Quit, &QAction::triggered, this, &Pineter::menuQuit);
			connect(ui_.actionVertical_Flip, &QAction::triggered, this, &Pineter::menuEVF);
			connect(ui_.actionHorizontal_Flip, &QAction::triggered, this, &Pineter::menuEHF);
			connect(ui_.actionRandom_Magenta, &QAction::triggered, this, &Pineter::menuERM);
			connect(ui_.actionChaos, &QAction::triggered, this, &Pineter::menuEC);
			connect(ui_.actionVertical_Mosaic, &QAction::triggered, this, &Pineter::menuEVM);
			connect(ui_.actionFull_Reverse, &QAction::triggered, this, &Pineter::menuEFR);

			//初始化

			image_ = nullptr;
			file_path_ = "";
			is_changed_ = false;
			ui_.stateLabel->setText("no pic");
			grayOutScreen();
			updateState();
		}

		void Pineter::updateState()
		{
			//没有打开的图片
			if (image_ == nullptr)
			{
				ui_.action_Open->setEnabled(true);
				ui_.action_Close->setEnabled(false);
				ui_.actionSave_as->setEnabled(false);
				ui_.action_Save->setEnabled(false);

				ui_.actionVertical_Flip->setEnabled(false);
				ui_.actionHorizontal_Flip->setEnabled(false);

				return;
			}

			//有打开的图片 没有保存过文件
			if (image_ != nullptr && file_path_ != "")
			{
				ui_.action_Open->setEnabled(true);
				ui_.action_Close->setEnabled(true);
				ui_.actionSave_as->setEnabled(true);
				ui_.action_Save->setEnabled(false);

				ui_.actionVertical_Flip->setEnabled(true);
				ui_.actionHorizontal_Flip->setEnabled(true);
				return;
			}

			//有打开的图片 有保存过文件
			if (image_ != nullptr && file_path_ != "")
			{
				ui_.action_Open->setEnabled(true);
				ui_.action_Close->setEnabled(true);
				ui_.actionSave_as->setEnabled(true);
				ui_.action_Save->setEnabled(true);

				ui_.actionVertical_Flip->setEnabled(true);
				ui_.actionHorizontal_Flip->setEnabled(true);
				return;
			}
		}

		void Pineter::refreshScreen()
		{
			if (image_ == nullptr) grayOutScreen();
			else
			{
				// 创建一个新的QImage对象
				QImage image(image_->width_, image_->height_, QImage::Format_RGB32);

				// 遍历你的图像数据，为每个像素设置r,g,b值
				for (int y = 0; y < image_->height_; ++y) {
					for (int x = 0; x < image_->width_; ++x) {
						image.setPixelColor(x, y, QColor(
							(*image_)(x, y)->r,
							(*image_)(x, y)->g,
							(*image_)(x, y)->b));
					}
				}

				// 创建一个QPixmap对象并用你的QImage对象来初始化它
				QPixmap pixmap = QPixmap::fromImage(image);

				// 使用QLabel来显示QPixmap对象
				ui_.imageLabel->setPixmap(pixmap);
				ui_.imageLabel->show();
			}

		}

		void Pineter::grayOutScreen()
		{
			QImage image(ui_.imageLabel->width(), ui_.imageLabel->height(), QImage::Format_RGB32);
			image.setColor(0, qRgb(100, 100, 100));
			QPixmap pixmap = QPixmap::fromImage(image);
			// 使用QLabel来显示QPixmap对象
			ui_.imageLabel->setPixmap(pixmap);
			ui_.imageLabel->show();
		}

		void Pineter::resizeEvent(QResizeEvent* event)
		{
			ui_.imageLabel->setGeometry(10, 10, this->width() - 20, this->height() - 50);
			ui_.stateLabel->setGeometry(10, this->height() - 40, this->width() - 10, 15);
			refreshScreen();
		}

		//
		//void Pineter::paintEvent(QPaintEvent* event)
		//{
		//	QPainter p(this);
		//	p.setPen(QColor(255, 0, 0));
		//	p.drawPoint(100, 200);
		//	p.drawLine(0, 0, 300, 400);
		//}
	}
}