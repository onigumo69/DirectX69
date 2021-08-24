#pragma once
#include "Bindable/Bindable.h"
#include "Vertex.h"

namespace Bind
{
	class InputLayout : public Bindable
	{
	public:
		InputLayout(Graphics& gfx,
			meta::VertexLayout layout,
			ID3DBlob* pVertexShaderBytecode);
		void Bind(Graphics& gfx) noexcept override;
		static std::shared_ptr<InputLayout> Resolve(Graphics& gfx,
			const meta::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode);
		static std::string GenerateUID(const meta::VertexLayout& layout, ID3DBlob* pVertexShaderBytecode = nullptr);
		std::string GetUID() const noexcept override;
	protected:
		meta::VertexLayout layout;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
	};
}