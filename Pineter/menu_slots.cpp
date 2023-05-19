#include "Pineter.h"

void Pineter::fileOpen()
{
	QFileDialog dlg(this, "Open a Bitmap file.", "c:\\", "Bitmap Files (*.bmp)");
	while (dlg.exec())
	{
		try
		{
			file_path_ = dlg.selectedFiles().first();
			ip_ = new IP(file_path_);
			this->setWindowTitle(file_path_);
			break;
		}
		catch (std::exception& e)
		{
			ip_ = nullptr;
			delete ip_;
			file_path_ = "";
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
		if (file_path_ == "") fileSaveAs();
		//无图片 报错
		else if (ip_ == nullptr) throw NoActiveImageFoundException();
		//有图片，有文件 保存
		else
		{
			//Bmp(BM, *ip_->image_).save(file_path_.toStdString().c_str());
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
	if (ip_ == nullptr) throw NoActiveImageFoundException();
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
			Bmp T(*ip_->image_);
			T.save(file_path_.toStdString().c_str());
			ui_.label->setText(QString::number(ip_->image_->getPixelNum()));
			this->setWindowTitle(file_path_);
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
//void Pineter::fileClose();
//void Pineter::fileQuit();
//
////Edit 自动生成项
//void Pineter::edit(const char* editFunc);
//
////About
//void Pineter::aboutPineapple();