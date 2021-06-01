#pragma once

namespace toolbox
{
	/*
	 * This class represents a timer which needs to be updated
	 * every frame to work correctly.
	 */
	class Timer
	{
	private:
		float current_time;
		float final_time;
		bool has_finished;

	public:
		/*
		 * @brief: Constructor to make the timer
		 *
		 * @param final_time: The time which the timer needs to count to
		 */
		Timer(float final_time): current_time(0), final_time(final_time), has_finished(false) {}

		/*
		 * @brief: Updates the timer. Call this method once every iteration in the game loop
		 *
		 * @param delta: The deltatime of the game
		 */
		void UpdateTimer(const double delta)
		{
			current_time += delta;
			
			if (current_time >= final_time)
			{
				has_finished = true;
			}
		}

		/*
		 * @brief: Returns if the timer has finished
		 *
		 * @return: True if the timer has finished 
		 */
		bool HasFinished() const { return has_finished; }
	};
}