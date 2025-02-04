﻿#pragma once

#include "render_test_light_blinn_phong.hpp"
#include "render_test_normal_mapping.hpp"
#include "render_test_skybox.hpp"
#include "render_test_shadow_mapping.hpp"
#include "render_test_pbr.hpp"
#include "render_test_deferred_rendering.hpp"
#include "loader\\bmp_loader.hpp"
#include "loader\\obj_loader.hpp"

class RenderTestScene final : public framework::IScene
{
private:
	std::vector<std::shared_ptr<framework::IScene>> sub_scenes;
	size_t sub_scene_id = 0;
public:
	void Init(framework::IRenderEngine& engine) override
	{
		sub_scenes.push_back(std::make_shared<SceneRenderTestNormalMap>());
		sub_scenes.push_back(std::make_shared<SceneRenderTestBlinnPhong>());
		sub_scenes.push_back(std::make_shared<SceneRenderTestShadowMapping>());
		sub_scenes.push_back(std::make_shared<SceneRenderTestSkybox>());
		sub_scenes.push_back(std::make_shared<SceneRenderTestPBR>());
		sub_scenes.push_back(std::make_shared<SceneRenderTestDrPBR>());

		for (auto& sub_scene : sub_scenes)
		{
			sub_scene->Init(engine);
		}
	}

	void HandleInput(const framework::IRenderEngine& engine) override
	{
		sub_scenes[sub_scene_id]->HandleInput(engine);
		if (engine.GetInputState().key_pressed[VK_SPACE])
		{
			sub_scene_id = ++sub_scene_id % sub_scenes.size();
		}
	}
	virtual void Update(const framework::IRenderEngine& engine) override
	{
		sub_scenes[sub_scene_id]->Update(engine);
	}
	virtual void RenderFrame(framework::IRenderEngine& engine) override
	{
		sub_scenes[sub_scene_id]->RenderFrame(engine);
	}

	virtual const framework::ICamera* GetMainCamera() const override
	{
		return sub_scenes[sub_scene_id]->GetMainCamera();
	}
};

class RenderTestApp final : public framework::SoftRasterApp
{
private:
	std::shared_ptr<framework::MaterialEntity> sphere;

public:
	RenderTestApp(HINSTANCE hinst) : SoftRasterApp{ hinst } {}

protected:

	void Init() override
	{
		auto _bunny = loader::obj::LoadFromFile(L".\\resource\\models\\bunny2.obj");
		auto _sphere = loader::obj::LoadFromFile(L".\\resource\\models\\sphere.obj");
		auto _box = loader::obj::LoadFromFile(L".\\resource\\models\\box.obj");

		auto _tex = loader::bmp::LoadFromFile(L".\\resource\\pictures\\tex0.bmp");
		auto _sunlight_icon = loader::bmp::LoadFromFile(L".\\resource\\pictures\\icon\\sunlight.bmp");
		auto _bulblight_icon = loader::bmp::LoadFromFile(L".\\resource\\pictures\\icon\\bulblight.bmp");

		auto _normal_map = loader::bmp::LoadFromFile(L".\\resource\\pictures\\normal.bmp", false);
		auto _bunny_normal_map = loader::bmp::LoadFromFile(L".\\resource\\pictures\\bunny_normal.bmp", false);


		auto _front = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\front.bmp");
		auto _back = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\back.bmp");
		auto _left = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\left.bmp");
		auto _right = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\right.bmp");
		auto _top = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\top.bmp");
		auto _bottom = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\bottom.bmp");
		auto _cubemap = std::make_shared<core::CubeMap>(_front, _back, _top, _bottom, _left, _right);
		auto _env_map = std::make_shared<core::pbr::IBL>();

		framework::SetResource(L"env_map", _env_map);
		framework::SetResource(L"cube_map", _cubemap);
		framework::SetResource(L"bunny", _bunny);
		framework::SetResource(L"bunny_normal_map", _bunny_normal_map);
		framework::SetResource(L"sphere", _sphere);
		framework::SetResource(L"box", _box);
		framework::SetResource(L"tex0", _tex);
		framework::SetResource(L"normal_map", _normal_map);
		framework::SetResource(L"sunlight", _sunlight_icon);
		framework::SetResource(L"bulblight", _bulblight_icon);

		//强行把天空盒变成HDR
		auto* env_tex = reinterpret_cast<decltype(_front)*>(_cubemap.get());
		for (size_t i = 0; i < 6; i++)
		{
			auto& data = env_tex[i]->GetData();
			std::transform(data.begin(), data.end(), data.begin(), [](core::Vec4 color) {
				//使用sinh函数提亮
				return core::Vec4{ _mm_sinh_ps(color * 2.1f) } / 2.1f; //把原来接近1的亮度提高到2, 而低亮度信息改变很少
				});
		}
		//...
		// 运行时计算环境光照贴图
		//std::thread t{ [&]() {
		//	_env_map->Init(*framework::GetResource<core::CubeMap>(L"cube_map").value().get());
		//} };
		//t.detach();
		// ...
		// 预计算环境光照贴图
		//_env_map->Init(*framework::GetResource<core::CubeMap>(L"cube_map").value().get());
		//_env_map->Save(L".\\resource\\env\\evn.ibl"); //小心覆盖
		//// 从文件加载光照贴图
		_env_map->Load(L".\\resource\\env\\evn.ibl");
		//...
		SoftRasterApp::Init();
		scene = std::make_shared<RenderTestScene>();
	}
};
