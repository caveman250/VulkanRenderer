#include "plumbus.h"
#include "tests/SponzaScene/SponzaScene.h"
#include "BaseApplication.h"
#include "renderer/vk/Window.h"
#include "components/ModelComponent.h"
#include "components/TranslationComponent.h"
#include "components/LightComponent.h"
#include "GameObject.h"

#include "Application.h"
#include "TesterScene.h"
#include "renderer/vk/Material.h"
#include "renderer/vk/VulkanRenderer.h"



namespace plumbus::tester::tests 
{
	
	SponzaScene::SponzaScene()
		: Test()
		, m_DeferredLightMaterial(new vk::Material("shaders/shader.vert", "shaders/shader.frag"))
	{
		 m_DeferredLightMaterial->Setup();
	}

	SponzaScene::~SponzaScene()
	{
	}

	void SponzaScene::Init()
	{
		TesterScene* scene = static_cast<TesterScene*>(Application::Get().GetScene());

		GameObject* sponza = new GameObject("Sponza");
		scene->AddGameObject(sponza->
			AddComponent<ModelComponent>(new ModelComponent("models/sponza.dae", "color", "normal"))->
			AddComponent<TranslationComponent>(new TranslationComponent())
		);

		sponza->GetComponent<ModelComponent>()->SetMaterial(m_DeferredLightMaterial);

        //light
        GameObject* light = new GameObject("Directional Light");
        scene->AddGameObject(light->
				AddComponent<TranslationComponent>(new TranslationComponent())->
				AddComponent<LightComponent>(new LightComponent()));

        light->GetComponent<LightComponent>()->AddDirectionalLight(glm::vec3(1.f, 1.f, 1.f), glm::vec3(-0.3f, 1.f, 0.3), false);

		BaseApplication::Get().GetScene()->LoadAssets();
	}

	void SponzaScene::Update()
	{
		
	}

	void SponzaScene::Shutdown()
	{
		for (GameObject* obj : BaseApplication::Get().GetScene()->GetObjects())
		{
			if (ModelComponent* component = obj->GetComponent<ModelComponent>())
			{
				component->Cleanup();
			}
		}

		BaseApplication::Get().GetScene()->ClearObjects();

		m_DeferredLightMaterial.reset();
	}

	void SponzaScene::OnGui()
	{
		ImGui::Text("Sponza Scene");
	}

}