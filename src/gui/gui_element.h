#pragma once

#include "../toolbox/toolbox.h"
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

		GuiTexture(int texture, glm::vec2 position, glm::vec2 scale): texture(texture), position(position), scale(scale)
		{
			scale.x /= (WINDOW_WIDTH / WINDOW_HEIGT);
		}
	};


	/*
	 * This class represents a gui item which can be interacted with
	 */
	class InteractableGui : public GuiTexture
	{
	private:
		int default_texture;
		int clicked_texture = 0;
		int hover_texture = 0;

		bool is_hovering = false;
		bool is_clicking = false;

		glm::vec2 minXY;
		glm::vec2 maxXY;
		
	public:
		InteractableGui(int default_texture, glm::vec2 position, glm::vec2 scale);

		void Update(GLFWwindow* window);

		virtual void OnClick() = 0;
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;

		void SetClickedTexture(int texture) { clicked_texture = texture; }
		void SetHoverTexture(int texture) { hover_texture = texture; }
	
	private:
		bool IsHoveringAbove(GLFWwindow* window);
	};
	
	/*
	 * This class represents a button
	 */
	class Button : public InteractableGui
	{
	private:
		void (*on_click_action)();
		void (*on_enter_action)();
		void (*on_exit_action)();

	public:
		Button(int default_texture, glm::vec2 position, glm::vec2 scale) : InteractableGui(default_texture, position, scale) {}

		void SetOnClickAction(void (*fun)()) { on_click_action = fun; }
		void SetOnEnterAction(void (*fun)()) { on_enter_action = fun; }
		void SetOnExitAction(void (*fun)()) { on_exit_action = fun; }
	
	protected:
		void OnClick() override { if (on_click_action != nullptr) on_click_action(); }
		void OnEnter() override { if (on_enter_action != nullptr) on_enter_action(); }
		void OnExit() override { if (on_exit_action != nullptr) on_exit_action(); }
	};
}
