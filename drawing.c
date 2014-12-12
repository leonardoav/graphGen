#include "drawing.h"
#include "storage.h"



void drawAxisY(cairo_t *context, int width, int height, float axisThickness) {
    cairo_save(context);
    cairo_set_line_width (context, axisThickness);
    cairo_set_source_rgb (context, 0, 0, 0);
    cairo_move_to(context, width * 0.10, height * 0.90);
    cairo_line_to(context, width * 0.10, height * 0.08);
    //SETAS DO EIXO---
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
    //SETAS DO EIXO---
    cairo_move_to(context, width * 0.90, height * 0.92);
    cairo_line_to(context, width * 0.92, height * 0.90);
    cairo_line_to(context, width * 0.90, height * 0.88);
    cairo_stroke(context);
    cairo_restore(context);
}
    
void draw_line(cairo_t *context, Point * content, Color color , float lineThickness, float RAIO) {
    cairo_save(context);
    cairo_set_source_rgba (context, color.r, color.g, color.b, color.a);
    cairo_set_line_width (context, lineThickness);
    cairo_move_to(context, content[0].x, content[0].y);
    int i = 0;
    for(; content[i].x > 0; i++) {
        cairo_line_to(context, content[i].x, content[i].y);
    }
    cairo_stroke(context);
    cairo_restore(context);
    //PONTOS DA LINHA---
    cairo_save(context);
    cairo_set_source_rgba (context, 0, 0, 0, 0.6);
    cairo_set_line_width (context, 5.0);
    int j = 0;
    for (; content[j].x > 0; j++){
    cairo_arc (context, content[j].x, content[j].y, RAIO - 0.5, 0, 2*360);
    cairo_fill (context);
    }
    cairo_restore(context);
}
 
void create_point(cairo_t *context, Point *content, Color color,float RAIO, float       lineThickness) {
    cairo_save(context);
    double dashed[] = {5.0};//LINHA TRACEJADA---
    cairo_set_source_rgba (context, color.r, color.g, color.b, color.a);
    cairo_set_line_width (context, lineThickness - 1.5);
    cairo_move_to(context, content[0].x, content[0].y);
    int j = 0;
    for(; content[j].x > 0; j++) {
        cairo_line_to(context, content[j].x, content[j].y);
    }
    cairo_set_dash(context, dashed, 1, 0);
    cairo_stroke(context);
    cairo_restore(context);
    
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
    cairo_arc (context, content[0].x, height * 0.90, 0, 0, 2*360);//TRAÇANDO UMA LINHA DO PRIMEIRO PONTO AO EIXO X---
    int i = 0, lastdot;
    for (; content[i].x > 0; i++){
    cairo_arc (context, content[i].x, content[i].y, 0, 0, 2*360);
        lastdot = i;//RECEBE O ÚLTIMO PONTO---
    }
    cairo_arc (context, content[lastdot].x, height * 0.90, 0, 0, 2*360);//TRAÇANDO UMA LINHA DO ÚLTIMO PONTO AO EIXO X---
    cairo_fill(context);
}

void text(const char * chartText, cairo_t *context, Color color, int width, int height){
    cairo_text_extents_t extents;
    const char *utf8 = chartText;
    double x,y;
    cairo_select_font_face (context, "Sans",
    CAIRO_FONT_SLANT_NORMAL,
    CAIRO_FONT_WEIGHT_BOLD);

cairo_set_font_size (context, height/20);
cairo_text_extents (context, utf8, &extents);
x = width/2 -(extents.width/2 + extents.x_bearing);
y = height/16 -(extents.height/2 + extents.y_bearing);

cairo_move_to (context, x, y);
cairo_show_text (context, utf8);

cairo_stroke (context);

}
    