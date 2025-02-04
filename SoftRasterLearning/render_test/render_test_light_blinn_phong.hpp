﻿#pragma once

#include "../core/core_api.hpp"
#include "../framework/framework.hpp"
#include "vs_out_type.hpp"


//世界空间 blinn_phong 着色器
class ShaderBlinnPhong
{
public:
	core::Mat mvp = {};
	core::Mat m = {};
	core::Texture* tex0 = nullptr;
	core::Vec3 light_position_ws = { 0,10,0 };
	core::Vec3 light_color = { 2,2,2 };
	core::Vec3 camera_position_ws = { 0,0,5 };

	VsOut_Light_ws VS(const core::Model_Vertex& v) const
	{
		VsOut_Light_ws vs_out{};
		vs_out.position = mvp * v.position.ToHomoCoord();
		vs_out.position_ws = m * v.position.ToHomoCoord();
		vs_out.uv = v.uv;
		vs_out.normal_ws = (m.ToMat3x3() * v.normal).Normalize();
		return vs_out;
	}

	core::Vec4 FS(const VsOut_Light_ws& v) const
	{
		using namespace core;
		Vec3 L = (light_position_ws - v.position_ws).Normalize();
		Vec3 V = (camera_position_ws - v.position_ws).Normalize();
		Vec3 H = (L + V).Normalize();
		Vec3 N = v.normal_ws.Normalize();
		Vec3 base_color = Texture::Sample(tex0, v.uv);
		Vec3 Ks = Vec3(0.3f, 0.3f, 0.3f);
		Vec3 ambient = Vec3(0.01f, 0.012f, 0.01f);

		Vec3 diffuse = base_color * light_color * max(N.Dot(L), 0);
		Vec3 specular = Ks * light_color * pow(max(N.Dot(H), 0), 16.f);
		Vec3 color = ambient + diffuse / pi + ((16 + 8) / (8 * pi)) * specular;

		return Vec4{ color, 1.f };
	}
};

class MaterialBlinnPhong : public framework::IMaterial
{
public:
	std::shared_ptr<core::Texture> tex0;
	std::shared_ptr<framework::ILight> light;

	void Render(const framework::Entity& entity, framework::IRenderEngine& engine) override
	{
		ShaderBlinnPhong shader{};
		core::Renderer<ShaderBlinnPhong> renderer = { engine.GetCtx(), shader };
		shader.tex0 = tex0.get();
		shader.mvp = engine.GetMainCamera()->GetProjectionViewMatrix() * entity.transform.GetModelMatrix();
		shader.m = entity.transform.GetModelMatrix();
		shader.light_position_ws = light->GetPosition();//core::Vec3{ -1.f,2.f,3.f };//engine->GetCamera().GetPosition();
		shader.light_color = light->GetColor();

		shader.camera_position_ws = engine.GetMainCamera()->GetPosition();

		renderer.DrawTriangles(&entity.model->mesh[0], entity.model->mesh.size());
	}
};

class SceneRenderTestBlinnPhong : public framework::Scene
{
private:
	std::shared_ptr<framework::MaterialEntity> sphere;
	std::shared_ptr<framework::TargetCamera> camera;
	std::shared_ptr<framework::PointLight> light;
public:
	void Init(framework::IRenderEngine& engine) override
	{
		auto material_blinn_phong = std::make_shared<MaterialBlinnPhong>();
		material_blinn_phong->tex0 = framework::GetResource<core::Texture>(L"tex0").value();

		//auto skybox = Spawn<framework::Skybox>();
		//skybox->cube_map = framework::GetResource<core::CubeMap>(L"cube_map").value();
		sphere = Spawn<framework::MaterialEntity>();
		sphere->model = framework::GetResource<core::Model>(L"sphere").value();
		sphere->material = material_blinn_phong;
		camera = std::make_shared<framework::TargetCamera>(sphere);

		light = Spawn<framework::PointLight>(); //std::make_shared<framework::DirectionalLight>();
		light->transform.position = { -1.f,2.f,3.f };
		light->color = { 2.4f,2.4f,1.6f };
		material_blinn_phong->light = light;
		//..
	}

	void HandleInput(const framework::IRenderEngine& engine) override
	{
		camera->HandleInput(engine);
		if (framework::IsKeyPressed<VK_CONTROL, 'R'>())
		{
			sphere->transform.rotation += core::Vec3{ 0, 0, 1 }*0.05f;
		}
		if (framework::IsKeyPressed<VK_CONTROL, 'F'>())
		{
			static size_t count = 0;
			sphere->transform.position = core::Vec3{ (cos(count / 500.f) - 1) * 2,0,  (sin(count / 500.f) - 1) * 2 };
			count += engine.GetEngineState().delta_count;
		}
	}

	virtual const framework::ICamera* GetMainCamera() const override
	{
		return camera.get();
	}

	virtual void Update(const framework::IRenderEngine& engine) override
	{
		size_t time = engine.GetEngineState().total_time;
		light->transform.position = core::Vec3{ (sin(time / 500.f)) * 2, 0.f, (-cos(time / 500.f)) * 2 };
	}
};
