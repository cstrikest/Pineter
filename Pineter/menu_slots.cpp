#include "Pineter.h"
namespace Pineter
{
	namespace Program
	{
		void Pineter::fileOpen()
		{


			//打开文件对话框
			QFileDialog dlg(this, "Open a Bitmap file.", "c:\\", "Bitmap Files (*.bmp)");
			while (dlg.exec())
			{
				try
				{
					//从文件创建Bmp对象
					PImageFileFormat::Bmp bmp_reader(dlg.selectedFiles().first().toLatin1().data());
					//从BmpBinary转换到LinearRGB24bit对象
					image_ = bmp_reader.toLinearRgb24b();
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
					return;
				}

			}
		}

		void Pineter::fileSave()
		{
			try
			{
				//有图片，没有加载文件 另存为
				if (file_path_ == "")
				{
					fileSaveAs();
				}
				//无图片 报错
				else if (image_ == nullptr)
				{
					throw PException::NoActiveImageFoundException();
				}
				//有图片，有文件 保存
				else
				{
					PImageFileFormat::Bmp(*image_).save(file_path_.toLatin1().data());
				}
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

		void Pineter::fileSaveAs()
		{
			try
			{
				if (image_ == nullptr) throw PException::NoActiveImageFoundException();
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
			QFileDialog dlg(this, "Save as...", "c:\\", "Bitmap Files (*.bmp)");
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
					QMessageBox::warning
					(
						this,
						"Failed to save",
						QString::fromStdString("Failed to save to\n") +
						dlg.selectedFiles().first() + "\n" + QString::fromStdString(e.what()),
						QMessageBox::Ok
					);
					return;
				}
			}
		}

		void Pineter::fileClose()
		{
			delete image_;
		}

		//void Pineter::fileClose();
		//void Pineter::fileQuit();
		//
		////Edit 自动生成项
		//void Pineter::edit(const char* editFunc);
		//
		////About
		//void Pineter::aboutPineapple();
	}
}