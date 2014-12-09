#include <stdio.h>
#include "storage.h"
#include "drawing.h"

int main(int argc, char * argv[]) {
    json_t *root;
    json_error_t error;
    if (argc != 2){
        printf(" Erro: Diretório ");
        return 1;
    }
    root = json_load_file(argv[1], 0, &error);
    if(root == 0){
        printf("ERRO AO LER ARQUIVO, linha %d!\n", error.line);
        return error.line;
    }
    const char * fileName = JSON_getString(root, "fileName");
    printf("O nome do arquivo é: %s\n", fileName);
    printf("O format é: %s\n", JSON_getString(root, "format"));
    int width = JSON_getInt(root, "width");
    printf("Width: %d\n", width);
    int height = JSON_getInt(root, "height");
    printf("Height: %d\n", height);
    printf("readOnly: %d\n", JSON_getBool(root, "readOnly"));

    cairo_surface_t *surface =
    cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cairo_t *context = cairo_create(surface);

    cairo_set_source_rgba(context, 1, 1, 1, 1);
    cairo_rectangle(context, 0, 0, width, height);
    cairo_fill(context);
    
    drawAxisX(context, width, height);
    drawAxisY(context, width, height);

    Color pointColor = JSON_getColor(root);
    cairo_set_source_rgba(context, pointColor.r,
                                   pointColor.g,
                                   pointColor.b,
                                   pointColor.a);
    float HIGHERX = higherX(root);
    float HIGHERY = higherY(root);
    int RAIO = (width + height)/1000 + 2;
    Point *points = JSON_getPoints(root, height, width, HIGHERX, HIGHERY);
    draw_line(context, points);
    create_point(context, points, pointColor, RAIO);
    cairo_surface_write_to_png(surface, fileName);
 

    cairo_destroy(context);
    cairo_surface_destroy(surface);
    return 0;
}
