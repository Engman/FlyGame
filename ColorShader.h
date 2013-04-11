#ifndef COLORSHADER_H
#define COLORSHADER_H

#include "..\IShader.h"
#include "..\D3DShell.h"

class ColorShader : public IShader
{
public:
	ColorShader();

	void draw(SHADER_PARAMETER_DATA& drawData);

private:

};

#endif