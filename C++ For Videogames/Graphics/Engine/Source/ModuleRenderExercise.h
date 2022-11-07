#pragma once
#include "Module.h"
#include "MathGeoLib/Math/float4x4.h"

class ModuleRenderExercise : public Module
{
public:
	ModuleRenderExercise();
	~ModuleRenderExercise();
	
	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
private:
	int program;
	unsigned vbo;
	Frustum* frustum;
};

