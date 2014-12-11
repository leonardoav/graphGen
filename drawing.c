#include "drawing.h"
#include "storage.h"



void drawAxisY(cairo_t *context, int width, int height, float axisThickness) {
    cairo_save(context);
    cairo_set_line_width (context, axisThickness);
    cairo_set_source_rgb (context, 0, 0, 0);
    cairo_move_to(context, width * 0.10, height * 0.90);
    cairo_line_to(context, width * 0.10, height * 0.08);
    cairo_move_to(context, width * 0.12, height * 0.10);
    cairo_line_to(context, width * 0.10, height * 0.08);
    cairo_line_to(context, width * 0.08, height * 0.10);
    cairo_stroke(context);
    cairo_restore(context);
    
}

void drawAxisX(cairo_t *context, int width, int height, float axisThickness){
    cairo_save(context);
    cairo_set_line_width (context, axisThickness);
    cairo_set_source_rgb (context, 0, 0, 0);
    cairo_move_to(context, width * 0.10, height * 0.90);
    cairo_line_to(context, width * 0.92, height * 0.90);
    cairo_move_to(context, width * 0.90, height * 0.92);
    cairo_line_to(context, width * 0.92, height * 0.90);
    cairo_line_to(context, width * 0.90, height * 0.88);
    cairo_stroke(context);
    cairo_restore(context);
}
    
void draw_line(cairo_t *context, Point * content, Color color) {
    cairo_save(context);
    cairo_set_source_rgba (context, color.r, color.g, color.b, color.a);
    cairo_set_line_width (context, 2.0);
    cairo_move_to(context, content[0].x, content[0].y);
    int i = 0;
    for(; content[i].x > 0; i++) {
        cairo_line_to(context, content[i].x, content[i].y);
    }
    cairo_stroke(context);
    cairo_restore(context);
}
 
void create_point(cairo_t *context, Point *content, Color color,float RAIO) {
    cairo_save(context);
    cairo_set_source_rgba (context, color.r, color.g, color.b, color.a);
    cairo_set_line_width (context, 5.0);
    int i = 0;
    for (; content[i].x > 0; i++){
    cairo_arc (context, content[i].x, content[i].y, RAIO, 0, 2*360);
    cairo_fill (context);
    }
    cairo_restore(context);
}

void draw_area(cairo_t *context, Point *content, Color color, int height) {
    cairo_save(context);
    cairo_set_source_rgba (context, color.r, color.g, color.b, color.a);
    cairo_set_line_width (context, 5.0);
    cairo_arc (context, content[0].x, height * 0.90, 0, 0, 2*360);
    int i = 0, lastdot;
    for (; content[i].x > 0; i++){
    cairo_arc (context, content[i].x, content[i].y, 0, 0, 2*360);
        lastdot = i;
    }
    cairo_arc (context, content[lastdot].x, height * 0.90, 0, 0, 2*360);
    cairo_fill(context);
}
        
    
    
