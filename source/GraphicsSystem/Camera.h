#pragma once

#include "UtilSystem/Timer.h"

namespace TE
{
	class Camera
	{
	public:
		Camera(float fieldOfViewY, float viewportWidth, float viewportHeight, float nearZ, float farZ);

		void Render();

		void MoveForward(bool keydown);
		void MoveBackward(bool keydown);
		void MoveLeft(bool keydown);
		void MoveRight(bool keydown);

		void MoveUpward(bool keydown);
		void MoveDownward(bool keydown);

		void RotateLeft(bool keydown);
		void RotateRight(bool keydown);

		void LookUpward(bool keydown);
		void LookDownward(bool keydown);

		void SetPos(float x, float y, float z);
		void SetRot(float x, float y, float z);

		XMFLOAT3 GetPos() { return m_pos; }
		XMFLOAT3 GetRot() { return m_rot; }

		CXMMATRIX GetViewMatrix();
		CXMMATRIX GetProjMatrix();
		CXMMATRIX GetOrtoMatrix();

		void* operator new(size_t i)
		{
			return _aligned_malloc(i,16);
		}

			void operator delete(void* p)
		{
			_aligned_free(p);
		}

	private:
		Timer m_time;
		
		XMFLOAT3 m_pos;
		XMFLOAT3 m_rot;

		XMMATRIX m_viewMatrix;
		XMMATRIX m_Ortho;
		XMMATRIX m_Projection;

		float m_frameTime;

		float m_forwardSpeed, m_backwardSpeed;
		float m_upwardSpeed, m_downwardSpeed;
		float m_leftTurnSpeed, m_rightTurnSpeed;
		float m_leftSpeed, m_rightSpeed;
		float m_lookUpSpeed, m_lookDownSpeed;
	};
}