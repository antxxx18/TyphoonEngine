#pragma once

namespace TE
{
	class RenderState
	{
	public:
		RenderState(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pImmediateContext);

		bool Init();
		void Close();

		void TurnZBufferOn();
		void TurnZBufferOff();

		void TurnOnAlphaBlending();
		void TurnOffAlphaBlending();

	private:
		bool CreateDepthStencilState();
		bool CreateBlendingState();
		bool CreateSamplerState();

		ID3D11Device* m_pd3dDevice;
		ID3D11DeviceContext* m_pImmediateContext;

		ID3D11DepthStencilState* m_pDepthEnableStencilState;
		ID3D11DepthStencilState* m_pDepthDisabledStencilState;
		ID3D11BlendState* m_pAlphaEnableBlendingState;
		ID3D11BlendState* m_pAlphaDisableBlendingState;

		ID3D11SamplerState* m_pSampleState;

		bool m_isDepthEnable;
		bool m_isAlphaEnable;
	};

}