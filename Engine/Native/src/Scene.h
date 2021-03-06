#pragma once
#include "plumbus.h"
#include "Camera.h"

namespace plumbus
{
	class GameObject;

	class Scene
	{
	public:
		virtual void Init();
		virtual void Shutdown();
		virtual void OnUpdate();

		virtual bool IsInitialised();

		Camera* GetCamera() { return &m_Camera; }

		void AddGameObject(GameObject* obj);
		std::vector<GameObject*>& GetObjects() { return m_GameObjects; }
		void ClearObjects();

		void LoadAssets();

	protected:
		Scene();

	private:
		Camera m_Camera;
		std::vector<GameObject*> m_GameObjects;

		bool m_Initialised;
	};
}