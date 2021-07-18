#pragma once

//vec4 sse加速
namespace gmath
{
	inline Vec4<float>::Vec4(float v) : x{ v }, y{ v }, z{ v }, w{ v }{}

	inline Vec4<float>::Vec4(float x, float y, float z, float w) : x{ x }, y{ y }, z{ z }, w{ w }{}

	inline Vec4<float>::Vec4(const Vec2<float>& vec2, float z, float w) : x{ vec2.x }, y{ vec2.y }, z{ z }, w{ w }{}

	inline Vec4<float>::Vec4(Vec3<float> vec3, float w) : x{ vec3.x }, y{ vec3.y }, z{ vec3.z }, w{ w }{}

	inline Vec4<float>::Vec4(__m128 data) : data_m128{ data } {}

	inline Vec4<float>::operator __m128()
	{
		return data_m128;
	}

	__forceinline Vec4<float> _vectorcall Vec4<float>::Pow(float rhs) const noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		return _mm_pow_ps(data_m128, rhs4); //假的intrinsic,
		//return _mm_exp10_ps(_mm_mul_ps(_mm_log10_ps(data_m128), rhs4));
		//return _mm_sqrt_ps(data_m128);
	}

	__forceinline Vec4<float> _vectorcall Vec4<float>::Sqrt() const noexcept
	{
		return _mm_sqrt_ps(data_m128);
	}

	__forceinline Vec4<float>& _vectorcall Vec4<float>::operator+=(Vec4 rhs) noexcept
	{
		data_m128 = _mm_add_ps(data_m128, rhs.data_m128);
		return *this;
	}

	__forceinline Vec4<float>& _vectorcall Vec4<float>::operator+=(float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		data_m128 = _mm_add_ps(data_m128, rhs4);
		return *this;
	}

	__forceinline Vec4<float>& _vectorcall Vec4<float>::operator-=(Vec4 rhs) noexcept
	{
		data_m128 = _mm_sub_ps(data_m128, rhs.data_m128);
		return *this;
	}

	__forceinline Vec4<float>& _vectorcall Vec4<float>::operator-=(float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		data_m128 = _mm_sub_ps(data_m128, rhs4);
		return *this;
	}

	__forceinline Vec4<float>& _vectorcall Vec4<float>::operator*=(Vec4 rhs) noexcept
	{
		data_m128 = _mm_mul_ps(data_m128, rhs.data_m128);
		return *this;
	}

	__forceinline Vec4<float>& _vectorcall Vec4<float>::operator*=(float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		data_m128 = _mm_mul_ps(data_m128, rhs4);
		return *this;
	}

	__forceinline Vec4<float>& _vectorcall Vec4<float>::operator/=(Vec4 rhs) noexcept
	{
		//data_m128 = _mm_mul_ps(data_m128, _mm_rcp_ps(rhs.data_m128));
		data_m128 = _mm_div_ps(data_m128, rhs.data_m128);
		return *this;
	}

	__forceinline Vec4<float>& _vectorcall Vec4<float>::operator/=(float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		//data_m128 = _mm_mul_ps(data_m128, _mm_rcp_ps(rhs4));
		data_m128 = _mm_div_ps(data_m128, rhs4);
		return *this;
	}

	__forceinline float _vectorcall Vec4<float>::Dot(Vec4 rhs) const noexcept
	{
		__m128 ret = _mm_mul_ps(data_m128, rhs.data_m128);
		ret = _mm_hadd_ps(ret, ret);
		ret = _mm_hadd_ps(ret, ret);
		return ret.m128_f32[0];
	}

	__forceinline Vec4<float> _vectorcall operator+(Vec4<float> lhs, Vec4<float> rhs) noexcept
	{
		return _mm_add_ps(lhs, rhs);
	}

	__forceinline Vec4<float> _vectorcall operator+(float lhs, Vec4<float> rhs) noexcept
	{
		__m128 lhs4 = _mm_set_ps1(lhs);
		return _mm_add_ps(lhs4, rhs);
	}

	__forceinline Vec4<float> _vectorcall operator+(Vec4<float> lhs, float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		return _mm_add_ps(lhs, rhs4);
	}

	__forceinline Vec4<float> _vectorcall operator-(Vec4<float> lhs, Vec4<float> rhs) noexcept
	{
		return _mm_sub_ps(lhs, rhs);
	}

	__forceinline Vec4<float> _vectorcall operator-(float lhs, Vec4<float> rhs) noexcept
	{
		__m128 lhs4 = _mm_set_ps1(lhs);
		return _mm_sub_ps(lhs4, rhs);
	}

	__forceinline Vec4<float> _vectorcall operator-(Vec4<float> lhs, float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		return _mm_sub_ps(lhs, rhs4);
	}

	__forceinline Vec4<float> _vectorcall operator*(Vec4<float> lhs, Vec4<float> rhs) noexcept
	{
		return _mm_mul_ps(lhs, rhs);
	}

	__forceinline Vec4<float> _vectorcall operator*(float lhs, Vec4<float> rhs) noexcept
	{
		__m128 lhs4 = _mm_set_ps1(lhs);
		return _mm_mul_ps(lhs4, rhs);
	}

	__forceinline Vec4<float> _vectorcall operator*(Vec4<float> lhs, float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		return _mm_mul_ps(lhs, rhs4);
	}

	__forceinline Vec4<float> _vectorcall operator/(Vec4<float> lhs, Vec4<float> rhs) noexcept
	{
		//return _mm_mul_ps(lhs, _mm_rcp_ps(rhs));
		return _mm_div_ps(lhs, rhs);
	}

	__forceinline Vec4<float> _vectorcall operator/(float lhs, Vec4<float> rhs) noexcept
	{
		__m128 lhs4 = _mm_set_ps1(lhs);
		//return _mm_mul_ps(lhs4, _mm_rcp_ps(rhs));
		return _mm_div_ps(lhs4, rhs);
	}

	__forceinline Vec4<float> _vectorcall operator/(Vec4<float> lhs, float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		//return _mm_mul_ps(lhs, _mm_rcp_ps(rhs4));
		return _mm_div_ps(lhs, rhs4);
	}
};

//vec3 sse加速
namespace gmath
{
	inline Vec3<float>::Vec3(float v) :x{ v }, y{ v }, z{ v }, _w{ 0 }{}
	inline Vec3<float>::Vec3(float x, float y, float z) : x{ x }, y{ y }, z{ z }, _w{ 0 }{}
	inline Vec3<float>::Vec3(Vec4<float> vec4) :
		x{ vec4.x },
		y{ vec4.y },
		z{ vec4.z },
		_w{ 0 }{};
	inline Vec3<float>::Vec3(Vec2<float> vec2, float z) :
		x{ vec2.x },
		y{ vec2.y },
		z{ z },
		_w{ 0 }
	{}
	inline Vec3<float>::Vec3(__m128 data) : data_m128{ data } {/* _w = 0; */ }
	inline Vec3<float>::operator __m128()
	{
		return data_m128;
	}

	__forceinline Vec4<float> Vec3<float>::ToHomoCoord() const
	{
		return Vec4<float>{x, y, z, 1.f};
	}

	__forceinline Vec3<float> _vectorcall Vec3<float>::cross(Vec3 rhs) const
	{
		__m128 temp1 = _mm_shuffle_ps(data_m128, data_m128, _MM_SHUFFLE(3, 0, 2, 1));
		__m128 temp2 = _mm_shuffle_ps(rhs.data_m128, rhs.data_m128, _MM_SHUFFLE(3, 1, 0, 2));
		__m128 ret = _mm_mul_ps(temp1, temp2);
		temp1 = _mm_shuffle_ps(temp1, temp1, _MM_SHUFFLE(3, 0, 2, 1));
		temp2 = _mm_shuffle_ps(temp2, temp2, _MM_SHUFFLE(3, 1, 0, 2));
		temp1 = _mm_mul_ps(temp1, temp2);
		ret = _mm_sub_ps(ret, temp1);
		return _mm_and_ps(ret, mask3.mask);
		//return Vec3{ y * rhs.z - z * rhs.y,z * rhs.x - x * rhs.z,x * rhs.y - y * rhs.x };
	}

	__forceinline Vec3<float> Vec3<float>::normalize() const
	{
		//float len = pow(x * x + y * y + z * z, 0.5f);
		__m128 len = _mm_dp_ps(data_m128, data_m128, 0x7f);
		len = _mm_sqrt_ps(len);
		//return _mm_and_ps(_mm_mul_ps(data_m128, _mm_rcp_ps(len)), mask3.mask);
		return _mm_and_ps(_mm_div_ps(data_m128, len), mask3.mask);
	}

	__forceinline float _vectorcall Vec3<float>::Dot(Vec3 rhs) const noexcept
	{
		//rhs._w = 0;
		//__m128 ret = _mm_mul_ps(data_m128, rhs.data_m128);
		//ret = _mm_and_ps(ret, mask3.mask);
		//ret = _mm_hadd_ps(ret, ret);
		//ret = _mm_hadd_ps(ret, ret);
		__m128 ret = _mm_dp_ps(data_m128, rhs.data_m128, 0x7f);
		return ret.m128_f32[0];
	}

	__forceinline Vec3<float>& _vectorcall Vec3<float>::operator+=(Vec3 rhs) noexcept
	{
		data_m128 = _mm_add_ps(data_m128, rhs.data_m128);
		return *this;
	}

	__forceinline Vec3<float>& _vectorcall Vec3<float>::operator+=(float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		data_m128 = _mm_add_ps(data_m128, rhs4);
		return *this;
	}

	__forceinline Vec3<float>& _vectorcall Vec3<float>::operator-=(Vec3 rhs) noexcept
	{
		data_m128 = _mm_sub_ps(data_m128, rhs.data_m128);
		return *this;
	}

	__forceinline Vec3<float>& _vectorcall Vec3<float>::operator-=(float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		data_m128 = _mm_sub_ps(data_m128, rhs4);
		return *this;
	}

	__forceinline Vec3<float>& _vectorcall Vec3<float>::operator*=(Vec3 rhs) noexcept
	{
		data_m128 = _mm_mul_ps(data_m128, rhs.data_m128);
		return *this;
	}

	__forceinline Vec3<float>& _vectorcall Vec3<float>::operator*=(float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		data_m128 = _mm_mul_ps(data_m128, rhs4);
		return *this;
	}

	__forceinline Vec3<float>& _vectorcall Vec3<float>::operator/=(Vec3 rhs) noexcept
	{
		//data_m128 = _mm_mul_ps(data_m128, _mm_rcp_ps(rhs.data_m128));
		data_m128 = _mm_div_ps(data_m128, rhs.data_m128);
		return *this;
	}

	__forceinline Vec3<float>& _vectorcall Vec3<float>::operator/=(float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		//data_m128 = _mm_mul_ps(data_m128, _mm_rcp_ps(rhs4));
		data_m128 = _mm_div_ps(data_m128, rhs4);
		return *this;
	}

	__forceinline Vec3<float> _vectorcall operator+(Vec3<float> lhs, Vec3<float> rhs) noexcept
	{
		return _mm_add_ps(lhs, rhs);
	}

	__forceinline Vec3<float> _vectorcall operator+(float lhs, Vec3<float> rhs) noexcept
	{
		__m128 lhs4 = _mm_set_ps1(lhs);
		return _mm_add_ps(lhs4, rhs);
	}

	__forceinline Vec3<float> _vectorcall operator+(Vec3<float> lhs, float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		return _mm_add_ps(lhs, rhs4);
	}

	__forceinline Vec3<float> _vectorcall operator-(Vec3<float> lhs, Vec3<float> rhs) noexcept
	{
		return _mm_sub_ps(lhs, rhs);
	}

	__forceinline Vec3<float> _vectorcall operator-(float lhs, Vec3<float> rhs) noexcept
	{
		__m128 lhs4 = _mm_set_ps1(lhs);
		return _mm_sub_ps(lhs4, rhs);
	}

	__forceinline Vec3<float> _vectorcall operator-(Vec3<float> lhs, float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		return _mm_sub_ps(lhs, rhs4);
	}

	__forceinline Vec3<float> _vectorcall operator*(Vec3<float> lhs, Vec3<float> rhs) noexcept
	{
		return _mm_mul_ps(lhs, rhs);
	}

	__forceinline Vec3<float> _vectorcall operator*(float lhs, Vec3<float> rhs) noexcept
	{
		__m128 lhs4 = _mm_set_ps1(lhs);
		return _mm_mul_ps(lhs4, rhs);
	}

	__forceinline Vec3<float> _vectorcall operator*(Vec3<float> lhs, float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		return _mm_mul_ps(lhs, rhs4);
	}

	__forceinline Vec3<float> _vectorcall operator/(Vec3<float> lhs, Vec3<float> rhs) noexcept
	{
		//return _mm_mul_ps(lhs, _mm_rcp_ps(rhs));
		return _mm_div_ps(lhs, rhs);
	}

	__forceinline Vec3<float> _vectorcall operator/(float lhs, Vec3<float> rhs) noexcept
	{
		__m128 lhs4 = _mm_set_ps1(lhs);
		//return _mm_mul_ps(lhs4, _mm_rcp_ps(rhs));
		return _mm_div_ps(lhs4, rhs);
	}

	__forceinline Vec3<float> _vectorcall operator/(Vec3<float> lhs, float rhs) noexcept
	{
		__m128 rhs4 = _mm_set_ps1(rhs);
		//return _mm_mul_ps(lhs, _mm_rcp_ps(rhs4));
		return _mm_div_ps(lhs, rhs4);
	}
}

//mat4x4 sse加速
namespace gmath
{
	inline Mat4x4<float>::Mat4x4(float _0, float _1, float _2, float _3, float _4, float _5, float _6, float _7, float _8, float _9, float _10, float _11, float _12, float _13, float _14, float _15) :
		data{
		_0,_4,_8,_12,
		_1,_5,_9,_13,
		_2,_6,_10,_14,
		_3,_7,_11,_15
	}
	{}

	inline Mat4x4<float>::Mat4x4(__m128 c1, __m128 c2, __m128 c3, __m128 c4) :
		column{ c1,c2,c3,c4 }
	{
	}

	//矩阵乘法
	__forceinline Mat4x4<float> Mat4x4<float>::operator*(const Mat4x4<float>& rhs) const
	{
		__m128 lhs_column_0 = column[0];
		__m128 lhs_column_1 = column[1];
		__m128 lhs_column_2 = column[2];
		__m128 lhs_column_3 = column[3];
		__m128 rhs_column_0 = rhs.column[0];
		__m128 rhs_column_1 = rhs.column[1];
		__m128 rhs_column_2 = rhs.column[2];
		__m128 rhs_column_3 = rhs.column[3];

		//对每个列进行向量乘法，最后合并为新的矩阵
		__m128 x = _mm_shuffle_ps(rhs_column_0, rhs_column_0, _MM_SHUFFLE(0, 0, 0, 0)); //提取第一列的第一个元素
		__m128 y = _mm_shuffle_ps(rhs_column_0, rhs_column_0, _MM_SHUFFLE(1, 1, 1, 1)); //提取第一列的第二个元素
		__m128 z = _mm_shuffle_ps(rhs_column_0, rhs_column_0, _MM_SHUFFLE(2, 2, 2, 2)); //提取第一列的第三个元素
		__m128 w = _mm_shuffle_ps(rhs_column_0, rhs_column_0, _MM_SHUFFLE(3, 3, 3, 3)); //提取第一列的第四个元素

		//得到新的第一列
		rhs_column_0 = _mm_mul_ps(lhs_column_0, x);
		rhs_column_0 = _mm_add_ps(rhs_column_0, _mm_mul_ps(lhs_column_1, y));
		rhs_column_0 = _mm_add_ps(rhs_column_0, _mm_mul_ps(lhs_column_2, z));
		rhs_column_0 = _mm_add_ps(rhs_column_0, _mm_mul_ps(lhs_column_3, w));

		x = _mm_shuffle_ps(rhs_column_1, rhs_column_1, _MM_SHUFFLE(0, 0, 0, 0));
		y = _mm_shuffle_ps(rhs_column_1, rhs_column_1, _MM_SHUFFLE(1, 1, 1, 1));
		z = _mm_shuffle_ps(rhs_column_1, rhs_column_1, _MM_SHUFFLE(2, 2, 2, 2));
		w = _mm_shuffle_ps(rhs_column_1, rhs_column_1, _MM_SHUFFLE(3, 3, 3, 3));

		//第二列
		rhs_column_1 = _mm_mul_ps(lhs_column_0, x);
		rhs_column_1 = _mm_add_ps(rhs_column_1, _mm_mul_ps(lhs_column_1, y));
		rhs_column_1 = _mm_add_ps(rhs_column_1, _mm_mul_ps(lhs_column_2, z));
		rhs_column_1 = _mm_add_ps(rhs_column_1, _mm_mul_ps(lhs_column_3, w));

		x = _mm_shuffle_ps(rhs_column_2, rhs_column_2, _MM_SHUFFLE(0, 0, 0, 0));
		y = _mm_shuffle_ps(rhs_column_2, rhs_column_2, _MM_SHUFFLE(1, 1, 1, 1));
		z = _mm_shuffle_ps(rhs_column_2, rhs_column_2, _MM_SHUFFLE(2, 2, 2, 2));
		w = _mm_shuffle_ps(rhs_column_2, rhs_column_2, _MM_SHUFFLE(3, 3, 3, 3));

		//第三列
		rhs_column_2 = _mm_mul_ps(lhs_column_0, x);
		rhs_column_2 = _mm_add_ps(rhs_column_2, _mm_mul_ps(lhs_column_1, y));
		rhs_column_2 = _mm_add_ps(rhs_column_2, _mm_mul_ps(lhs_column_2, z));
		rhs_column_2 = _mm_add_ps(rhs_column_2, _mm_mul_ps(lhs_column_3, w));

		x = _mm_shuffle_ps(rhs_column_3, rhs_column_3, _MM_SHUFFLE(0, 0, 0, 0));
		y = _mm_shuffle_ps(rhs_column_3, rhs_column_3, _MM_SHUFFLE(1, 1, 1, 1));
		z = _mm_shuffle_ps(rhs_column_3, rhs_column_3, _MM_SHUFFLE(2, 2, 2, 2));
		w = _mm_shuffle_ps(rhs_column_3, rhs_column_3, _MM_SHUFFLE(3, 3, 3, 3));

		//第四列
		rhs_column_3 = _mm_mul_ps(lhs_column_0, x);
		rhs_column_3 = _mm_add_ps(rhs_column_3, _mm_mul_ps(lhs_column_1, y));
		rhs_column_3 = _mm_add_ps(rhs_column_3, _mm_mul_ps(lhs_column_2, z));
		rhs_column_3 = _mm_add_ps(rhs_column_3, _mm_mul_ps(lhs_column_3, w));

		return Mat4x4<float>{ rhs_column_0, rhs_column_1, rhs_column_2, rhs_column_3 };
	}

	//乘向量 4分量
	__forceinline Vec4<float> _vectorcall Mat4x4<float>::operator*(Vec4<float> rhs) const
	{
		__m128 x = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 y = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 z = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 w = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(3, 3, 3, 3));
		__m128 ret = _mm_mul_ps(column[0], x);
		ret = _mm_add_ps(ret, _mm_mul_ps(column[1], y));
		ret = _mm_add_ps(ret, _mm_mul_ps(column[2], z));
		ret = _mm_add_ps(ret, _mm_mul_ps(column[3], w));
		return ret;
	}

	__forceinline Mat4x4<float> Mat4x4<float>::Transpose() const
	{
		__m128 c0 = column[0];
		__m128 c1 = column[1];
		__m128 c2 = column[2];
		__m128 c3 = column[3];

		_MM_TRANSPOSE4_PS(c0, c1, c2, c3);

		return Mat4x4{ c0,c1,c2,c3 };
	}

	inline Mat3x3<float> Mat4x4<float>::ToMat3x3() const
	{
		return Mat3x3<float>{
			_mm_and_ps(column[0], Vec3<float>::mask3.mask),
				_mm_and_ps(column[1], Vec3<float>::mask3.mask),
				_mm_and_ps(column[2], Vec3<float>::mask3.mask),
		};
	}
}

//mat4x4 sse加速
namespace gmath
{
	inline Mat3x3<float>::Mat3x3(__m128 c1, __m128 c2, __m128 c3) :
		column{ c1,c2,c3 }
	{
	}
	inline Mat3x3<float>::Mat3x3(float a, float b, float c, float d, float e, float f, float g, float h, float i) :
		data{
		a,d,g,0,
		b,e,h,0,
		c,f,i,0 }
	{
	}

	//乘矩阵
	__forceinline Mat3x3<float> Mat3x3<float>::operator*(const Mat3x3<float>& rhs) const
	{
		__m128 lhs_column_0 = column[0];
		__m128 lhs_column_1 = column[1];
		__m128 lhs_column_2 = column[2];
		__m128 rhs_column_0 = rhs.column[0];
		__m128 rhs_column_1 = rhs.column[1];
		__m128 rhs_column_2 = rhs.column[2];

		//对每个列进行向量乘法，最后合并为新的矩阵
		__m128 x = _mm_shuffle_ps(rhs_column_0, rhs_column_0, _MM_SHUFFLE(0, 0, 0, 0)); //提取第一列的第一个元素
		__m128 y = _mm_shuffle_ps(rhs_column_0, rhs_column_0, _MM_SHUFFLE(1, 1, 1, 1)); //提取第一列的第二个元素
		__m128 z = _mm_shuffle_ps(rhs_column_0, rhs_column_0, _MM_SHUFFLE(2, 2, 2, 2)); //提取第一列的第三个元素

		//得到新的第一列
		rhs_column_0 = _mm_mul_ps(lhs_column_0, x);
		rhs_column_0 = _mm_add_ps(rhs_column_0, _mm_mul_ps(lhs_column_1, y));
		rhs_column_0 = _mm_add_ps(rhs_column_0, _mm_mul_ps(lhs_column_2, z));

		x = _mm_shuffle_ps(rhs_column_1, rhs_column_1, _MM_SHUFFLE(0, 0, 0, 0));
		y = _mm_shuffle_ps(rhs_column_1, rhs_column_1, _MM_SHUFFLE(1, 1, 1, 1));
		z = _mm_shuffle_ps(rhs_column_1, rhs_column_1, _MM_SHUFFLE(2, 2, 2, 2));

		//第二列
		rhs_column_1 = _mm_mul_ps(lhs_column_0, x);
		rhs_column_1 = _mm_add_ps(rhs_column_1, _mm_mul_ps(lhs_column_1, y));
		rhs_column_1 = _mm_add_ps(rhs_column_1, _mm_mul_ps(lhs_column_2, z));

		x = _mm_shuffle_ps(rhs_column_2, rhs_column_2, _MM_SHUFFLE(0, 0, 0, 0));
		y = _mm_shuffle_ps(rhs_column_2, rhs_column_2, _MM_SHUFFLE(1, 1, 1, 1));
		z = _mm_shuffle_ps(rhs_column_2, rhs_column_2, _MM_SHUFFLE(2, 2, 2, 2));

		//第三列
		rhs_column_2 = _mm_mul_ps(lhs_column_0, x);
		rhs_column_2 = _mm_add_ps(rhs_column_2, _mm_mul_ps(lhs_column_1, y));
		rhs_column_2 = _mm_add_ps(rhs_column_2, _mm_mul_ps(lhs_column_2, z));

		return Mat3x3<float>{ rhs_column_0, rhs_column_1, rhs_column_2 };
	}
	//乘向量
	__forceinline Vec3<float> _vectorcall Mat3x3<float>::operator*(Vec3<float> rhs) const
	{
		__m128 x = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 y = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 z = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 ret = _mm_mul_ps(column[0], x);
		ret = _mm_add_ps(ret, _mm_mul_ps(column[1], y));
		ret = _mm_add_ps(ret, _mm_mul_ps(column[2], z));
		return _mm_and_ps(ret, Vec3<float>::mask3.mask);
	}

	//inline Vec4<float> _vectorcall Mat3x3<float>::operator*(Vec4<float> rhs) const
	//{
	//	__m128 x = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(0, 0, 0, 0));
	//	__m128 y = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(1, 1, 1, 1));
	//	__m128 z = _mm_shuffle_ps(rhs, rhs, _MM_SHUFFLE(2, 2, 2, 2));
	//	__m128 ret = _mm_mul_ps(column[0], x);
	//	ret = _mm_add_ps(ret, _mm_mul_ps(column[1], y));
	//	ret = _mm_add_ps(ret, _mm_mul_ps(column[2], z));
	//	return ret;
	//}

	//转置
	inline Mat3x3<float> Mat3x3<float>::Transpose() const
	{
		__m128 c0 = column[0];
		__m128 c1 = column[1];
		__m128 c2 = column[2];
		__m128 c3 = {};
		_MM_TRANSPOSE4_PS(c0, c1, c2, c3);

		return Mat3x3{ c0,c1,c2 };
	}

	//求逆
	inline Mat3x3<float> Mat3x3<float>::Inverse() const
	{
		//暂时不用sse改造, 因为基本只在顶点着色器使用
		float det = data[0] * data[5] * data[10] + data[4] * data[9] * data[2] + data[8] * data[1] * data[6] -
			data[2] * data[5] * data[8] - data[6] * data[9] * data[0] - data[10] * data[1] * data[4];

		if (fabs(det) <= 1e-20)
		{
			//不可求逆,返回自身
			return *this;
		}

		//手算 A* / |A|（的转置）
		Mat3x3<float> _inverse = Mat3x3<float>{
			//第一行
			 (data[5] * data[10] - data[9] * data[6]) / det,
			-(data[1] * data[10] - data[9] * data[2]) / det,
			(data[1] * data[6] - data[5] * data[2]) / det,
			//第二行
			-(data[4] * data[10] - data[8] * data[6]) / det,
			(data[0] * data[10] - data[8] * data[2]) / det,
			-(data[0] * data[6] - data[4] * data[2]) / det,
			//第三行
			(data[4] * data[9] - data[8] * data[5]) / det,
			-(data[0] * data[9] - data[8] * data[1]) / det,
			(data[0] * data[5] - data[4] * data[1]) / det,
		};

		//转置
		_inverse = _inverse.Transpose();

		//矩阵中可能出现-0.0f，但不重要, 因为矩阵中的元素不会被除
		return _inverse;
	}
}

namespace gmath
{
	template<typename T> inline Vec4<T>::Vec4(T v) : x{ v }, y{ v }, z{ v }, w{ v }{}
	template<typename T> inline Vec4<T>::Vec4(T x, T y, T z, T w) : x{ x }, y{ y }, z{ z }, w{ w }{}
	template<typename T> inline Vec4<T>::Vec4(const Vec2<T>& vec2, T z, T w) : x{ vec2.x }, y{ vec2.y }, z{ z }, w{ w }{}
	template<typename T> inline Vec4<T>::Vec4(const Vec3<T>& vec3, T w) : x{ vec3.x }, y{ vec3.y }, z{ vec3.z }, w{ w }{}

	template<typename T>inline  T  Vec4<T>::Dot(const Vec4<T>& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z + w * rhs.w;
	}

	template<typename T> inline Vec4<T> Vec4<T>::operator+(const Vec4& rhs) const
	{
		return { x + rhs.x,y + rhs.y,z + rhs.z, w + rhs.w };
	}

	template<typename T> inline Vec4<T> Vec4<T>::operator-(const Vec4& rhs) const
	{
		return { x - rhs.x,y - rhs.y,z - rhs.z, w - rhs.w };
	}

	template<typename T> inline Vec4<T>& Vec4<T>::operator+=(const Vec4& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		w += rhs.w;
		return *this;
	}
	template<typename T> inline Vec4<T>& Vec4<T>::operator-=(const Vec4& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		w -= rhs.w;
		return *this;
	}
	template<typename T> inline Vec4<T>& Vec4<T>::operator*=(const Vec4& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		w *= rhs.w;
		return *this;
	}
	template<typename T> inline Vec4<T>& Vec4<T>::operator/=(const Vec4& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		w /= rhs.w;
		return *this;
	}

	template<typename T> inline Vec4<T> operator*(const Vec4<T>& lhs, T rhs)
	{
		return { lhs.x * rhs,lhs.y * rhs,lhs.z * rhs,lhs.w * rhs };
	}

	template<typename T> inline Vec4<T> operator*(T lhs, const Vec4<T>& rhs)
	{
		return { rhs.x * lhs,rhs.y * lhs,rhs.z * lhs, rhs.w * lhs };
	}

	template<typename T> inline Vec4<T> operator/(const Vec4<T>& lhs, T rhs)
	{
		return { lhs.x / rhs,lhs.y / rhs,lhs.z / rhs, lhs.w / rhs };
	}

	template<typename T> inline Vec4<T> operator*(const Vec4<T>& lhs, const Vec4<T>& rhs)
	{
		return { lhs.x * rhs.x,lhs.y * rhs.y,lhs.z * rhs.z, lhs.w * rhs.w };
	}
};

namespace gmath
{
	template<typename T> inline Vec3<T>::Vec3(T v) : x{ v }, y{ v }, z{ v }{}

	template<typename T> inline Vec3<T>::Vec3(T x, T y, T z) : x{ x }, y{ y }, z{ z }{}

	template<typename T> inline Vec3<T>::Vec3(const Vec4<T>& vec4) :
		x{ vec4.x },
		y{ vec4.y },
		z{ vec4.z }
	{}

	template<typename T> inline Vec3<T>::Vec3(const Vec2<T>& vec2) :x{ vec2.x }, y{ vec2.y }{}

	template<typename T> inline Vec4<T> Vec3<T>::ToHomoCoord() const
	{
		return Vec4<T>{ x, y, z, 1.f };
	}

	template<typename T> inline Vec3<T> Vec3<T>::normalize() const
	{
		T len = pow(x * x + y * y + z * z, 0.5f);
		return {
			x / len,
			y / len,
			z / len
		};
	}

	template<typename T> inline T Vec3<T>::Dot(const Vec3& rhs) const
	{
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	template<typename T> inline Vec3<T> Vec3<T>::cross(const Vec3& b) const
	{
		return Vec3{ y * b.z - z * b.y,z * b.x - x * b.z,x * b.y - y * b.x };
	}

	template<typename T> inline Vec3<T> Vec3<T>::operator+(const Vec3& rhs) const
	{
		return { x + rhs.x,y + rhs.y,z + rhs.z };
	}

	template<typename T> inline Vec3<T> Vec3<T>::operator-(const Vec3& rhs) const
	{
		return { x - rhs.x,y - rhs.y,z - rhs.z };
	}

	template<typename T> inline Vec3<T> operator*(const Vec3<T>& lhs, T rhs)
	{
		return { lhs.x * rhs,lhs.y * rhs,lhs.z * rhs };
	}
	template<typename T> inline Vec3<T>operator*(T lhs, const Vec3<T>& rhs)
	{
		return { rhs.x * lhs,rhs.y * lhs,rhs.z * lhs };
	}
	template<typename T> inline Vec3<T> operator/(const Vec3<T>& lhs, T rhs)
	{
		return { lhs.x / rhs,lhs.y / rhs,lhs.z / rhs };
	}

	template<typename T> inline Vec3<T> operator*(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{
		return { lhs.x * rhs.x,lhs.y * rhs.y,lhs.z * rhs.z };
	}

	template<typename T> inline Vec3<T>& Vec3<T>::operator+=(const Vec3& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}
	template<typename T> inline Vec3<T>& Vec3<T>::operator-=(const Vec3& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}
	template<typename T> inline Vec3<T>& Vec3<T>::operator*=(const Vec3& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;
		return *this;
	}
	template<typename T> inline Vec3<T>& Vec3<T>::operator/=(const Vec3& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		z /= rhs.z;
		return *this;
	}
};

namespace gmath
{
	template<typename T> inline Vec2<T>::Vec2(T v) : x{ v }, y{ v } {}
	template<typename T> inline Vec2<T>::Vec2(T x, T y) : x{ x }, y{ y } {}
	template<typename T> inline Vec2<T>::Vec2(const Vec4<T>& vec4) : x{ vec4.x }, y{ vec4.y }{}
	template<typename T> inline Vec2<T>::Vec2(const Vec3<T>& vec3) : x{ vec3.x }, y{ vec3.y }{}

	template<typename T> inline Vec2<T> Vec2<T>::operator+(const Vec2& rhs) const
	{
		return { x + rhs.x,y + rhs.y };
	}

	template<typename T> inline Vec2<T> Vec2<T>::operator-(const Vec2& rhs) const
	{
		return { x - rhs.x,y - rhs.y };
	}

	template<typename T> inline T Vec2<T>::Dot(const Vec2& rhs) const
	{
		return x * rhs.x + y * rhs.y;
	}

	template<typename T> inline T Vec2<T>::cross(const Vec2 b) const
	{
		return x * b.y - y * b.x;
	}

	template<typename T> inline Vec2<T> Vec2<T>::normalize() const
	{
		T len = pow(x * x + y * y, 0.5f);
		return {
			x / len,
			y / len
		};
	}

	template<typename T> inline Vec2<T> operator*(const  Vec2<T>& lhs, T rhs)
	{
		return { lhs.x * rhs, lhs.y * rhs };
	}
	template<typename T> inline Vec2<T> operator*(T lhs, const  Vec2<T>& rhs)
	{
		return { rhs.x * lhs, rhs.y * lhs };
	}
	template<typename T> inline Vec2<T> operator/(const  Vec2<T>& lhs, T rhs)
	{
		return { lhs.x / rhs, lhs.y / rhs };
	}

	template<typename T>  Vec2<T> operator*(const  Vec2<T>& lhs, const  Vec2<T>& rhs)
	{
		return { lhs.x * rhs.x,lhs.y * rhs.y };
	}

	template<typename T> inline Vec2<T>& Vec2<T>::operator+=(const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	template<typename T> inline Vec2<T>& Vec2<T>::operator-=(const Vec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
	template<typename T> inline Vec2<T>& Vec2<T>::operator*=(const Vec2& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		return *this;
	}
	template<typename T> inline Vec2<T>& Vec2<T>::operator/=(const Vec2& rhs)
	{
		x /= rhs.x;
		y /= rhs.y;
		return *this;
	}
};

namespace gmath
{
	template<typename T> inline  Mat3x3<T>::Mat3x3(Vec3<T> a, Vec3<T> b, Vec3<T> c)
	{
		data[0] = a.x;
		data[1] = b.x;
		data[2] = c.x;
		data[3] = a.y;
		data[4] = b.y;
		data[5] = c.y;
		data[6] = a.z;
		data[7] = b.z;
		data[8] = c.z;
	}

	template<typename T> inline Mat3x3<T>::Mat3x3(T a, T b, T c, T d, T e, T f, T g, T h, T i)
	{
		data[0] = a;
		data[1] = b;
		data[2] = c;
		data[3] = d;
		data[4] = e;
		data[5] = f;
		data[6] = g;
		data[7] = h;
		data[8] = i;
	}

	//乘矩阵
	template<typename T> inline Mat3x3<T> Mat3x3<T>::operator*(const Mat3x3& rhs) const
	{
		return Mat3x3{
			//第一行
			data[0] * rhs.data[0] + data[1] * rhs.data[3] + data[2] * rhs.data[6],
			data[0] * rhs.data[1] + data[1] * rhs.data[4] + data[2] * rhs.data[7],
			data[0] * rhs.data[2] + data[1] * rhs.data[5] + data[2] * rhs.data[8],
			//第二行
			data[3] * rhs.data[0] + data[4] * rhs.data[3] + data[5] * rhs.data[6],
			data[3] * rhs.data[1] + data[4] * rhs.data[4] + data[5] * rhs.data[7],
			data[3] * rhs.data[2] + data[4] * rhs.data[5] + data[5] * rhs.data[8],
			//第三行
			data[6] * rhs.data[0] + data[7] * rhs.data[3] + data[8] * rhs.data[6],
			data[6] * rhs.data[1] + data[7] * rhs.data[4] + data[8] * rhs.data[7],
			data[6] * rhs.data[2] + data[7] * rhs.data[5] + data[8] * rhs.data[8],
		};
	}

	//乘向量
	template<typename T> inline Vec3<T> Mat3x3<T>::operator*(const Vec3<T>& rhs) const
	{
		return Vec3<T>{
			data[0] * rhs.x + data[1] * rhs.y + data[2] * rhs.z,
				data[3] * rhs.x + data[4] * rhs.y + data[5] * rhs.z,
				data[6] * rhs.x + data[7] * rhs.y + data[8] * rhs.z
		};
	}

	//乘向量
	template<typename T> inline Vec4<T> Mat3x3<T>::operator*(const Vec4<T>& rhs) const
	{
		return Vec4<T>{
			data[0] * rhs.x + data[1] * rhs.y + data[2] * rhs.z,
				data[3] * rhs.x + data[4] * rhs.y + data[5] * rhs.z,
				data[6] * rhs.x + data[7] * rhs.y + data[8] * rhs.z,
				1.f
		};
	}

	//构造单位矩阵
	template<typename T> inline Mat3x3<T> Mat3x3<T>::Unit()
	{
		return Mat3x3{
			1.f,0,0,
			0,1.f,0,
			0,0,1.f,
		};
	}

	//转置
	template<typename T> inline Mat3x3<T> Mat3x3<T>::Transpose() const
	{
		return Mat3x3{
			data[0],data[3],data[6],
			data[1],data[4],data[7],
			data[2],data[5],data[8]
		};
	}

	//求逆
	template<typename T> inline Mat3x3<T> Mat3x3<T>::Inverse() const
	{
		// A^-1 =  A*/|A|
		//A* : A的伴随矩阵
		//|A| : A的行列式

		//手算 |A|
		float det = data[0] * data[4] * data[8] + data[1] * data[5] * data[6] + data[2] * data[3] * data[7] -
			data[6] * data[4] * data[2] - data[7] * data[5] * data[0] - data[8] * data[3] * data[1];

		if (fabs(det) <= 1e-20)
		{
			//不可求逆,返回自身
			return *this;
		}

		//手算 A* / |A|（的转置）
		Mat3x3<T> _inverse = Mat3x3<T>{
			//第一行
			 (data[4] * data[8] - data[5] * data[7]) / det,
			-(data[3] * data[8] - data[5] * data[6]) / det,
			(data[3] * data[7] - data[4] * data[6]) / det,
			//第二行
			-(data[1] * data[8] - data[2] * data[7]) / det,
			(data[0] * data[8] - data[2] * data[6]) / det,
			-(data[0] * data[7] - data[1] * data[6]) / det,
			//第三行
			(data[1] * data[5] - data[2] * data[4]) / det,
			-(data[0] * data[5] - data[2] * data[3]) / det,
			(data[0] * data[4] - data[1] * data[3]) / det,
		};

		//转置
		_inverse = _inverse.Transpose();

		//矩阵中可能出现-0.0f，但不重要, 因为矩阵中的元素不会被除
		return _inverse;
	}
};

namespace gmath
{
	//矩阵乘法
	template<typename T> Mat4x4<T> Mat4x4<T>::operator*(const Mat4x4& rhs) const
	{
		return Mat4x4{
			//第一行
			data[0] * rhs.data[0] + data[1] * rhs.data[4] + data[2] * rhs.data[8] + data[3] * rhs.data[12],
			data[0] * rhs.data[1] + data[1] * rhs.data[5] + data[2] * rhs.data[9] + data[3] * rhs.data[13],
			data[0] * rhs.data[2] + data[1] * rhs.data[6] + data[2] * rhs.data[10] + data[3] * rhs.data[14],
			data[0] * rhs.data[3] + data[1] * rhs.data[7] + data[2] * rhs.data[11] + data[3] * rhs.data[15],
			//第二行
			data[4] * rhs.data[0] + data[5] * rhs.data[4] + data[6] * rhs.data[8] + data[7] * rhs.data[12],
			data[4] * rhs.data[1] + data[5] * rhs.data[5] + data[6] * rhs.data[9] + data[7] * rhs.data[13],
			data[4] * rhs.data[2] + data[5] * rhs.data[6] + data[6] * rhs.data[10] + data[7] * rhs.data[14],
			data[4] * rhs.data[3] + data[5] * rhs.data[7] + data[6] * rhs.data[11] + data[7] * rhs.data[15],
			//第三行
			data[8] * rhs.data[0] + data[9] * rhs.data[4] + data[10] * rhs.data[8] + data[11] * rhs.data[12],
			data[8] * rhs.data[1] + data[9] * rhs.data[5] + data[10] * rhs.data[9] + data[11] * rhs.data[13],
			data[8] * rhs.data[2] + data[9] * rhs.data[6] + data[10] * rhs.data[10] + data[11] * rhs.data[14],
			data[8] * rhs.data[3] + data[9] * rhs.data[7] + data[10] * rhs.data[11] + data[11] * rhs.data[15],
			//第四行
			data[12] * rhs.data[0] + data[13] * rhs.data[4] + data[14] * rhs.data[8] + data[15] * rhs.data[12],
			data[12] * rhs.data[1] + data[13] * rhs.data[5] + data[14] * rhs.data[9] + data[15] * rhs.data[13],
			data[12] * rhs.data[2] + data[13] * rhs.data[6] + data[14] * rhs.data[10] + data[15] * rhs.data[14],
			data[12] * rhs.data[3] + data[13] * rhs.data[7] + data[14] * rhs.data[11] + data[15] * rhs.data[15]
		};
	}

	//乘向量 4分量
	template<typename T> Vec4<T> Mat4x4<T>::operator*(const Vec4<T>& rhs) const
	{
		return Vec4<T>{
			data[0] * rhs.x + data[1] * rhs.y + data[2] * rhs.z + data[3] * rhs.w,
				data[4] * rhs.x + data[5] * rhs.y + data[6] * rhs.z + data[7] * rhs.w,
				data[8] * rhs.x + data[9] * rhs.y + data[10] * rhs.z + data[11] * rhs.w,
				data[12] * rhs.x + data[13] * rhs.y + data[14] * rhs.z + data[15] * rhs.w,
		};
	}

	template<typename T> Mat3x3<T> Mat4x4<T>::ToMat3x3() const
	{
		return Mat3x3 <T>{
			data[0], data[1], data[2],
				data[4], data[5], data[6],
				data[8], data[9], data[10],
		};
	}
};

namespace gmath::utility
{
	template<typename T, typename U, typename V>
	inline T Clamp(T v, U a, V b)
	{
		return ((v < a ? a : v) < b ? (v < a ? a : v) : b);
	}

	template<typename T>
	inline T Clamp(T v)
	{
		return ((v < 0 ? 0 : v) < 1 ? (v < 0 ? 0 : v) : 1);
	}

	template<typename T, typename U>
	inline T Lerp(T a, T b, U n)
	{
		return a * n + b * (1.0f - n);
	}

	template<typename T>
	inline T BlendColor(T color0, T color1)
	{
		float a = 1.0f - (1.0f - color1.a) * (1.0f - color0.a);
		T color = 1.0f / a * (color1 * color1.a + (1.0f - color1.a) * color0.a * color0);
		color.a = a;
		return color;
	}

	inline float radians(float degree)
	{
		return degree / 180.f * pi;
	}

	inline float degrees(float radian)
	{
		return radian * 180.f / pi;
	}

	template<typename T>
	inline Mat3x3<T> Mat3Unit()
	{
		return Mat4x4<T>{
			1.f, 0, 0,
				0, 1.f, 0,
				0, 0, 1.f,
		};
	}

	template<typename T>
	inline Mat4x4<T> Mat4Unit()
	{
		return Mat4x4<T>{
			1.f, 0, 0, 0,
				0, 1.f, 0, 0,
				0, 0, 1.f, 0,
				0, 0, 0, 1.f
		};
	}

	//平移
	template<typename T>
	inline Mat4x4<T> Translate(T x, T y, T z)
	{
		return Mat4x4<T>{
			1.f, 0, 0, x,
				0, 1.f, 0, y,
				0, 0, 1.f, z,
				0, 0, 0, 1.f
		};
	}

	template<typename T>
	inline Mat4x4<T> Translate(const Vec3<T>& v)
	{
		return Mat4x4<T>{
			1.f, 0, 0, v.x,
				0, 1.f, 0, v.y,
				0, 0, 1.f, v.z,
				0, 0, 0, 1.f
		};
	}

	template<typename T>
	inline Mat4x4<T> Rotate(T x, T y, T z)
	{
		Mat4x4<T> Rx = Mat4x4<T>{
			1.f, 0, 0, 0,
				0, cos(x), sin(x), 0,
				0, -sin(x), cos(x), 0,
				0, 0, 0, 1.f
		};

		Mat4x4<T> Ry = Mat4x4<T>{
				cos(y), 0, -sin(y), 0,
					0, 1.f, 0, 0,
					sin(y), 0, cos(y), 0,
					0, 0, 0, 1.f
		};

		Mat4x4<T> Rz = Mat4x4<T>{
			cos(z), sin(z), 0, 0,
				-sin(z), cos(z), 0, 0,
				0, 0, 1.f, 0,
				0, 0, 0, 1.f
		};
		return Rz * Rx * Ry;
	}

	template<typename T>
	inline Mat4x4<T> Rotate(const Vec3<T>& v)
	{
		Mat4x4<T> Rx = Mat4x4<T>{
			1.f, 0, 0, 0,
				0, cos(v.x), sin(v.x), 0,
				0, -sin(v.x), cos(v.x), 0,
				0, 0, 0, 1.f
		};

		Mat4x4<T> Ry = Mat4x4<T>{
				cos(v.y), 0, -sin(v.y), 0,
					0, 1.f, 0, 0,
					sin(v.y), 0, cos(v.y), 0,
					0, 0, 0, 1.f
		};

		Mat4x4<T> Rz = Mat4x4<T>{
			cos(v.z), sin(v.z), 0, 0,
				-sin(v.z), cos(v.z), 0, 0,
				0, 0, 1.f, 0,
				0, 0, 0, 1.f
		};
		return Rz * Rx * Ry;
	}

	//缩放
	template<typename T>
	inline Mat4x4<T> Scale(T x, T y, T z)
	{
		return Mat4x4<T>{
			x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, 1
		};
	}

	//缩放
	template<typename T>
	inline Mat4x4<T> Scale(const Vec3<T>& v)
	{
		return Mat4x4<T>{
			v.x, 0, 0, 0,
				0, v.y, 0, 0,
				0, 0, v.z, 0,
				0, 0, 0, 1
		};
	}

	//view 矩阵
	template<typename T>
	inline Mat4x4<T> View(const Vec3<T>& position, const Vec3<T>& front, const Vec3<T>& up)
	{
		Vec3<T> f = front.normalize();
		Vec3<T> u = up.normalize();
		Vec3<T> right = f.cross(u);

		return Mat4x4<T>{
			right.x, right.y, right.z, 0,
				u.x, u.y, u.z, 0,
				-f.x, -f.y, -f.z, 0,
				0, 0, 0, 1
		} *Mat4x4<T>{
			1, 0, 0, -position.x,
				0, 1, 0, -position.y,
				0, 0, 1, -position.z,
				0, 0, 0, 1
		};
	}

	//相机矩阵
	template<typename T>
	inline Mat4x4<T> LookAt(const Vec3<T>& position, const Vec3<T>& target, const Vec3<T>& up)
	{
		Vec3<T> f = (target - position).normalize();
		Vec3<T> u = up.normalize();
		Vec3<T> right = f.cross(u);

		return Mat4x4<T>{
			right.x, right.y, right.z, 0,
				u.x, u.y, u.z, 0,
				-f.x, -f.y, -f.z, 0,
				0, 0, 0, 1
		} *Mat4x4<T>{
			1, 0, 0, -position.x,
				0, 1, 0, -position.y,
				0, 0, 1, -position.z,
				0, 0, 0, 1
		};
	}

	//正交
	template<typename T>
	inline Mat4x4<T> Ortho(T left, T right, T bottom, T top, T _near, T _far)
	{
		T dx = right - left;
		T dy = top - bottom;
		T dz = _far - _near;
		T a = 2 / dx;
		T b = -(right + left) / dx;
		T c = 2 / dy;
		T d = -(top + bottom) / dy;
		T e = -1 / dz;
		T f = -_near / dz;
		return Mat4x4<T>{
			a, 0, 0, b,
				0, c, 0, d,
				0, 0, e, f,
				0, 0, 0, 1
		};
	}

	//透视矩阵-定义平截头体
	template<typename T>
	inline Mat4x4<T> Frustum(T left, T right, T bottom, T top, T _near, T _far)
	{
		T dx = right - left;
		T dy = top - bottom;
		T dz = _far - _near;
		T a = 2 * _near / dx;
		T b = (right + left) / dx;
		T c = 2 * _near / dy;
		T d = (top + bottom) / dy;
		T e = -_far / dz;
		T f = -_far * _near / dz;
		return Mat4x4<T>{
			a, 0, b, 0,
				0, c, d, 0,
				0, 0, e, f,
				0, 0, -1, 0
		};
	}

	//透视矩阵
	template<typename T>
	inline Mat4x4<T> Projection(T fovy, T aspect, T _near, T _far)
	{
		T dz = _far - _near;
		T b = 1 / tan(fovy / 2);
		T a = b / aspect;
		T c = -_far / dz;
		T d = -_near * _far / dz;
		return Mat4x4<T>{
			a, 0, 0, 0,
				0, b, 0, 0,
				0, 0, c, d,
				0, 0, -1, 0
		};
	}
};
