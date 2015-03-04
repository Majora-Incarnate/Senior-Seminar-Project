#include "Video_Engine.h"
#include "Application_Event.h"



bool Video_Engine::Setup() {
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glViewport(0, 0, System::window_width, System::window_height);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);

	// Antialiasing on and amount
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 3);

	//Check for error
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL: %s\n", gluErrorString(error));
		Application_Event::New_Event(APPLICATION_ERROR);
		return false;
	}

	return true;
}

void Video_Engine::Cleanup() {
	//TODO
}



void Video_Engine::DrawLine(float x1, float y1, float x2, float y2, const Color * color)
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, System::window_width, System::window_height, 0, -1, 1 );
	glTranslatef(0, 0, 0);
	glRotatef(0, 0, 0, 1);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glDisable(GL_TEXTURE_2D);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (color != NULL)
		glColor4f(color->r, color->g, color->b, color->a);

	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}



void Video_Engine::DrawRect(float x, float y, float w, float h, const Color * color)
{
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, System::window_width, System::window_height, 0, -1, 1 );
	glTranslatef(0, 0, 0);
	glRotatef(0, 0, 0, 1);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glDisable(GL_TEXTURE_2D);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (color != NULL)
		glColor4f(color->r, color->g, color->b, color->a);

	glBegin(GL_QUADS);
		glVertex2f(x, y);
		glVertex2f(x, y + h);
		glVertex2f(x + w, y + h);
		glVertex2f(x + w, y);
	glEnd();

}



void Video_Engine::DrawPolygon(float x, float y, float r, int s, float a, const Color * color) {
    int loop_iter = (s - 1) / 2;
    float div_angle = 2 * PI / s;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, System::window_width, System::window_height, 0, -1, 1 );
	glTranslatef(0, 0, 0);
	glRotatef(0, 0, 0, 1);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glDisable(GL_TEXTURE_2D);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (color != NULL)
		glColor4f(color->r, color->g, color->b, color->a);
    
    glBegin(GL_TRIANGLE_STRIP);
    
    glVertex2f(x, y + r);//sin(0) = 0 and cos(0) = 1
    
    for (int i = 0; i <= loop_iter; i++) {
        float lha = a - div_angle * i;
        float rha = a + div_angle * i;
        
        glVertex2f(x + sin(lha) * r, y + cos(lha) * r);
        glVertex2f(x + sin(rha) * r, y + cos(rha) * r);
    }
    
    if (s % 2 == 0) {
        float angle = a + div_angle * (s / 2);
        glVertex2f(x + sin(angle) * r, y + cos(angle) * r);
    }
    
    glEnd();
}



void Video_Engine::DrawCircle(float x, float y, float r, const Color * color) {
    DrawPolygon(x, y, r, SMOOTH_FACTOR, 0, color);
}



void Video_Engine::DrawCircleSection(float x, float y, float r, float sa, float ea, const Color * color) {
    sa *= (PI / 180);
    ea *= (PI / 180);
    float div_angle = (ea - sa) / SMOOTH_FACTOR;

    if (div_angle <= 0)
    	return;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, System::window_width, System::window_height, 0, -1, 1 );
	glTranslatef(0, 0, 0);
	glRotatef(0, 0, 0, 1);
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glDisable(GL_TEXTURE_2D);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (color != NULL)
		glColor4f(color->r, color->g, color->b, color->a);
    
    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(x, y);
    
    for (double i = sa; i <= ea; i += div_angle)
        glVertex2f(x - sin(i) * r, y - cos(i) * r);
    
    glEnd();
}

void Video_Engine::DrawText(float x, float y, float w, float h, const char * c, TTF_Font * font, const Color * color) {
	if (color == NULL)
		color = &WHITE;

	glColor4f(color->r, color->g, color->b, color->a);
	//LoadText(c, font, color, w, h)->DrawAtRect(x, y);
}