#pragma once

#define WND_EXCEPT(hr) Window::HrException(__FILE__, __LINE__, hr)
#define WND_LAST_EXCEPT() Window::HrException(__FILE__, __LINE__, GetLastError())
#define WND_NOGFX_EXCEPT() Window::NoGfxException(__FILE__, __LINE__)