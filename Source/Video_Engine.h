#ifndef VIDEO_ENGINE_H
#define VIDEO_ENGINE_H



#include <cmath>

#include "Color.h"



class Texture {};
class Text {};



static const int SMOOTH_FACTOR = 100;



class Video_Engine {
public:
	static bool Setup();
	static void Cleanup();

	static void Draw(Texture *) {}
	static void Draw(Text *) {}

	static void DrawLine(float, float, float, float, const Color * color = NULL);
	static void DrawRect(float, float, float, float, const Color * color = NULL);
	static void DrawPolygon(float, float, float, int, float, const Color * color = NULL);
	static void DrawCircle(float, float, float, const Color * color = NULL);
	static void DrawCircleSection(float, float, float, float, float, const Color * color = NULL);
	static void DrawText(float, float, float, float, const char *, TTF_Font *, const Color * color = NULL);

private:	
};



#endif