#pragma once
#include <assert.h>
#include <iostream>

#define CALL_VK(vkExpress) { \
	VkResult result = vkExpress; \
	if(result != VK_SUCCESS)    \
    {                        \
        throw std::runtime_error(std::string(#vkExpress) + " failed");\
    }\
	}

#define RETUEN_RESULT_CALL_VK() 

namespace VkUtility
{

}