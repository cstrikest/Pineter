#include "Pineter.h"

using Pineter::PImageFunctions::operator>>;

namespace Pineter
{
	namespace Program
	{
		//打开文件菜单
		void Pineter::menuOpen()
		{
			QMessageBox msgBox;
			msgBox.setWindowTitle("Save your image?");
			msgBox.setText("Changes didn't saved.\nDo you want to save your image?");
			msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
			msgBox.setDefaultButton(QMessageBox::Save);
			//有打开的图片 没有保存过的文件
			if (image_ != nullptr && file_path_ == "")
			{
				if (msgBox.exec() == QMessageBox::Save) imageSaveAs();
			}
			//有打开的图片 有保存过的文件 有新改动
			else if (is_changed_ == true)
			{
				if (msgBox.exec() == QMessageBox::Save) imageSave();
			}
			msgBox.close();
			imageOpen();
			refreshScreen();
			updateState();
			return;
		}

		//保存文件菜单
		void Pineter::menuSave()
		{
			//新图片 没有保存过的文件
			if (file_path_ == "")
			{
				imageSaveAs();
			}
			//有图片 有保存过的文件
			else
			{
				imageSave();
			}
			updateState();
			return;
		}

		//另存为菜单
		void Pineter::menuSaveAs()
		{
			imageSaveAs();
			updateState();
			return;
		}

		//关闭文件菜单
		void Pineter::menuClose()
		{
			//未保存的更改
			if (is_changed_)
			{
				QMessageBox msgBox;
				msgBox.setWindowTitle("Save your image?");
				msgBox.setText("Changes didn't saved.\nDo you want to save your image?");
				msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
				msgBox.setDefaultButton(QMessageBox::Save);
				if (msgBox.exec() == QMessageBox::Save)
				{
					if (file_path_ == "") imageSaveAs();
					else imageSave();
				}
				msgBox.close();
			}
			imageClose();
			updateState();
			refreshScreen();
			return;
		}

		//退出菜单
		void Pineter::menuQuit()
		{
			if (is_changed_)
			{
				QMessageBox msgBox;
				msgBox.setWindowTitle("Save your image?");
				msgBox.setText("Changes didn't saved.\nDo you want to save your image?");
				msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
				msgBox.setDefaultButton(QMessageBox::Save);
				if (msgBox.exec() == QMessageBox::Save)
				{
					if (file_path_ == "") imageSaveAs();
					else imageSave();
				}
				msgBox.close();
			}
			imageClose();
			this->close();
		}

		//打开文件函数
		void Pineter::imageOpen()
		{
			//打开文件对话框
			QFileDialog dlg(this, "Open a Bitmap file.", DEFAULT_WORK_PATH, "Bitmap Files (*.bmp)");
			while (dlg.exec())
			{
				try
				{
					//从文件创建Bmp对象
					file_path_ = dlg.selectedFiles().first();
					PImageFileFormat::Bmp bmp_reader(file_path_.toLatin1().data());
					//从BmpBinary转换到LinearRGB24bit对象
					image_ = bmp_reader.toLinearRgb24b();
					ui_.stateLabel->setText("opened");
					//image_ = PImageFunctions::resizeBilinear(image_, 400,300);
					break;
				}
				catch (std::exception& e)
				{
					QMessageBox::warning
					(
						this,
						"Failed to load",
						QString::fromStdString("Failed to load image file.\n") +
						dlg.selectedFiles().first() + "\n" + QString::fromStdString(e.what()),
						QMessageBox::Ok
					);
					dlg.close();
					return;
				}
			}
			dlg.close();
		}

		//保存文件函数
		void Pineter::imageSave()
		{
			try
			{
				PImageFileFormat::Bmp(*image_).save(file_path_.toLatin1().data());
			}
			catch (std::exception& e)
			{
				QMessageBox::warning
				(
					this,
					"Failed to save",
					QString::fromStdString("Failed to save.\n") +
					file_path_ + QString::fromStdString(e.what()),
					QMessageBox::Ok
				);
				return;
			}
		}

		//另存为函数
		void Pineter::imageSaveAs()
		{
			QFileDialog dlg(this, "Save as...", DEFAULT_WORK_PATH, "Bitmap Files (*.bmp)");
			dlg.setFileMode(QFileDialog::AnyFile);
			while (dlg.exec())
			{
				try
				{
					file_path_ = dlg.selectedFiles().first();
					PImageFileFormat::Bmp T(*image_);
					T.save(file_path_.toLatin1().data());
					break;
				}
				catch (std::exception& e)
				{
					int ret = QMessageBox::warning
					(
						this,
						"Failed to save",
						QString::fromStdString("Failed to save to\n") +
						dlg.selectedFiles().first() + "\n" + QString::fromStdString(e.what()),
						QMessageBox::Ok
					);
					dlg.close();
					return;
				}
			}
			dlg.close();
		}

		//关闭图片函数
		void Pineter::imageClose()
		{
			delete image_;
			image_ = nullptr;
			file_path_ = "";
			ui_.stateLabel->setText("no pic");
		}

		//各个图像处理函数的菜单项目
		void Pineter::menuEVF()
		{
			*image_ >> PImageFunctions::verticalFlip;
			refreshScreen();
		}

		void Pineter::menuEHF()
		{
			*image_ >> PImageFunctions::horizontalFlip;
			refreshScreen();
		}

		void Pineter::menuERM()
		{
			*image_ >> PImageFunctions::randMagenta;
			refreshScreen();
		}

		void Pineter::menuEC()
		{
			*image_ >> PImageFunctions::chaos;
			refreshScreen();
		}

		void Pineter::menuEVM()
		{
			*image_ >> PImageFunctions::verticalMosaic;
			refreshScreen();
		}

		void Pineter::menuEFR()
		{
			*image_ >> PImageFunctions::fullReverse;
			refreshScreen();
		}

		//关于Pineapple
		void Pineter::menuPineapple()
		{
			QMessageBox msgBox;
			msgBox.setWindowTitle("About author");
			msgBox.setIconPixmap(QPixmap("./image/Pineter_128.png"));
			msgBox.setText("\n\n\nCreated by pineapple(cstrikest)\n"
				"github: cstrikest/Pineter\n"
				"For learning c++ & Qt6.5.\n"
				"Programming for fun :)");
			msgBox.setStandardButtons(QMessageBox::Ok);
			msgBox.exec();
			msgBox.close();
		}

		//更新程序状态
		// - 可用菜单项
		// - 
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

		//刷新图片显示区域内容
		void Pineter::refreshScreen()
		{
			//如果没有图像 全刷灰
			if (image_ == nullptr) grayOutScreen();
			else
			{
				// 创建一个新的QImage对象
				QImage image(image_->width_, image_->height_, QImage::Format_RGB32);

				//如果有图像 判断大小
				//图像比绘图区小，刷灰边缘
				if (image.width() < ui_.imageLabel->width() or image.height() < ui_.imageLabel->height())
					image.setColor(0, QRGB_COLOR_DEFALUT_GARY);
				// 遍历你的图像数据，为每个像素设置r,g,b值
				for (int y = 0; y < image_->height_; ++y) {
					for (int x = 0; x < image_->width_; ++x) {
						image.setPixelColor(x, y, QColor(
							(*image_)(x, y).r,
							(*image_)(x, y).g,
							(*image_)(x, y).b));
					}
				}
				// 创建一个QPixmap对象并用你的QImage对象来初始化它
				QPixmap pixmap = QPixmap::fromImage(image);

				// 使用QLabel来显示QPixmap对象
				ui_.imageLabel->setPixmap(pixmap);
				ui_.imageLabel->show();

				image.detach();
				pixmap.detach();
			}
		}

		//全部刷灰图片显示区
		void Pineter::grayOutScreen()
		{
			QImage image(ui_.imageLabel->width(), ui_.imageLabel->height(), QImage::Format_RGB32);
			image.setColor(0, QRGB_COLOR_DEFALUT_GARY);
			QPixmap pixmap = QPixmap::fromImage(image);
			// 使用QLabel来显示QPixmap对象
			ui_.imageLabel->setPixmap(pixmap);
			ui_.imageLabel->show();
		}

		//窗口大小变化事件
		void Pineter::resizeEvent(QResizeEvent* event)
		{
			ui_.imageLabel->setGeometry(10, 10, this->width() - 20, this->height() - 50);
			ui_.stateLabel->setGeometry(10, this->height() - 40, this->width() - 10, 15);
			refreshScreen();
		}
	}
}