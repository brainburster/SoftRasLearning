#pragma once

#include "light.hpp"
#include "billboard.hpp"

namespace framework
{
	class DirectionalLight : public Object, public ILight
	{
	public:
		Vec3 color;
	public:
		virtual ELightType GetLightType() override
		{
			return ELightType::DirectionalLight;
		}
		virtual Vec3 GetColor() override
		{
			return color;
		}
		virtual Vec3 GetPosition() override
		{
			return transform.position;
		}
		virtual Vec3 GetDirection() override
		{
			using namespace gmath::utility;
			return Rotate(transform.rotation) * Vec4 { 0, 0, -1.f, 0 };
		}
		virtual float GetCutOff() override
		{
			return 0.f;
		}
		virtual Mat4 GetLightMartrix() override
		{
			using namespace gmath::utility;
			Vec3 front = GetDirection();
			Vec3 right = front.cross({ 0,1,0 });
			Vec3 up = right.cross(front);
			return Ortho(-10.f, 10.f, -10.f, 10.f, 0.1f, 1000.f) * View(transform.position, front, up);
		}
		virtual void Render(IRenderEngine& engine) const override
		{
			//...
			//�����
			//
			BillBord bb;
			bb.transform.position = transform.position;
			bb.transform.rotation = { 0 };
			bb.transform.scale = { 0.5f,0.5f,1.f };
			auto tex = Resource<core::Texture>::Get(L"sunlight");
			if (tex.has_value())
			{
				bb.tex0 = tex.value();
			}

			bb.Render(engine);
		}
	};
};
