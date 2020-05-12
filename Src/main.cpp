#include "Platform/Platform.h"
#include "Renderer/Renderer.h"
#include "Thread/RenderThread.h"
#include "Logic/Logic.h"
#include "Input/Input.h"
#include "Input/UserManager.h"

int main(int argc, char* args[]) {

	srand((unsigned int)time(NULL));

	UserManager::init();
	Input::init();
	Platform::Init();

	Renderer::Init();
	Logic::init();

	//Inicializa la hebra de renderizado
	RenderThread rT;
	rT.start();
	bool ended = false;

	//Bucle principal del juego
	while (!Platform::Tick()) {
		if (rT.getFrameOffset() <= 2) {
			UserManager::Tick();
			Input::Tick();
			Logic::Tick();
			Logic::Render(&rT);
		}//If frame offset
		if(Logic::GetRestart())
			Logic::Restart();
	}//Bucle principal
	rT.stop();
	Logic::Release();
	Renderer::Release();
	Platform::Release();
	UserManager::release();
	Input::release();
	
	return 0;
}