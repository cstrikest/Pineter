#include "Pineter.h"

using Pineter::PImageFunctions::operator>>;

namespace Pineter
{
	namespace Program
	{
		void Pineter::wheelEvent(QWheelEvent* event)
		{
			// 当滚轮向上滑，远离使用者
			if (event->angleDelta().y() > 0)
			{
				image_ = PImageFunctions::resizeBilinear(image_, (int)(image_->width_ * 1.2), (int)(image_->height_ * 1.2));
			}
			// 当滚轮向下滑，靠近使用者
			else if (event->angleDelta().y() < 0 && image_->width_ > 10 && image_->height_ > 10)
			{
				image_ = PImageFunctions::resizeBilinear(image_, (int)(image_->width_ * 0.8), (int)(image_->height_ * 0.8));
			}
			refreshScreen();
			event->accept();
		}
	}
}