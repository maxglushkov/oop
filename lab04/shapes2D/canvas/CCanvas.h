#pragma once
#include "ICanvas.h"

struct SDL_Renderer;
struct SDL_Window;

class CCanvas: public ICanvas
{
public:
	CCanvas();

	CCanvas(CCanvas &&) = delete;
	CCanvas(CCanvas const&) = delete;

	~CCanvas()override;

	CCanvas & operator =(CCanvas &&) = delete;
	CCanvas & operator =(CCanvas const&) = delete;

	void DrawLine(CPoint const& from, CPoint const& to, uint32_t lineColor)override;

	void FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor)override;

	void DrawCircle(CPoint const& center, double radius, uint32_t lineColor)override;

	void FillCircle(CPoint const& center, double radius, uint32_t fillColor)override;

	void DisplayAndPause();

private:
	SDL_Window * m_window;
	SDL_Renderer * m_renderer;
};
