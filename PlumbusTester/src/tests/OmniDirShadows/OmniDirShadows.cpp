#include "plumbus.h"
#include "tests/OmniDirShadows/OmniDirShadows.h"
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
#include "imgui_impl/ImGuiImpl.h"
#include "renderer/vk/DescriptorSet.h"
#include "renderer/vk/ShadowManager.h"
#include "renderer/vk/ShadowOmniDirectional.h"

namespace plumbus::tester::tests 
{
	OmniDirShadows::OmniDirShadows()
		: Test()
		, m_DeferredLightMaterial(new vk::Material("shaders/shader.vert", "shaders/shader.frag"))
	{
		m_DeferredLightMaterial->Setup();
	}

	OmniDirShadows::~OmniDirShadows()
	{
	}

	void OmniDirShadows::Init()
	{
		TesterScene* scene = static_cast<TesterScene*>(Application::Get().GetScene());

		if (Camera* camera = scene->GetCamera())
		{
			camera->SetPosition(glm::vec3(0.f, 11.f, -35.f));
			camera->SetRotation(glm::vec3(-10.f, 0.f, 0.0f));
		}

		GameObject* plane = new GameObject("plane");
		scene->AddGameObject(plane->
             AddComponent<components::ModelComponent>(new components::ModelComponent("models/plane.obj", "stonefloor_color", "stonefloor_normal"))->
             AddComponent<components::TranslationComponent>(new components::TranslationComponent())
		);
		plane->GetComponent<components::ModelComponent>()->SetMaterial(m_DeferredLightMaterial);

        GameObject* plane2 = new GameObject("plane2");
        scene->AddGameObject(plane2->
                AddComponent<components::ModelComponent>(new components::ModelComponent("models/plane.obj", "stonefloor_color", "stonefloor_normal"))->
                AddComponent<components::TranslationComponent>(new components::TranslationComponent())
        );
        plane2->GetComponent<components::ModelComponent>()->SetMaterial(m_DeferredLightMaterial);
        plane2->GetComponent<components::TranslationComponent>()->SetRotation(glm::vec3(0.f, 0.f, glm::half_pi<float>()));
        plane2->GetComponent<components::TranslationComponent>()->SetTranslation(glm::vec3(-10.f, -10.f, 0.f));

        GameObject* plane3 = new GameObject("plane3");
        scene->AddGameObject(plane3->
                AddComponent<components::ModelComponent>(new components::ModelComponent("models/plane.obj", "stonefloor_color", "stonefloor_normal"))->
                AddComponent<components::TranslationComponent>(new components::TranslationComponent())
        );
        plane3->GetComponent<components::ModelComponent>()->SetMaterial(m_DeferredLightMaterial);
        plane3->GetComponent<components::TranslationComponent>()->SetRotation(glm::vec3(0.f, 0.f, -glm::half_pi<float>()));
        plane3->GetComponent<components::TranslationComponent>()->SetTranslation(glm::vec3(10.f, -10.f, 0.f));

        GameObject* plane4 = new GameObject("plane4");
        scene->AddGameObject(plane4->
                AddComponent<components::ModelComponent>(new components::ModelComponent("models/plane.obj", "stonefloor_color", "stonefloor_normal"))->
                AddComponent<components::TranslationComponent>(new components::TranslationComponent())
        );
        plane4->GetComponent<components::ModelComponent>()->SetMaterial(m_DeferredLightMaterial);
        plane4->GetComponent<components::TranslationComponent>()->SetRotation(glm::vec3(-glm::half_pi<float>(), 0.f, 0.f));
        plane4->GetComponent<components::TranslationComponent>()->SetTranslation(glm::vec3(0.f, -10.f, -10.f));

		GameObject* knight = new GameObject("Knight");
		scene->AddGameObject(knight->
         AddComponent<components::ModelComponent>(new components::ModelComponent("models/armor.dae", "color", "normal"))->
         AddComponent<components::TranslationComponent>(new components::TranslationComponent())
		);
		knight->GetComponent<components::TranslationComponent>()->SetTranslation(glm::vec3(0.f, -2.4f, -4.f));
		knight->GetComponent<components::ModelComponent>()->SetMaterial(m_DeferredLightMaterial);

        GameObject* knight2 = new GameObject("Knight2");
        scene->AddGameObject(knight2->
                AddComponent<components::ModelComponent>(new components::ModelComponent("models/armor.dae", "color", "normal"))->
                AddComponent<components::TranslationComponent>(new components::TranslationComponent())
        );
        knight2->GetComponent<components::TranslationComponent>()->SetTranslation(glm::vec3(0.f, -2.4f, 4.f));
        knight2->GetComponent<components::TranslationComponent>()->SetRotation(glm::vec3(0.f, -glm::pi<float>(), 0.f));
        knight2->GetComponent<components::ModelComponent>()->SetMaterial(m_DeferredLightMaterial);

        GameObject* knight3 = new GameObject("Knight3");
        scene->AddGameObject(knight3->
                AddComponent<components::ModelComponent>(new components::ModelComponent("models/armor.dae", "color", "normal"))->
                AddComponent<components::TranslationComponent>(new components::TranslationComponent())
        );
        knight3->GetComponent<components::TranslationComponent>()->SetTranslation(glm::vec3(-4.f, -2.4f, 0.f));
        knight3->GetComponent<components::TranslationComponent>()->SetRotation(glm::vec3(0.f, glm::half_pi<float>(), 0.f));
        knight3->GetComponent<components::ModelComponent>()->SetMaterial(m_DeferredLightMaterial);

        GameObject* knight4 = new GameObject("Knight4");
        scene->AddGameObject(knight4->
                AddComponent<components::ModelComponent>(new components::ModelComponent("models/armor.dae", "color", "normal"))->
                AddComponent<components::TranslationComponent>(new components::TranslationComponent())
        );
        knight4->GetComponent<components::TranslationComponent>()->SetTranslation(glm::vec3(4.f, -2.4f, 0.f));
        knight4->GetComponent<components::TranslationComponent>()->SetRotation(glm::vec3(0.f, -glm::half_pi<float>(), 0.f));
        knight4->GetComponent<components::ModelComponent>()->SetMaterial(m_DeferredLightMaterial);

        GameObject* light = new GameObject("Light");
        scene->AddGameObject(light->
            AddComponent<components::LightComponent>(new components::LightComponent())->
            AddComponent<components::ModelComponent>(new components::ModelComponent("models/sphere.obj", "stonefloor_color", "stonefloor_normal"))->
            AddComponent<components::TranslationComponent>(new components::TranslationComponent())
		);

        light->GetComponent<components::LightComponent>()->AddPointLight(glm::vec3(1.0f, 1.f, 1.f), 100.f, true);
        light->GetComponent<components::TranslationComponent>()->SetTranslation(glm::vec3(0.f, -2.f, 0.f));
        light->GetComponent<components::TranslationComponent>()->SetScale(glm::vec3(0.1f, 0.1f, 0.1f));
        light->GetComponent<components::ModelComponent>()->SetMaterial(m_DeferredLightMaterial);

		BaseApplication::Get().GetScene()->LoadAssets();
	}

	void OmniDirShadows::Update()
	{
#if ENABLE_IMGUI
        std::vector<vk::ShadowOmniDirectional*>& OmniDirShadows = vk::ShadowManager::Get()->GetOmniDirectionalShadows();
		if (m_ShadowTextureImGui.size() != OmniDirShadows.size())
		{
		    m_ShadowTextureImGui.clear();
			if (OmniDirShadows.size() > 0)
			{
			    for (const vk::ShadowOmniDirectional* shadow : OmniDirShadows)
			    {
                    vk::VulkanRenderer *vkRenderer = vk::VulkanRenderer::Get();
                    m_ShadowTextureImGui.push_back(vkRenderer->GetImGui()->CreateImGuiTextureMaterialInstance(
                            shadow->GetCubeMap().m_TextureSampler,
                            shadow->GetCubeMap().m_ImageView, vk::TextureType::R32Cube));
                }
			}
		}
#endif
	}

	void OmniDirShadows::Shutdown()
	{
		vkDeviceWaitIdle(vk::VulkanRenderer::Get()->GetDevice()->GetVulkanDevice());
		for (GameObject* obj : BaseApplication::Get().GetScene()->GetObjects())
		{
			if (components::ModelComponent* component = obj->GetComponent<components::ModelComponent>())
			{
				component->Cleanup();
			}
		}

		BaseApplication::Get().GetScene()->ClearObjects();

		m_DeferredLightMaterial.reset();
        m_ShadowTextureImGui.clear();
	}

	void OmniDirShadows::OnGui()
	{
		ImGui::Text("OmniDirShadows");

#if !PL_DIST
		for (vk::MaterialInstanceRef shadowMaterial : m_ShadowTextureImGui)
		{
            ImGui::Image(shadowMaterial.get(), ImVec2(400, 225), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1),
                         ImVec4(0, 0, 0, 0));
        }
#endif
		
	}

}
