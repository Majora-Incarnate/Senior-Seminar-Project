#ifndef COLOR_H
#define COLOR_H



#include "Math.h"
#include "System.h"



class Color {
public:
	Color();
	Color(float, float, float, float);
	Color(const Color &);

	void set(float, float, float, float);
	void randomize();

	Color operator+(const Color &) const;
	Color operator+(float) const;
	Color operator-(const Color &) const;
	Color operator-(float) const;
	Color operator*(const Color &) const;
	Color operator*(float) const;
	Color operator/(const Color &) const;
	Color operator/(float) const;
	Color & operator+=(const Color &);
	Color & operator+=(float);
	Color & operator-=(const Color &);
	Color & operator-=(float);
	Color & operator*=(const Color &);
	Color & operator*=(float);
	Color & operator/=(const Color &);
	Color & operator/=(float);

	float r, g, b, a;

private:
	void Check_Bounds();
};



static const Color RED(1, 0, 0, 1);
static const Color BLUE(0, 0, 1, 1);
static const Color GREEN(0, 1, 0, 1);
static const Color WHITE(1, 1, 1, 1);
static const Color BLACK(0, 0, 0, 1);
static const Color GRAY(0.5, 0.5, 0.5, 1);

static const Color LIGHT_BLUE(0, 0, 1, 0.5);
static const Color LIGHT_RED(1, 0, 0, 0.5);
static const Color LIGHT_GREEN(0, 1, 0, 0.5);
static const Color LIGHT_GRAY(0.5, 0.5, 0.5, 0.5);

static const Color COLLISION(1, 0, 0, 0.25);


#endif
