#pragma once

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "../toolbox/toolbox.h"
#include "gui_element.h"
#include <functional>

namespace gui
{
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

		/*
		 * @brief: Call this function every frame
		 *
		 * @param window: An openGL window
		 */
		void Update(GLFWwindow* window);

		/*
		 * @brief: Call this function when you want to perform a mouseclick
		 *
		 * @param mousebutton: mouseButton you want to perform the click on
		 */
		void ForceClick(int mouseButton);

		
		/*
		 * @brief: This function gets called when the InteractabeGui is clicked
		 */
		virtual void OnClick() = 0;

		/*
		 * @brief: This function gets called when the mouse starts hovering above the InteractableGUI
		 */
		virtual void OnEnter() = 0;

		/*
		 * @brief: This function gets called when the mouse stops hovering above the InteractableGUI
		 */
		virtual void OnExit() = 0;

		/*
		 * @brief: This function sets the texture of the InteractableGUI for when the InteractableGUI is clicked
		 */
		void SetClickedTexture(int texture)
		{
			clicked_texture = texture;
		}

		/*
		 * @brief: This function sets the texture of the InteractableGUI for when the mouse is hovering above the InteractableGUI
		 */
		void SetHoverTexture(int texture) { hover_texture = texture; }

	private:
		/*
		 * @brief: This function checks if the mouse is hovering above the InteractableGUI
		 *
		 * @param window: An openGL window
		 *
		 * @return: True or false
		 */
		bool IsHoveringAbove(GLFWwindow* window);
	};


	
	/*
 * This class represents a button
 */
	class Button : public InteractableGui
	{
	private:

		std::function<void()> on_click_action;
		std::function<void()> on_enter_action;
		std::function<void()> on_exit_action;

	public:
		Button(int default_texture, glm::vec2 position, glm::vec2 scale) : InteractableGui(default_texture, position, scale) {}

		/*
		 * @brief: This function sets an action (function pointer) to the OnClick function
		 *
		 * @param fun: A function pointer to a function (or lambda)
		 */
		void SetOnClickAction(std::function<void()> fun) { on_click_action = fun; }

		/*
		 * @brief: This function sets an action (function pointer) to the OnEnter function
		 *
		 * @param fun: A function pointer to a function (or lambda)
		 */
		void SetOnEnterAction(std::function<void()> fun) { on_enter_action = fun; }

		/*
		 * @brief: This function sets an action (function pointer) to the OnExit function
		 *
		 * @param fun: A function pointer to a function (or lambda)
		 */
		void SetOnExitAction(std::function<void()> fun) { on_exit_action = fun; }

		GuiType GetType() override {
			return GuiType::BUTTON;
		}

	protected:
		void OnClick() override { if (on_click_action != nullptr) on_click_action(); }
		void OnEnter() override { if (on_enter_action != nullptr) on_enter_action(); }
		void OnExit() override { if (on_exit_action != nullptr) on_exit_action(); }
	};
}
