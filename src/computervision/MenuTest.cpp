#include "MenuTest.h"
#include <iostream>

namespace computervision 
{
	int menu_item_array[4] = { 1, 2, 3, 4 };
	float item_number = 0;

	MenuTest::MenuTest(void) {
		
	}

	int MenuTest::GetMenuItem(bool hand_state) {
		item_number += 0.20f;

		
		int temp_item_number = item_number;
		//If temp_item_number is equal to the size of the array, set item_number bac to zero to loop through the array again
		if (temp_item_number == sizeof(menu_item_array) / sizeof(menu_item_array[0])) {
			item_number = 0;
		}

		return menu_item_array[temp_item_number];
	}
}