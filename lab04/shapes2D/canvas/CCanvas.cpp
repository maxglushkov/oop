#include <SDL2/SDL2_gfxPrimitives.h>
#include "CCanvas.h"

inline uint32_t BgrToRgba(uint32_t bgr);

[[noreturn]] static void ThrowSDLError();

CCanvas::CCanvas()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ThrowSDLError();
	}

	if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_OPENGL, &m_window, &m_renderer) < 0)
	{
		SDL_Quit();
		ThrowSDLError();
	}
}

CCanvas::~CCanvas()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void CCanvas::DrawLine(CPoint const& from, CPoint const& to, uint32_t lineColor)
{
	if (::lineColor(m_renderer, from.x, from.y, to.x, to.y, BgrToRgba(lineColor)) < 0)
	{
		ThrowSDLError();
	}
}

void CCanvas::FillPolygon(std::vector<CPoint> const& points, uint32_t fillColor)
{
	const size_t nCoords = points.size();
	Sint16 *xCoords = new Sint16[2 * nCoords];
	Sint16 *yCoords = xCoords + nCoords;
	for (CPoint const& point: points)
	{
		*xCoords++ = point.x;
		*yCoords++ = point.y;
	}
	xCoords -= nCoords;
	yCoords -= nCoords;

	if (filledPolygonColor(m_renderer, xCoords, yCoords, nCoords, BgrToRgba(fillColor)) < 0)
	{
		delete[] xCoords;
		ThrowSDLError();
	}
	delete[] xCoords;
}

void CCanvas::DrawCircle(CPoint const& center, double radius, uint32_t lineColor)
{
	if (circleColor(m_renderer, center.x, center.y, radius, BgrToRgba(lineColor)) < 0)
	{
		ThrowSDLError();
	}
}

void CCanvas::FillCircle(CPoint const& center, double radius, uint32_t fillColor)
{
	if (filledCircleColor(m_renderer, center.x, center.y, radius, BgrToRgba(fillColor)) < 0)
	{
		ThrowSDLError();
	}
}

void CCanvas::DisplayAndPause()
{
	SDL_RenderPresent(m_renderer);

	SDL_Event event;
	while (SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			return;
		}
	}
}

uint32_t BgrToRgba(uint32_t bgr)
{
	return ((bgr >> 16) & 0xff) | (bgr & 0xff00) | ((bgr & 0xff) << 16) | 0xff000000;
}

static void ThrowSDLError()
{
	throw std::runtime_error(SDL_GetError());
}
