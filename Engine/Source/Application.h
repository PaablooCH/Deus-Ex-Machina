#pragma once

#include<list>
#include "Globals.h"
#include "Module.h"

class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;
class ModuleProgram;
class ModuleRenderExercise;
class ModuleEditor;
class ModuleDebugDraw;
class ModuleCamera;
class ModuleTexture;

class Application
{
public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleProgram* program = nullptr;
	ModuleRenderExercise* exercise = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleDebugDraw* debugdraw = nullptr;
	ModuleCamera* camera = nullptr;
	ModuleTexture* texture = nullptr;

	float deltaTime;

private:

	std::list<Module*> modules;
	long lastTime;

};

extern Application* App;