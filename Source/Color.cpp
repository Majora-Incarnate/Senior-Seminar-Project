#include "Color.h"



Color::Color(float r_, float g_, float b_, float a_ = 1)
	: r(r_), g(g_), b(b_), a(a_)
{
	Check_Bounds();
}

Color::Color()
	: r(1), g(1), b(1), a(1)
{}

Color::Color(const Color & c)
	: r(c.r), g(c.g), b(c.b), a(c.a)
{}


void Color::set(float r_, float g_, float b_, float a_ = 1) {
	r = r_; g = g_; b = b_; a = a_;
}

void Color::randomize()
{
	r = rand() / (float)RAND_MAX;
	g = rand() / (float)RAND_MAX;
	b = rand() / (float)RAND_MAX;
	a = rand() / (float)RAND_MAX;
}

void Color::Check_Bounds() {
	r > 1 ? 1 : r;
	g > 1 ? 1 : g;
	b > 1 ? 1 : b;
	a > 1 ? 1 : a;

	r < 0 ? 0 : r;
	g < 0 ? 0 : g;
	b < 0 ? 0 : b;
	a < 0 ? 0 : a;
}


Color Color::operator+(const Color & n) const {
	return Color(r + n.r, g + n.g, b + n.b, a + n.a);
}

Color Color::operator+(float n) const {
	return Color(r + n, g + n, b + n);
}

Color Color::operator-(const Color & n) const {
	return Color(r - n.r, g - n.g, b - n.b, a - n.a);
}

Color Color::operator-(float n) const {
	return Color(r - n, g - n, b - n);
}

Color Color::operator*(const Color & n) const {
	return Color(r * n.r, g * n.g, b * n.b, a * n.a);
}

Color Color::operator*(float n) const {
	return Color(r * n, g * n, b * n);
}

Color Color::operator/(const Color & n) const {
	return Color(r / n.r, g / n.g, b / n.b, a / n.a);
}

Color Color::operator/(float n) const {
	return Color(r / n, g / n, b / n);
}

Color & Color::operator+=(const Color & n) {
	r += n.r;
	g += n.g;
	b += n.b;
	a += n.a;
	Check_Bounds();

	return *this;
}

Color & Color::operator+=(float n) {
	r += n;
	g += n;
	b += n;
	Check_Bounds();

	return *this;
}

Color & Color::operator-=(const Color & n) {
	r -= n.r;
	g -= n.g;
	b -= n.b;
	a -= n.a;
	Check_Bounds();

	return *this;
}

Color & Color::operator-=(float n) {
	r -= n;
	g -= n;
	b -= n;
	Check_Bounds();

	return *this;
}

Color & Color::operator*=(const Color & n) {
	r *= n.r;
	g *= n.g;
	b *= n.b;
	a *= n.a;
	Check_Bounds();

	return *this;
}

Color & Color::operator*=(float n) {
	r *= n;
	g *= n;
	b *= n;
	Check_Bounds();

	return *this;
}

Color & Color::operator/=(const Color & n) {
	r /= n.r;
	g /= n.g;
	b /= n.b;
	a /= n.a;
	Check_Bounds();

	return *this;
}

Color & Color::operator/=(float n) {
	r /= n;
	g /= n;
	b /= n;
	Check_Bounds();

	return *this;
}