﻿#pragma once

#pragma once

#include "../core/core_api.hpp"
#include "../framework/framework.hpp"
#include "vs_out_type.hpp"

//镜面反射shader
class ShaderMirror
{
public:
	core::Mat mvp = {};
	core::Mat m = {};
	core::CubeMap* cube_map = nullptr;
	core::Texture* normal_map = nullptr;
	core::Vec3 camera_position_ws = { 0,0,5.f };

	VsOut_Light_ws VS(const core::Model_Vertex& v) const
	{
		using namespace core;
		Mat3 normal_mat = m.ToMat3x3().Inverse().Transpose();

		Vec3 tangent = (normal_mat * v.tangent).Normalize();
		Vec3 normal = (normal_mat * v.normal).Normalize();
		Vec3 bitangent = normal.Cross(tangent).Normalize();
		gmath::Mat3x3 TBN = { tangent, bitangent,normal };

		VsOut_Light_ws vs_out{};
		vs_out.position = mvp * v.position.ToHomoCoord();
		vs_out.position_ws = m * v.position.ToHomoCoord();
		vs_out.uv = v.uv;
		vs_out.normal_ws = v.tangent;
		vs_out.TBN = TBN;
		return vs_out;
	}

	core::Vec4 FS(const VsOut_Light_ws& v) const
	{
		using namespace core;
		Vec3 V = Vec3(camera_position_ws - v.position_ws).Normalize();
		Vec3 N = Vec3(Texture::Sample(normal_map, v.uv) * 2 - 1.f);
		N = (v.TBN * N).Normalize();
		Vec3 R = (-V).Reflect(N);

		Vec3 light_color = cube_map->Sample(R);

		return Vec4{ light_color * 0.8f , 1.f };
	}
};

class MaterialMirror : public framework::IMaterial
{
public:
	std::shared_ptr<core::CubeMap> cube_map;
	std::shared_ptr<core::Texture> normal_map;

	void Render(const framework::Entity& entity, framework::IRenderEngine& engine) override
	{
		ShaderMirror shader{};
		core::Renderer<ShaderMirror> renderer = { engine.GetCtx(), shader };
		shader.cube_map = cube_map.get();
		shader.normal_map = normal_map.get();
		shader.mvp = engine.GetMainCamera()->GetProjectionViewMatrix() * entity.transform.GetModelMatrix();
		shader.m = entity.transform.GetModelMatrix();
		shader.camera_position_ws = engine.GetMainCamera()->GetPosition();

		renderer.DrawTriangles(&entity.model->mesh[0], entity.model->mesh.size());
	}
};

class SceneRenderTestSkybox : public framework::Scene
{
private:
	std::shared_ptr<framework::MaterialEntity> sphere;
	std::shared_ptr<framework::TargetCamera> camera;

public:
	void Init(framework::IRenderEngine& engine) override
	{
		auto material = std::make_shared<MaterialMirror>();
		material->cube_map = framework::GetResource<core::CubeMap>(L"cube_map").value();
		material->normal_map = framework::GetResource<core::Texture>(L"normal_map").value();
		auto skybox = Spawn<framework::Skybox>();
		skybox->cube_map = framework::GetResource<core::CubeMap>(L"cube_map").value();
		sphere = Spawn<framework::MaterialEntity>();
		sphere->model = framework::GetResource<core::Model>(L"sphere").value();
		sphere->material = material;
		camera = std::make_shared<framework::TargetCamera>(sphere, 5.f, 0.f, -30.f);
		//..
	}

	void HandleInput(const framework::IRenderEngine& engine) override
	{
		camera->HandleInput(engine);
		if (framework::IsKeyPressed<VK_CONTROL, 'R'>())
		{
			sphere->transform.rotation += core::Vec3{ 0, 1, 0 }*0.05f;
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
};
