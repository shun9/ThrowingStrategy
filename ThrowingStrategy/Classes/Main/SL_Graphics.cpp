//************************************************/
//* @file  :SL_Graphics.cpp
//* @brief :DirectX�֘A
//* @date  :2017/10/26
//* @author:S.Katou
//************************************************/
#include "SL_Graphics.h"

#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include "SL_Window.h"

/// <summary>
/// DirectX3D�̏�����
/// </summary>
HRESULT ShunLib::Graphics::InitD3D()
{
	auto window = ShunLib::Window::GetInstance();

	// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = (UINT)window->Width();      //��ʉ���
	sd.BufferDesc.Height = (UINT)window->Height();    //��ʏc��
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//32bit�J���[
	sd.BufferDesc.RefreshRate.Numerator = 60;         //�t���b�V�����[�g�@60fps
	sd.BufferDesc.RefreshRate.Denominator = 1;        //�o�b�N�o�b�t�@�̐�
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = window->Handle();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* featureLevel = NULL;

	auto result = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&featureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&m_swapChain,
		&m_device,
		featureLevel,
		&m_deviceContext);

	if (FAILED(result))return FALSE;


	//�X���b�v�`�F�C���������Ă���o�b�N�o�b�t�@���擾
	ID3D11Texture2D *backBuffer;
	m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	//�����_�[�^�[�Q�b�g�r���[�̍쐬
	//�����_�[�^�[�Q�b�g�ƃ��\�[�X���q�������
	m_device->CreateRenderTargetView(backBuffer, NULL, &m_recderTargetView);

	//�o�b�N�o�b�t�@�̎Q�ƃJ�E���^���P���炷
	//���j���ł͂Ȃ�
	SAFE_RELEASE(backBuffer);

	//�[�x�X�e���V���r���[�̍쐬
	//Z�o�b�t�@�ƃX�e���V���o�b�t�@�ɑ΂���r���[
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = (UINT)window->Width();
	descDepth.Height = (UINT)window->Height();
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	m_device->CreateTexture2D(&descDepth, NULL, &m_texture2D);
	m_device->CreateDepthStencilView(m_texture2D, NULL, &m_depthStencilView);

	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���p�C�v���C���Ɋ֘A�t����
	m_deviceContext->OMSetRenderTargets(1, &m_recderTargetView, m_depthStencilView);

	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)window->Width();  //��ʕ�
	vp.Height = (FLOAT)window->Height();//��ʕ�
	vp.MinDepth = 0.0f;         //Z���̕�
	vp.MaxDepth = 1.0f;         //Z���̕�
	vp.TopLeftX = 0;            //����̍��W
	vp.TopLeftY = 0;            //����̍��W
	m_deviceContext->RSSetViewports(1, &vp);

	//���X�^���C�Y�ݒ�
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));

	rd.CullMode = D3D11_CULL_NONE;
	rd.FillMode = D3D11_FILL_SOLID;

	ID3D11RasterizerState* irs = NULL;
	m_device->CreateRasterizerState(&rd, &irs);
	m_deviceContext->RSSetState(irs);
	SAFE_RELEASE(irs);

	return S_OK;
}

/// <summary>
/// �o�[�e�b�N�X�V�F�[�_�[�ƒ��_�C���v�b�g���C�A�E�g���쐬
/// </summary>
HRESULT ShunLib::Graphics::CreateVertexShader(
	const wchar_t* fileName,
	const char* entryPoint,
	const char* target,
	ID3D11VertexShader** vs,
	const D3D11_INPUT_ELEMENT_DESC layout[],
	const UINT& layoutSize,
	ID3D11InputLayout** il)
{

	//hlsl�t�@�C���ǂݍ��ݗp�u���u
	//�u���u�̎��_�ł͉��̃V�F�[�_�[�Ȃ̂�������Ȃ�
	ID3DBlob* compiledShader = NULL;
	ID3DBlob* error = NULL;

	//�o�[�e�b�N�X�V�F�[�_�[�̃u���u���쐬
	if (FAILED(D3DCompileFromFile((LPCWSTR)fileName, NULL, NULL, (LPCSTR)entryPoint, (LPCSTR)target, 0, 0, &compiledShader, &error)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(error);

	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(m_device->CreateVertexShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), NULL, vs)))
	{
		SAFE_RELEASE(compiledShader);
		return E_FAIL;
	}

	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(m_device->CreateInputLayout(layout, layoutSize, compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), il)))
	{
		SAFE_RELEASE(compiledShader);
		return E_FAIL;
	}

	SAFE_RELEASE(compiledShader);

	return S_OK;
}


/// <summary>
/// �s�N�Z���V�F�[�_�[���쐬
/// </summary>
HRESULT ShunLib::Graphics::CreatePixleShader(
	const wchar_t* fileName,
	const char* entryPoint,
	const char* target,
	ID3D11PixelShader** ps)
{
	auto window = Window::GetInstance();

	//hlsl�t�@�C���ǂݍ��ݗp�u���u
	//�u���u�̎��_�ł͉��̃V�F�[�_�[�Ȃ̂�������Ȃ�
	ID3DBlob* compiledShader = NULL;
	ID3DBlob* error = NULL;

	//�s�N�Z���V�F�[�_�[�̃u���u���쐬
	if (FAILED(D3DCompileFromFile((LPCWSTR)fileName, NULL, NULL, (LPCSTR)entryPoint, (LPCSTR)target, 0, 0, &compiledShader, &error)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(error);

	//�s�N�Z���V�F�[�_�[�쐬
	if (FAILED(m_device->CreatePixelShader(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), NULL, ps)))
	{
		SAFE_RELEASE(compiledShader);
		return E_FAIL;
	}

	SAFE_RELEASE(compiledShader);

	return S_OK;
}

/// <summary>
/// �R���X�^���g�o�b�t�@���쐬
/// </summary>
HRESULT ShunLib::Graphics::CreateConstantBuffer(D3D11_BUFFER_DESC * cd, ID3D11Buffer ** buf)
{
	if (FAILED(m_device->CreateBuffer(cd, NULL, buf)))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT ShunLib::Graphics::CreateVertexBuffer(D3D11_BUFFER_DESC * bd, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer ** buf)
{
	if (FAILED(m_device->CreateBuffer(bd, data, buf)))
	{
		return E_FAIL;

	}
	return S_OK;
}


/// <summary>
/// ��ʂ̃N���A
/// </summary>
void ShunLib::Graphics::Clear()
{
	//��ʂ̐F
	float color[4] = { 0,1,1,1 };

	//��ʃN���A
	m_deviceContext->ClearRenderTargetView(m_recderTargetView, color);

	//�[�x�o�b�t�@�N���A
	m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

/// <summary>
/// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@������
/// </summary>
void ShunLib::Graphics::Present()
{
	if (m_swapChain != nullptr)
	{
		m_swapChain->Present(0, 0);
	}
}
