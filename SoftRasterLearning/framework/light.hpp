﻿#pragma once

#include "../core/game_math.hpp"
#include "../core/software_renderer.hpp"

namespace framework
{
	enum class ELightCategory
	{
		DirectionalLight = 0,
		PointLight = 1,
		Spotlight = 2
	};

	class ILight
	{
	public:
		using Vec3 = gmath::Vec3<float>;
		using Vec4 = gmath::Vec4<float>;
		using Mat3 = gmath::Mat3x3<float>;
		using Mat4 = gmath::Mat4x4<float>;

		virtual ELightCategory GetLightCategory() const noexcept = 0;
		virtual Vec3 GetColor() const = 0;
		virtual Vec3 GetPosition() const = 0;
		virtual Vec3 GetDirection() const = 0;
		virtual float GetCutOff() const = 0;
		virtual Mat4 GetLightMartrix() const = 0;
	};
};
