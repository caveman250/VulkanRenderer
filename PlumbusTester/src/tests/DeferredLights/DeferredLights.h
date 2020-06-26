#pragma once

#include "tests/Test.h"
#include "renderer/base/renderer_fwd.h"

namespace plumbus
{
	namespace base
	{
		class Material;
	}

	namespace tester::tests
	{
		class DeferredLights : public Test
		{
		public:
			DeferredLights();
			~DeferredLights();
			void Init() override;
			void Update() override;
			void Shutdown() override;
			void OnGui() override;
		private:
			double m_LightTime;
			bool m_LightsPaused;
			float m_LightSpeed;
			float m_LightsDistanceFromCenter;

			MaterialRef m_DeferredLightMaterial;
		};
	}
}
