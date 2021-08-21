#pragma once

// "HRESULT hr" needs to be exist in local scope for these to work

// graphics exception checking/throwing macros (some with dxgi infos)
#define GFX_EXCEPT_NOINFO(hr) Graphics::HrException(__FILE__, __LINE__, (hr))
#define GFX_THROW_NOINFO(hrcall) if(FAILED(hr = (hrcall))) throw Graphics::HrException(__FILE__, __LINE__, hr)

#ifndef NDEBUG
#define GFX_EXCEPT(hr) Graphics::HrException(__FILE__, __LINE__, (hr), infoManager.GetMessages())
#define GFX_THROW_INFO(hrcall) infoManager.Set(); if(FAILED(hr = (hrcall))) throw GFX_EXCEPT(hr)
#define GFX_THROW_INFO_ONLY(call) infoManager.Set(); (call); {auto v = infoManager.GetMessages(); if(!v.empty()) {throw Graphics::InfoException(__FILE__, __LINE__, v);}}
#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException(__FILE__, __LINE__, (hr), infoManager.GetMessages())
#else
#define GFX_EXCEPT(hr) Graphics::HrException(__FILE__, __LINE__, (hr))
#define GFX_THROW_INFO(hrcall) GFX_THROW_NOINFO(hrcall)
#define GFX_THROW_INFO_ONLY(call) (call)
#define GFX_DEVICE_REMOVED_EXCEPT(hr) Graphics::DeviceRemovedException(__FILE__, __LINE__, (hr))
#endif

// macro for importing InfoManager into local scope
// this.GetInfoManager(Graphics& gfx) must exist
#ifdef NDEBUG
#define INFO_MANAGER(gfx) HRESULT hr
#else
#define INFO_MANAGER(gfx) HRESULT hr; DXGIInfoManager& infoManager = GetInfoManager(gfx)
#endif