#include "Bindable/Bindable.h"

ID3D11Device* Bindable::GetDevice(Graphics& gfx) noexcept
{
	return gfx.pDevice.Get();
}

ID3D11DeviceContext* Bindable::GetContext(Graphics& gfx) noexcept
{
	return gfx.pContext.Get();
}

DXGIInfoManager& Bindable::GetInfoManager(Graphics& gfx) noexcept(IS_DEBUG)
{
#ifndef NDEBUG
	return gfx.infoManager;
#else
	throw std::logic_error("gfx.infoManager is not allowed to access in Release build");
#endif
}