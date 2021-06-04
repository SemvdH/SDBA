#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gui_interactable.h"

#include <iostream>

namespace gui
{
	InteractableGui::InteractableGui(int default_texture, glm::vec2 position, glm::vec2 scale)
		: GuiTexture(default_texture, position, scale)
	{
		this->default_texture = default_texture;

		minXY = glm::vec2(position.x - scale.x, position.y - scale.y);
		maxXY = glm::vec2(position.x + scale.x, position.y + scale.y);
	}

	void InteractableGui::Update(GLFWwindow* window)
	{
		if (IsHoveringAbove(window) && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			if (clicked_texture != 0)
			{
				texture = clicked_texture;
			}
			else
			{
				texture = default_texture;
			}

			if (!is_clicking)
			{
				OnClick();
				is_clicking = true;
			}
		}
		else
		{
			if (is_clicking)
			{
				is_clicking = false;
			}
		}
	}

	void InteractableGui::ForceClick( int mouseButton)
	{
		if(mouseButton == GLFW_MOUSE_BUTTON_LEFT)
		{
			if (clicked_texture != 0)
			{
				texture = clicked_texture;
			}
			else
			{
				texture = default_texture;
			}

			if (!is_clicking)
			{
				OnClick();
				is_clicking = true;
			}
		}
		else
		{
			if (is_clicking)
			{
				is_clicking = false;
			}
		}
		
	}
	
	bool InteractableGui::IsHoveringAbove(GLFWwindow* window)
	{
		double x_pos, y_pos;
		glfwGetCursorPos(window, &x_pos, &y_pos);

		const float x_rel = (x_pos / SCALED_WIDTH / DEFAULT_WIDTH) * 2.0f - 1.0f;
		const float y_rel = -((y_pos / SCALED_HEIGHT / DEFAULT_HEIGHT) * 2.0f - 1.0f);

		if (x_rel >= minXY.x && x_rel <= maxXY.x &&
			y_rel >= minXY.y && y_rel <= maxXY.y)
		{
			if (hover_texture != 0)
			{
				texture = hover_texture;
			}
			else
			{
				texture = default_texture;
			}

			if (!is_hovering)
			{
				OnEnter();
				is_hovering = true;
			}

			return true;
		}

		texture = default_texture;

		if (is_hovering)
		{
			OnExit();
			is_hovering = false;
		}

		return false;
	}
}
