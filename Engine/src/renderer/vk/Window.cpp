#include "plumbus.h"

#include "renderer/vk/Window.h"
#include "imgui_impl/Log.h"
#include "VulkanRenderer.h"
#include "Instance.h"

namespace plumbus::vk
{
	void Window::Init(uint32_t& width, uint32_t& height, std::string name)
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		GLFWmonitor* monitor =  glfwGetPrimaryMonitor();
   		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		width = (uint32_t)(mode->width * 0.5f);
		height = (uint32_t)(mode->height * 0.5f);

		m_Window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

		glfwSetWindowUserPointer(m_Window, this);
	}

	void Window::CreateSurface()
	{
		if (glfwCreateWindowSurface(VulkanRenderer::Get()->GetInstance()->GetVulkanInstance(), m_Window, nullptr, &m_Surface) != VK_SUCCESS)
		{
			Log::Fatal("failed to create window surface!");
		}
	}

	void Window::Destroy()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	glm::vec2 Window::GetMousePos()
	{
		double xpos, ypos;
		glfwGetCursorPos(m_Window, &xpos, &ypos);

		return glm::vec2(xpos, ypos);
	}

	uint32_t Window::GetWidth()
	{
		int width;
		glfwGetWindowSize(m_Window, &width, nullptr);
		return width;
	}

	uint32_t Window::GetHeight()
	{
		int height;
		glfwGetWindowSize(m_Window, nullptr, &height);
		return height;
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_Window);
	}

	bool Window::IsKeyDown(const int key)
	{
		return glfwGetKey(GetWindow(), key);
	}

}

