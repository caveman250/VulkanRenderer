#pragma once
#include "plumbus.h"

namespace plumbus::vk
{
	class Window
	{
	public:
		Window() {}
		~Window() {}

		void Init(uint32_t& width, uint32_t& height, std::string name);
		void CreateSurface();
		void Destroy();

		uint32_t GetWidth();
		uint32_t GetHeight();
		bool ShouldClose();

#if !PL_PLATFORM_ANDROID
		GLFWwindow* GetWindow() { return m_Window; }
#endif
		VkSurfaceKHR GetSurface() { return m_Surface; }
        
        float GetContentScaleX() { return m_ContentScaleX; }
        float GetContentScaleY() { return m_ContentScaleY; }

	private:
#if !PL_PLATFORM_ANDROID
		GLFWwindow* m_Window;
#endif
		VkSurfaceKHR m_Surface;
        
        float m_ContentScaleX;
        float m_ContentScaleY;
	};
}
