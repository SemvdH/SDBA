#pragma once

#include <string>
#include "../models/model.h"

namespace render_engine
{
	/*
	 * @brief: This function retrieves an .obj file, loads it into the VBO and returns a RawModel
	 *
	 * @param file_name: The path to the .obj file
	 */
	models::RawModel LoadObjModel(std::string file_name);
}