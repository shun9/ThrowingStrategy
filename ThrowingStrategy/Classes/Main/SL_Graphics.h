//************************************************/
//* @file  :SL_Graphics.h
//* @brief :DirectX関連
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
		//全体で１つ
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		IDXGISwapChain* m_swapChain;
		ID3D11RenderTargetView* m_recderTargetView;
		ID3D11DepthStencilView* m_depthStencilView;
		ID3D11Texture2D* m_texture2D;

	public:
		ID3D11Device* Device() { return m_device; }
		ID3D11DeviceContext* DeviceContext() { return m_deviceContext; }

		//DirectX関連の初期化
		HRESULT InitD3D();

		//画面クリア
		void Clear();

		//バックバッファとフロントバッファを交換
		void Present();

		//頂点シェーダと頂点インプットレイアウトを作成
		HRESULT CreateVertexShader(
			const wchar_t* fileName,
			const char* entryPoint,
			const char* target,
			ID3D11VertexShader** vs,
			const D3D11_INPUT_ELEMENT_DESC layout[],
			const UINT& layoutSize,
			ID3D11InputLayout** il);

		//ピクセルシェーダーを作成
		HRESULT CreatePixleShader(
			const wchar_t* fileName,
			const char* entryPoint,
			const char* target,
			ID3D11PixelShader** ps);

		//コンスタントバッファを作成
		HRESULT CreateConstantBuffer(
			D3D11_BUFFER_DESC* cd,
			ID3D11Buffer** buf);

		//バーテックスバッファを作成
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