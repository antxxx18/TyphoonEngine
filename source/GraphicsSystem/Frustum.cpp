#include "stdafx.h"
#include "Frustum.h"

namespace TE
{

	void Frustum::ConstructFrustum(float screenDepth, CXMMATRIX projectionMatrix, CXMMATRIX viewMatrix)
	{
		XMMATRIX projMatrix = projectionMatrix;
		
		float zMinimum = -projMatrix._43 / projMatrix._33;
		float r = screenDepth / (screenDepth - zMinimum);
		projMatrix._33 = r;
		projMatrix._43 = -r * zMinimum;

		XMMATRIX matrix = XMMatrixMultiply(viewMatrix, projMatrix);

		float a, b, c, d;

		a = matrix._14 + matrix._13;
		b = matrix._24 + matrix._23;
		c = matrix._34 + matrix._33;
		d = matrix._44 + matrix._43;
		m_planes[0] = XMVectorSet(a, b, c, d);
		m_planes[0] = XMPlaneNormalize(m_planes[0]);

		a = matrix._14 - matrix._13;
		b = matrix._24 - matrix._23;
		c = matrix._34 - matrix._33;
		d = matrix._44 - matrix._43;
		m_planes[1] = XMVectorSet(a, b, c, d);
		m_planes[1] = XMPlaneNormalize(m_planes[1]);

		a = matrix._14 + matrix._11;
		b = matrix._24 + matrix._21;
		c = matrix._34 + matrix._31;
		d = matrix._44 + matrix._41;
		m_planes[2] = XMVectorSet(a, b, c, d);
		m_planes[2] = XMPlaneNormalize(m_planes[2]);

		a = matrix._14 - matrix._11;
		b = matrix._24 - matrix._21;
		c = matrix._34 - matrix._31;
		d = matrix._44 - matrix._41;
		m_planes[3] = XMVectorSet(a, b, c, d);
		m_planes[3] = XMPlaneNormalize(m_planes[3]);

		a = matrix._14 - matrix._12;
		b = matrix._24 - matrix._22;
		c = matrix._34 - matrix._32;
		d = matrix._44 - matrix._42;
		m_planes[4] = XMVectorSet(a, b, c, d);
		m_planes[4] = XMPlaneNormalize(m_planes[4]);

		a = matrix._14 + matrix._12;
		b = matrix._24 + matrix._22;
		c = matrix._34 + matrix._32;
		d = matrix._44 + matrix._42;
		m_planes[5] = XMVectorSet(a, b, c, d);
		m_planes[5] = XMPlaneNormalize(m_planes[5]);
	}

	bool Frustum::CheckPoint(float x, float y, float z)
	{
		for (int i = 0; i < 6; i++)
		{
			float ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet(x, y, z, 1.0f)));
			if (ret < 0.0f)
				return false;
		}

		return true;
	}


	bool Frustum::CheckCube(float xCenter, float yCenter, float zCenter, float size)
	{
		for (int i = 0; i < 6; i++)
		{
			float ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter - size), (yCenter - size), (zCenter - size), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter + size), (yCenter - size), (zCenter - size), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter - size), (yCenter + size), (zCenter - size), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter + size), (yCenter + size), (zCenter - size), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter - size), (yCenter - size), (zCenter + size), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter + size), (yCenter - size), (zCenter + size), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter - size), (yCenter + size), (zCenter + size), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter + size), (yCenter + size), (zCenter + size), 1.0f)));
			if (ret >= 0.0f)
				continue;

			return false;
		}

		return true;
	}

	bool Frustum::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
	{
		for (int i = 0; i < 6; i++)
		{
			float ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet(xCenter, yCenter, zCenter, 1.0f)));
			if (ret < -radius)
				return false;
		}

		return true;
	}

	bool Frustum::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
	{
		for (int i = 0; i < 6; i++)
		{
			float ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter - xSize), (yCenter - ySize), (zCenter - zSize), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter + xSize), (yCenter - ySize), (zCenter - zSize), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter - xSize), (yCenter + ySize), (zCenter - zSize), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter - xSize), (yCenter - ySize), (zCenter + zSize), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter + xSize), (yCenter + ySize), (zCenter - zSize), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter + xSize), (yCenter - ySize), (zCenter + zSize), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter - xSize), (yCenter + ySize), (zCenter + zSize), 1.0f)));
			if (ret >= 0.0f)
				continue;

			ret = XMVectorGetX(XMPlaneDotCoord(m_planes[i], XMVectorSet((xCenter + xSize), (yCenter + ySize), (zCenter + zSize), 1.0f)));
			if (ret >= 0.0f)
				continue;

			return false;
		}

		return true;
	}

}