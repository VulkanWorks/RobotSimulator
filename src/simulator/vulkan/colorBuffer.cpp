//--------------------------------------------------
// Robot Simulator
// colorBuffer.cpp
// Date: 09/07/2020
// By Breno Cunha Queiroz
//--------------------------------------------------
#include "colorBuffer.h"

ColorBuffer::ColorBuffer(Device* device, SwapChain* swapChain, VkExtent2D extent):
	_extent(extent)
{
	_device = device;
	_swapChain = swapChain;

	_image = new Image(_device, _extent.width, _extent.height, _swapChain->getImageFormat()
			, VK_IMAGE_TILING_OPTIMAL
			, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
			, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT
			, 1, device->getMsaaSamples());
	_imageView = new ImageView(_device, _image->handle(), _swapChain->getImageFormat(), VK_IMAGE_ASPECT_COLOR_BIT);
}

ColorBuffer::~ColorBuffer()
{
	if(_image != nullptr)
	{
		delete _image;
		_image = nullptr;
	}

	if(_imageView != nullptr)
	{
		delete _imageView;
		_imageView = nullptr;
	}
}
