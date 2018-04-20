#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vector>
#include <array>
#include <glm/glm.hpp>
#include "Scene.h"

#include "vk/Model.h"
#include "vk/Device.h"
#include "vk/FrameBuffer.h"

class Scene;
namespace vk
{
	class Model;
}
class Application
{
private:

	struct SwapChainSupportDetails 
	{
		VkSurfaceCapabilitiesKHR m_Capabilities;
		std::vector<VkSurfaceFormatKHR> m_Formats;
		std::vector<VkPresentModeKHR> m_PresentModes;
	};

	struct VertexDescription
	{
		VkPipelineVertexInputStateCreateInfo m_InputState;
		std::vector<VkVertexInputBindingDescription> m_BindingDescriptions;
		std::vector<VkVertexInputAttributeDescription> m_AttributeDescriptions;
	};

	struct UniformBuffers
	{
		vk::Buffer m_VertFullScreen;
		vk::Buffer m_FragLights;
	};

	struct UniformBufferVert
	{
		glm::mat4 m_Projection;
		glm::mat4 m_Model;
		glm::mat4 m_View;
		glm::vec4 m_InstancePos[3];
	};

	struct LightBufferInfo 
	{
		glm::vec4 m_Position;
		glm::vec3 m_Colour;
		float m_Radius;
	};

	static const size_t MAX_LIGHTS = 50;
	struct UniformBufferLights
	{
		LightBufferInfo m_Lights[MAX_LIGHTS];
		glm::vec4 m_ViewPos;
	};

	struct PipelineLayouts
	{
		VkPipelineLayout m_Deferred;
		VkPipelineLayout m_Offscreen;
	};

	struct Pipelines 
	{
		VkPipeline m_Deferred;
		VkPipeline m_Offscreen;
		VkPipeline m_Debug;
	};

public:
	Application();

	static void CreateInstance() { m_Instance = new Application(); }
	static Application& Get() { return *m_Instance; }
	void Run();

	vk::VulkanDevice* GetVulkanDevice() { return m_VulkanDevice; }
	VkDescriptorPool& GetDescriptorPool() { return m_DescriptorPool; }
	VkExtent2D& GetSwapChainExtent() { return m_SwapChainExtent; }
	VkDescriptorSetLayout& GetDescriptorSetLayout() { return m_DescriptorSetLayout; }
	GLFWwindow* GetWindow() { return m_Window; }
	double GetDeltaTime() { return m_DeltaTime; }

	double m_LightTime = 0;

	VkFormat FindDepthFormat();

private:
	void InitWindow();
	void InitScene();
	void InitVulkan();
	void CreateVulkanInstance();
	void SetupDebugCallback();
	void PickPhysicalDevice();
	bool IsDeviceSuitable(VkPhysicalDevice device);
	bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
	void CreateSurface();
	void CreatePipelineCache();
	void GenerateQuads();
	void CreateVertexDescriptions();
	void CreateUniformBuffers();
	void InitLightsVBO();
	void CreateDescriptorSetLayout();
	void CreatePipelines();
	void CreateDescriptorPool();
	void CreateDescriptorSet();
	void BuildCommandBuffers();
	void BuildDefferedCommandBuffer();
	void CreateSwapChain();
	void RecreateSwapChain();
	void CleanupSwapChain();
	void CreateImageViews();
	void CreateRenderPass();
	void UpdateUniformBuffersScreen();
	void UpdateUniformBufferDeferredLights();
	void CreateDepthResources();
	void CreateFrameBuffers();
	void CreateCommandBuffers();
	void CreateSemaphores();

	void MainLoop();
	void UpdateScene();
	void DrawFrame();
	void Cleanup();
	static void OnWindowResized(GLFWwindow* window, int width, int height);

	std::vector<const char*> GetRequiredExtensions();
	bool CheckValidationLayerSupport();

	VkFormat FindSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	
	SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	VkShaderModule CreateShaderModule(const std::vector<char>& code);
	VkPipelineShaderStageCreateInfo LoadShader(std::string fileName, VkShaderStageFlagBits stage);

	GLFWwindow* m_Window;
	VkInstance m_VulkanInstance;
	VkDebugReportCallbackEXT m_Callback;
	vk::VulkanDevice* m_VulkanDevice;
	VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
	VkQueue m_GraphicsQueue;
	VkSurfaceKHR m_Surface;
	VkQueue m_PresentQueue;
	VkSwapchainKHR m_SwapChain;
	std::vector<VkImage> m_SwapChainImages;
	VkFormat m_SwapChainImageFormat;
	VkExtent2D m_SwapChainExtent;
	std::vector<VkImageView> m_SwapChainImageViews;
	VkRenderPass m_RenderPass;
	VkDescriptorPool m_DescriptorPool;
	VkDescriptorSetLayout m_DescriptorSetLayout;
	VkDescriptorSet m_DescriptorSet;
	PipelineLayouts m_PipelineLayouts;
	Pipelines m_Pipelines;
	std::vector<VkFramebuffer> m_Framebuffers;
	std::vector<VkCommandBuffer> m_CommandBuffers;
	VkSemaphore m_ImageAvailableSemaphore;
	VkSemaphore m_RenderFinishedSemaphore;
	VkSemaphore m_OffscreenSemaphore;
	VertexDescription m_VertexDescriptions;
	vk::FrameBuffer* m_OffscreenFrameBuffer;
	UniformBuffers m_UniformBuffers;
	UniformBufferVert m_VertUBO;
	UniformBufferLights m_LightsUBO;
	VkPipelineCache m_PipelineCache;
	VkCommandBuffer m_OffScreenCmdBuffer = VK_NULL_HANDLE;
	VkImage m_DepthImage;
	VkDeviceMemory m_DepthImageMemory;
	VkImageView m_DepthImageView;
	vk::Model m_Quad;
	std::vector<VkShaderModule> m_ShaderModules;

	static Application* m_Instance;
	Scene* m_Scene;
	double m_DeltaTime = 0;
	double m_lastUpdateTime;

};