#ifndef GBUFFERSHADER_H
#define GBUFFERSHADER_H

#include "IShader.h"

class GBufferShader : IShader
{
	public:
		GBufferShader();

		void draw(SHADER_PARAMETER_DATA& drawData);

	private:
		
};

#endif