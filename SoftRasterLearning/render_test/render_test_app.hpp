#pragma once

#include "render_test_unlit.hpp"
#include "render_test_light_blinn_phong.hpp"
#include "render_test_normal_mapping.hpp"
#include "render_test_skybox.hpp"

class RenderTestScene final : public framework::IScene
{
private:
	std::vector<std::shared_ptr<framework::IScene>> sub_scenes;
	size_t sub_scene_id = 0;
public:
	void Init(framework::IRenderEngine& engine) override
	{
		sub_scenes.push_back(std::make_shared<Scene_Render_Test_Test_Normal>());
		sub_scenes.push_back(std::make_shared<Scene_Render_Test_Test_Blinn_Phong>());
		sub_scenes.push_back(std::make_shared<Scene_Render_Test_Unlit>());
		sub_scenes.push_back(std::make_shared<Scene_Render_Test_Skybox>());

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

	virtual void OnMouseMove(const framework::IRenderEngine& engine) override
	{
		sub_scenes[sub_scene_id]->OnMouseMove(engine);
	}

	virtual void OnMouseWheel(const framework::IRenderEngine& engine) override
	{
		sub_scenes[sub_scene_id]->OnMouseWheel(engine);
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
		SoftRasterApp::Init();

		auto _sphere = loader::obj::LoadFromFile(L".\\resource\\models\\sphere.obj");
		auto _box = loader::obj::LoadFromFile(L".\\resource\\models\\box.obj");

		auto _tex = loader::bmp::LoadFromFile(L".\\resource\\pictures\\tex0.bmp");
		auto _sunlight_icon = loader::bmp::LoadFromFile(L".\\resource\\pictures\\icon\\sunlight.bmp");
		auto _normal_map = loader::bmp::LoadFromFile(L".\\resource\\pictures\\normal.bmp", false);

		auto _front = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\front.bmp");
		auto _back = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\back.bmp");
		auto _left = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\left.bmp");
		auto _right = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\right.bmp");
		auto _top = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\top.bmp");
		auto _bottom = loader::bmp::LoadFromFile(L".\\resource\\pictures\\cubemap\\bottom.bmp");

		framework::SetResource(L"cube_map", std::make_shared<core::CubeMap>(_front, _back, _top, _bottom, _left, _right));
		framework::SetResource(L"sphere", _sphere);
		framework::SetResource(L"box", _box);
		framework::SetResource(L"tex0", _tex);
		framework::SetResource(L"normal_map", _normal_map);
		framework::SetResource(L"sunlight", _sunlight_icon);

		//...
		scene = std::make_shared<RenderTestScene>();
	}
};
