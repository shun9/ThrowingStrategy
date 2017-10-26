//************************************************/
//* @file  :SL_Graphics.h
//* @brief :DirectX�֘A
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <SL_Singleton.h>
#include <SL_MacroConstants.h>


namespace ShunLib {
	class Graphics :public Singleton<Graphics>
	{
		friend Singleton<Graphics>;

	private:
		//�S�̂łP��
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		IDXGISwapChain* m_swapChain;
		ID3D11RenderTargetView* m_recderTargetView;
		ID3D11DepthStencilView* m_depthStencilView;
		ID3D11Texture2D* m_texture2D;

	public:
		ID3D11Device* Device() { return m_device; }
		ID3D11DeviceContext* DeviceContext() { return m_deviceContext; }

		//DirectX�֘A�̏�����
		HRESULT InitD3D();

		//��ʃN���A
		void Clear();

		//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@������
		void Present();

		//���_�V�F�[�_�ƒ��_�C���v�b�g���C�A�E�g���쐬
		HRESULT CreateVertexShader(
			const wchar_t* fileName,
			const char* entryPoint,
			const char* target,
			ID3D11VertexShader** vs,
			const D3D11_INPUT_ELEMENT_DESC layout[],
			const UINT& layoutSize,
			ID3D11InputLayout** il);

		//�s�N�Z���V�F�[�_�[���쐬
		HRESULT CreatePixleShader(
			const wchar_t* fileName,
			const char* entryPoint,
			const char* target,
			ID3D11PixelShader** ps);

		//�R���X�^���g�o�b�t�@���쐬
		HRESULT CreateConstantBuffer(
			D3D11_BUFFER_DESC* cd,
			ID3D11Buffer** buf);

		//�o�[�e�b�N�X�o�b�t�@���쐬
		HRESULT CreateVertexBuffer(
			D3D11_BUFFER_DESC* cd,
			D3D11_SUBRESOURCE_DATA* data,
			ID3D11Buffer** buf);


	private:
		Graphics() {
		}
		~Graphics() {
			SAFE_RELEASE(m_swapChain);
			SAFE_RELEASE(m_recderTargetView);
			SAFE_RELEASE(m_deviceContext);
			SAFE_RELEASE(m_texture2D);
			SAFE_RELEASE(m_depthStencilView);
			SAFE_RELEASE(m_device);
		}
	};
}