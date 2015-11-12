#include "OLabel.h"

namespace Origami {

	OLabel::OLabel(const std::string& text, float x, float y, uint color)
		: m_text(text), m_Font(OFontManager::Get("SourceSansPro"))
	{
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;
	}

	OLabel::OLabel(const std::string& text, float x, float y, OFont* font, uint color)
		: m_text(text), m_Font(font)
	{
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;
	}

	OLabel::OLabel(const std::string& text, float x, float y, const std::string& font, uint color)
		: m_text(text), m_Font(OFontManager::Get(font))
	{
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;

		ValidateFont(font);
	}

	OLabel::OLabel(const std::string& text, float x, float y, const std::string& font, uint size, uint color)
		: m_text(text), m_Font(OFontManager::Get(font, size))
	{
		m_Position = maths::vec3(x, y, 0.0f);
		m_Color = color;

		ValidateFont(font, size);
	}

	void OLabel::Submit(ORenderer2D* renderer) const
	{
		renderer->DrawString(m_text, m_Position, *m_Font, m_Color);
	}

	void OLabel::ValidateFont(const std::string& name, int size)
	{
		if (m_Font != nullptr)
			return;

		std::cout << "NULL FONT! Font=" << name;
		if (size > 0)
			std::cout << ", Size=" << size;
		std::cout << std::endl;

		m_Font = OFontManager::Get("SourceSansPro");
	}


}