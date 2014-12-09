#include "drawing.h"


void drawAxisY(cairo_t *context, int width, int height) {
    cairo_save(context);
    cairo_set_line_width (context, 3.0);
    cairo_set_source_rgb (context, 0, 0, 0);
    cairo_move_to(context, width * 0.10, height * 0.90);
    cairo_line_to(context, width * 0.10, height * 0.08);
    cairo_move_to(context, width * 0.12, height * 0.10);
    cairo_line_to(context, width * 0.10, height * 0.08);
    cairo_line_to(context, width * 0.08, height * 0.10);
    cairo_stroke(context);
    cairo_restore(context);
    
}

void drawAxisX(cairo_t *context, int width, int height){
    cairo_save(context);
    cairo_set_line_width (context, 3.0);
    cairo_set_source_rgb (context, 0, 0, 0);
    cairo_move_to(context, width * 0.10, height * 0.90);
    cairo_line_to(context, width * 0.92, height * 0.90);
    cairo_move_to(context, width * 0.90, height * 0.92);
    cairo_line_to(context, width * 0.92, height * 0.90);
    cairo_line_to(context, width * 0.90, height * 0.88);
    cairo_stroke(context);
    cairo_restore(context);
}
    
void draw_line(cairo_t *context, Point * points) {
    cairo_save(context);
    cairo_set_line_width (context, 2.0);
    cairo_set_source_rgb (context, 0, 0, 0);
    cairo_move_to(context, points[0].x, points[0].y);
    int i = 0;
    for(; points[i].x > 0; i++) {
        cairo_line_to(context, points[i].x, points[i].y);
    }
    cairo_stroke(context);
    cairo_restore(context);
}
 
void create_point(cairo_t *context, Point *points, Color color,float RAIO) {
    cairo_save(context);
    cairo_set_source_rgba (context, color.r, color.g, color.b, color.a);
    cairo_set_line_width (context, 5.0);
    int i = 0;
    for (; points[i].x > 0; i++){
    cairo_arc (context, points[i].x, points[i].y, RAIO, 0, 2*360);
    cairo_fill (context);
    }
    cairo_restore(context);
}

