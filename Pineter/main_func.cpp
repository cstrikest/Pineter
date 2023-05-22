#include "Pineter.h"

using Pineter::PImageFunctions::operator>>;

namespace Pineter
{
	namespace Program
	{
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
			refreshImage();
			updateState();
			return;
		}

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

		void Pineter::menuSaveAs()
		{
			imageSaveAs();
			updateState();
			return;
		}

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
			return;
		}

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
		//void Pineter::menuClose();
		//void Pineter::fileQuit();
		//
		////Edit 自动生成项
		//void Pineter::edit(const char* editFunc);
		//
		////About
		//void Pineter::aboutPineapple();

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
					ui_.stateLabel->setText("opened.");
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

		void Pineter::imageClose()
		{
			delete image_;
			image_ = nullptr;
			file_path_ = "";
			ui_.stateLabel->setText("no pic");
		}

		void Pineter::menuEVF()
		{
			*image_ >> PImageFunctions::verticalFlip;
			refreshImage();
		}

		void Pineter::menuEHF()
		{
			*image_ >> PImageFunctions::horizontalFlip;
			refreshImage();
		}
		void Pineter::menuERM()
		{
			*image_ >> PImageFunctions::randMagenta;
			refreshImage();
		}
		void Pineter::menuEC()
		{
			*image_ >> PImageFunctions::chaos;
			refreshImage();
		}

		void Pineter::menuEVM()
		{
			*image_ >> PImageFunctions::verticalMosaic;
			refreshImage();
		}
		void Pineter::menuEFR()
		{
			*image_ >> PImageFunctions::fullReverse;
			refreshImage();
		}

	}
}