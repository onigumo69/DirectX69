#include "Bindable/InputLayout.h"
#include "Bindable/BindableCodex.h"
#include "Vertex.h"
#include "Macros/GraphicsThrowMacros.h"

namespace Bind
{
	InputLayout::InputLayout(Graphics& gfx,
		meta::VertexLayout layout_in,
		ID3DBlob* pVertexShaderBytecode)
		:
		layout{ std::move(layout_in) }
	{
		INFO_MANAGER(gfx);

		const auto d3dLayout = layout.GetD3DLayout();

		GFX_THROW_INFO(GetDevice(gfx)->CreateInputLayout(
			d3dLayout.data(), (UINT)d3dLayout.size(),
			pVertexShaderBytecode->GetBufferPointer(),
			pVertexShaderBytecode->GetBufferSize(),
			&pInputLayout
		));
	}

	void InputLayout::Bind(Graphics& gfx) noexcept
	{
		GetContext(gfx)->IASetInputLayout(pInputLayout.Get());
	}
	std::shared_ptr<InputLayout> InputLayout::Resolve(Graphics& gfx,
		const meta::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode)
	{
		return Codex::Resolve<InputLayout>(gfx, layout, pVertexShaderBytecode);
	}
	std::string InputLayout::GenerateUID(const meta::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode)
	{
		using namespace std::string_literals;
		return typeid(InputLayout).name() + "#"s + layout.GetCode();
	}
	std::string InputLayout::GetUID() const noexcept
	{
		return GenerateUID(layout);
	}
}
