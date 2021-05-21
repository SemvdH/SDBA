#pragma once

#include <string>
#include "../models/model.h"

namespace render_engine
{
	/*
	 * This function retrieves an .obj file, loads it into the VBO and returns a RawModel
	 */
	models::RawModel LoadObjModel(std::string file_name);
}