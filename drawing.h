#ifndef DRAWING_H
#define DRAWING_H

#include <cairo/cairo.h>
#include "utils.h"
#include <jansson.h>


void draw_line(cairo_t *context, Point * content, Color color, float lineThickness, float RAIO);
    
void create_point(cairo_t *context, Point *content, Color color,float RAIO, float lineThickness);

void drawAxisX(cairo_t *context, int width, int height, float axisThickness);

void drawAxisY(cairo_t *context, int width, int height, float axisThickness);

void draw_area(cairo_t *context, Point *content, Color color,int height);

void text(const char * chartText, cairo_t *context, Color color, int width, int height);
    
#endif
