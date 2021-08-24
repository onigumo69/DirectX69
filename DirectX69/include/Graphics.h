#pragma once
#include "CleanWindows.h"
#include "CleanException.h"
#include "Macros/ConditionalNoexcept.h"
#include <d3d11.h>
#include <wrl.h>
#include <vector>
#include "DXGIInfoManager.h"
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <memory>
#include <random>

namespace Bind
{
	class Bindable;
}

class Graphics
{
	friend Bind::Bindable;
public:
	Graphics(HWND hWnd, int width, int height);
	Graphics(const Graphics&) = delete;
	Graphics operator=(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void BeginFrame(float red, float green, float blue) noexcept;
	void DrawIndexed(UINT count) noxnd;
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX cam) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;
	void EnableImgui() noexcept;
	void DisableImgui() noexcept;
	bool IsImguiEnabled() const noexcept;

private:
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera;
	bool imguiEnabled = true;

#ifndef NDEBUG
	DXGIInfoManager infoManager;
#endif
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDepth;

public:
	class Exception : public CleanException
	{
		using CleanException::CleanException;
	};
	class HrException : public Exception
	{
	public:
		HrException(const char* file, int line, HRESULT hr, std::vector<std::string> infoMsgs = {}) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;
		std::string GetErrorString() const noexcept;
		std::string GetErrorDescription() const noexcept;
		std::string GetErrorInfo() const noexcept;
	private:
		HRESULT hr;
		std::string info;
	};
	class InfoException : public Exception
	{
	public:
		InfoException(const char* file, int line, std::vector<std::string> infoMsgs) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorInfo() const noexcept;
	private:
		std::string info;
	};
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;
	public:
		const char* GetType() const noexcept override;
	private:
		std::string reason;
	};
};