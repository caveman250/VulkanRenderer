#pragma once

#include "plumbus.h"
#include "mono_impl/mono_fwd.h"

namespace plumbus::vk
{
	class VulkanRenderer;
}

namespace plumbus
{
	class Scene;
	class BaseApplication
	{
	public:
		BaseApplication();

		static void CreateInstance() { PL_ASSERT(false); /*create your own application class.*/ }
		static BaseApplication& Get() { return *s_Instance; }
		void Run();
		double GetDeltaTime() { return m_DeltaTime; }

		template <typename T>
		void CreateScene();
		void SetScene(Scene* scene);

		Scene* GetScene() { return m_Scene; }
		vk::VulkanRenderer* GetRenderer() { return m_Renderer; }
		void MainLoop();
		virtual void Cleanup();

		virtual void OnGui();

		void SetAppName(std::string name) { m_AppName = name; }

		bool m_GameWindowFocused = false;

	protected:
		void InitScene();
		void UpdateScene();
		bool IsValidToReplaceCurrentScene();

		static BaseApplication* s_Instance;
		Scene* m_Scene;
		double m_DeltaTime = 0;
		double m_LastUpdateTime;

		vk::VulkanRenderer* m_Renderer;
		std::string m_AppName;
	};

	template <typename T>
	void BaseApplication::CreateScene()
	{
		PL_ASSERT(IsValidToReplaceCurrentScene());
		m_Scene = new T();
	}
}

MONO_EXPORT(double) Application_GetDeltaTime();
