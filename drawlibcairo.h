#ifndef _DRAW_LIB_CAIRO_H
#define _DRAW_LIB_CAIRO_H

#include <cairo/cairo.h>
#include "drawlib.h"

///Drawing with a cairo back end
class DrawLibCairo : public LocalStore
{
protected:
	cairo_t *cr;
	cairo_surface_t *surface;
	cairo_surface_t *maskSurface;
	std::map<std::string, cairo_surface_t *> imageResources;

	virtual void DrawCmdPolygons(class DrawPolygonsCmd &polygons);
	virtual void DrawCmdLines(class DrawLinesCmd &linesCmd);
	virtual void DrawCmdText(class DrawTextCmd &textCmd);
	virtual void DrawCmdTwistedText(class DrawTwistedTextCmd &textCmd);
	virtual void LoadResources(class LoadImageResourcesCmd &resourcesCmd);
	virtual void UnloadResources(class UnloadImageResourcesCmd &resourcesCmd);

	void CreateMaskSurface(double width, double height);
	void SetPolySource(const class ShapeProperties &properties);
public:
	DrawLibCairo(cairo_surface_t *surface);
	virtual ~DrawLibCairo();

	void Draw();
	int GetTriangleBoundsText(const TextLabel &label, const class TextProperties &properties, 
		TwistedTriangles &trianglesOut);
	int GetDrawableExtents(double &x1,
		double &y1,
		double &x2,
		double &y2);
	int GetResourceDimensionsFromFilename(const std::string &filename, unsigned &widthOut, unsigned &heightOut);
};

class DrawLibCairoPango : public DrawLibCairo
{
protected:
	void DrawCmdText(class DrawTextCmd &textCmd);
	void DrawCmdTwistedText(class DrawTwistedTextCmd &textCmd);

public:
	DrawLibCairoPango(cairo_surface_t *surface);
	virtual ~DrawLibCairoPango();

	int GetTriangleBoundsText(const TextLabel &label, const class TextProperties &properties, 
		TwistedTriangles &trianglesOut);
	int GetTriangleBoundsTwistedText(const TwistedTextLabel &label, 
		const class TextProperties &properties, 
		TwistedTriangles &trianglesOut, double &pathLenOut, double &textLenOut);
};

#endif //_DRAW_LIB_CAIRO_H
