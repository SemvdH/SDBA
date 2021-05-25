#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace gui
{
	/*
	 * Structure for representing a gui item to display on the screen
	 *
	 * texture  = The texture for the gui
	 * position = The center position of the gui
	 * scale    = The size (scale) of the gui
	 */
	struct GuiTexture
	{
		int texture;
		glm::vec2 position;
		glm::vec2 scale;
	};
}
