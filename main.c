#include <stdio.h>
#include "storage.h"
#include "drawing.h"
#include <cairo/cairo-pdf.h>
#include <string.h>
#include <jansson.h>


int main(int argc, char * argv[]) {
    json_t *root;
    json_error_t error;
    if (argc != 2){
        printf(" Erro: Entre com dois argumentos\n ");
        return 1;
    }
    root = json_load_file(argv[1], 0, &error);
    if(root == 0){
        printf("ERRO AO LER ARQUIVO, linha %d!\n", error.line);
        return error.line;
    }
    const char * fileName = JSON_getString(root, "fileName");
    printf("O nome do arquivo é: %s\n", fileName);
    const char * fileType = JSON_getString(root, "fileType");
    printf("O format é: %s\n", fileType);
    int width = JSON_getInt(root, "width");
    printf("Width: %d\n", width);
    int height = JSON_getInt(root, "height");
    printf("Height: %d\n", height);
    int type = JSON_getInt(root, "type");
    printf("Type: %d\n", type);
    const char * title = JSON_getString(root, "title");
    printf("O título do aquivo é: %s\n", JSON_getString(root, "title"));

    cairo_surface_t *surface;
        if(!(strcmp(fileType,"png"))){//VERIFICANDO SE O FORMATO É PDF OU PNG---
            surface =cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
        }else if (!(strcmp(fileType,"pdf"))){
            surface = cairo_pdf_surface_create(fileName, width, height);
         }
    
    cairo_t *context = cairo_create(surface);
    cairo_set_source_rgba(context, 1, 1, 1, 1);
    cairo_rectangle(context, 0, 0, width, height);
    cairo_fill(context);

    Color pointColor = JSON_getColor(root);
    cairo_set_source_rgba(context, pointColor.r,
                                   pointColor.g,
                                   pointColor.b,
                                   pointColor.a);
    float HIGHERX = higherX(root);//RECEBE MAIOR X---
    float HIGHERY = higherY(root);//RECEBE MAIOR Y---
    float RAIO = (width + height)/1000 + 2.5;//PROPORÇÃO DO PONTO---
    float axisThickness = (width + height)/1000 + 3.0;//PROPORÇÃO DOS EIXOS---
    float lineThickness = (width + height)/1000 + 2.0;//PROPORÇÃO DA LINHA---
    Point *content = JSON_getPoints(root, width, height, HIGHERX, HIGHERY);
    
    text(title,context, pointColor, width, height);//TEXTO---

    if ( type == 0 ){//GRÁFICO DE PONTOS--- OS EIXOS SÃO DESENHADOS PRIMEIRO CASO O PONTO DADO         FIQUE EM CIMA DELES---
        drawAxisX(context, width, height, axisThickness);//EIXO X---
        drawAxisY(context, width, height, axisThickness);//EIXO Y---
        create_point(context, content, pointColor, RAIO, lineThickness);
    }if ( type == 1){//GRÁFICO DE LINHA---
        draw_line(context, content, pointColor, lineThickness, RAIO);
        drawAxisX(context, width, height, axisThickness);//EIXO X---
        drawAxisY(context, width, height, axisThickness);//EIXO Y---
    }if ( type == 2){//GRÁFICO DE ÁREA---
        draw_area(context, content, pointColor, height);
        drawAxisX(context, width, height, axisThickness);//EIXO X---
        drawAxisY(context, width, height, axisThickness);//EIXO Y---
    }
        
    if(!(strcmp(fileType,"png"))){//VERIFICANDO SE O FORMATO É PDF OU PNG---
        cairo_surface_write_to_png(surface, fileName);
    }else if (!(strcmp(fileType,"pdf"))){
        cairo_show_page(context);
     }
    cairo_destroy(context);
    cairo_surface_destroy(surface);
    return 0;
}
