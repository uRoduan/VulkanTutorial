#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <memory>

#include "DeviceObjectBase.h"

class ImageView: public DeviceObjectBase<ImageView>
{
public:
	static std::shared_ptr<ImageView> Create(const std::shared_ptr<Device>& pDevice, const VkImageViewCreateInfo& createInfo);

public:
	bool Init(const std::shared_ptr<Device>& pDevice, const std::shared_ptr<ImageView>& pSelf, const VkImageViewCreateInfo& createInfo);

	VkImageView GetImageView() const { return m_imageView; }

	~ImageView();

private:
	VkImageView m_imageView;
};