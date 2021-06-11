
namespace computervision
{
	class MenuTest {
	public:
		/**
		 * @brief Constructor for the class MenuTest, loads in array with menu items
		 *
		 */
		MenuTest(void);
		/**
		 * @brief Returns the itemnumber in an array 
		 * 
		 * @param input_bool is either true or false, depending on the recognized hand gesture
		 */
		int GetMenuItem(bool input_bool);
	};
}