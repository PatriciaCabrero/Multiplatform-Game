#include "RenderThread.h"
#include "..\Config.h"

RenderThread::RenderThread()
{
	frameOffset = 0;
	TAM_X_CELLS = Renderer::GetWidth() / X_CELLS;
	TAM_Y_CELLS = Renderer::GetHeight() / Y_CELLS;
}

RenderThread::~RenderThread()
{
	while (_commands.getSize() == 0)
	{
		_commands.pop();
	}
}

void RenderThread::start()
{
	_running = true;
	t = thread(&RenderThread::render, this);
}

void RenderThread::stop() {
	_running = false;
	t.join();
}
void RenderThread::enqClear(Color color)
{
	_cmd.init(CommandType::Clear, color);
	_commands.push(_cmd);
}

void RenderThread::enqPPixel(int x, int y, Color color)
{
	_cmd.init(CommandType::PutPixel, color, x, y);
	_commands.push(_cmd);
}

void RenderThread::enqDLine(int x, int y, int h, int w, Color color)
{
	_cmd.init(CommandType::DrawLine, color, x, y, w, h);
	_commands.push(_cmd);
}

void RenderThread::enqDCell(int x, int y, Color color)
{
	_cmd.init(CommandType::DrawCell, color, x, y);
	_commands.push(_cmd);
}

void RenderThread::enqEndFrame()
{
	_cmd.init(CommandType::EndFrame);
	_commands.push(_cmd);
	frameOffset++;
}


void RenderThread::render()
{
	while (_running) {
		Command act;
		_commands.pop(act);
		switch (act._type)
		{
		case CommandType::Clear:
			Renderer::Clear(act.dClear.color);
			break;
		case CommandType::PutPixel:
			Renderer::PutPixel(act.dpp.x, act.dpp.y, act.dpp.color);
			break;
		case CommandType::DrawLine:
			Renderer::DrawLine(act.dLine.x*TAM_X_CELLS, act.dLine.y*TAM_X_CELLS, act.dLine.length*TAM_X_CELLS, act.dLine.height*TAM_X_CELLS, act.dLine.color);
			break;
		case CommandType::DrawCell:
			Renderer::DrawLine(act.dCell.x*TAM_X_CELLS, act.dCell.y*TAM_Y_CELLS, TAM_X_CELLS, TAM_Y_CELLS, act.dCell.color);
			break;
		case CommandType::EndFrame:
			Renderer::Present();
			frameOffset--;
			break;
		default:
			break;
		}//Switch

	}//While running

}//Render metodo