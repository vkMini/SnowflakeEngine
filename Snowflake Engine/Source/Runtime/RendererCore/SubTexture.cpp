#include "sfpch.h"
#include "SubTexture.h"

namespace Snowflake {

	SubTexture2D::SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& minBound, const glm::vec2& maxBound)
		: m_Texture(texture)
	{
		m_TextureCoords[0] = { minBound.x, minBound.y };
		m_TextureCoords[1] = { maxBound.x, minBound.y };
		m_TextureCoords[2] = { maxBound.x, maxBound.y };
		m_TextureCoords[3] = { minBound.x, maxBound.y };
	}

	Ref<SubTexture2D> SubTexture2D::CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& spriteSize)
	{
		glm::vec2 min = { (coords.x * spriteSize.x) / texture->GetWidth(), (coords.y * spriteSize.y) / texture->GetHeight() };
		glm::vec2 max = { ((coords.x + 1) * spriteSize.x) / texture->GetWidth(), ((coords.y + 1) * spriteSize.y) / texture->GetHeight() };

		Ref<SubTexture2D> resultTexture = CreateRef<SubTexture2D>(texture, min, max);
		return resultTexture;
	}
	 
}