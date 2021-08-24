#pragma once
#include "Graphics.h"
#include "Macros/ConditionalNoexcept.h"

namespace Bind
{
	class Bindable
	{
	public:
		virtual void Bind(Graphics& gfx) noexcept = 0;
		virtual ~Bindable() = default;
	protected:
		static ID3D11DeviceContext* GetContext(Graphics& gfx) noexcept;
		static ID3D11Device* GetDevice(Graphics& gfx) noexcept;
		static DXGIInfoManager& GetInfoManager(Graphics& gfx) noxnd;
	};
}