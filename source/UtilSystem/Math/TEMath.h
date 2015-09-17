#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Matrix.h"
#include "Quaternion.h"

namespace TE
{
	float const PI = 3.1415926535897932384626433832795f;
	float const PI_DIV2 = 1.5707963267948966192313216916398f;
	float const PI_DIV4 = 0.78539816339744830961566084581988f;

	inline float ToRadians(float const angel)
	{
		return angel*PI / 180.0f;
	}

	inline float ToDegrees(float const angel)
	{
		return angel*180.0f / PI;
	}

}