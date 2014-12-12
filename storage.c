#include "storage.h"

int JSON_getInt(json_t *node, const char * varName) {
    json_t *jVal = json_object_get(node, varName);
    return json_integer_value(jVal);
}

const char * JSON_getString(json_t *node, const char * varName) {
    json_t *jVal = json_object_get(node, varName);
    return json_string_value(jVal);
}

int JSON_getBool(json_t *node, const char * varName) {
    json_t *jVal = json_object_get(node, varName);
    return json_is_true(jVal);
}

Color JSON_getColor(json_t *root) {
    Color c;
    json_t *jColor = json_object_get(root, "color");
    json_t * jItem0 = json_array_get(jColor, 0);
    c.r = json_integer_value(jItem0)/255.0;
    json_t * jItem1 = json_array_get(jColor, 1);
    c.g = json_integer_value(jItem1)/255.0;
    json_t * jItem2 = json_array_get(jColor, 2);
    c.b = json_integer_value(jItem2)/255.0;
    json_t * jItem3 = json_array_get(jColor, 3);
    c.a = json_integer_value(jItem3)/255.0;
    return c;
}

double higherX(json_t *root){//FUNÇÃO PARA PEGAR O MAIOR X---
    int i = 0;  
    double xHigher = 0;
    json_t *jPoints = json_object_get(root, "content");
    Point * content = malloc(sizeof(Point)*json_array_size(jPoints));
    for(; i < json_array_size(jPoints); ++i){
        json_t * jPoint = json_array_get(jPoints, i);
        json_t *jX = json_object_get(jPoint, "x");
        if ( xHigher < json_integer_value(jX))
            xHigher = json_integer_value(jX);
    }
    return xHigher;//RETORNA O MAIOR X---
}

double higherY( json_t *root){//FUNÇÃO PARA PEGAR O MAIOR Y---
    int i = 0; 
    double yHigher = 0;
    json_t *jPoints = json_object_get(root, "content");
    Point * content = malloc(sizeof(Point)*json_array_size(jPoints));
    for(; i < json_array_size(jPoints); i++){
        json_t * jPoint = json_array_get(jPoints, i);
        json_t *jY = json_object_get(jPoint, "y");
        if( yHigher < json_integer_value(jY))
            yHigher = json_integer_value(jY);
    }
    return yHigher;//RETORNA O MAIOR Y---
}

Point * JSON_getPoints(json_t *root, float width, float height, double HIGHERX, double HIGHERY) {
    json_t *jPoints = json_object_get(root, "content");
    Point * content = malloc(sizeof(Point)*json_array_size(jPoints));
    for(int i = 0; i < json_array_size(jPoints); ++i){
        json_t * jPoint = json_array_get(jPoints, i);
        json_t *jX = json_object_get(jPoint, "x");
        json_t *jY = json_object_get(jPoint, "y");
        if(json_integer_value(jX) >= 0){
            //PROPORÇÃO DOS PONTOS---
            content[i].x = width * 0.10 + (json_integer_value(jX)/HIGHERX) * (width * 0.80);
        } else{ 
            content[i].x = json_integer_value(jX);
          } if (json_integer_value(jY) >= 0){
            //PROPORÇÃO DOS PONTOS---
            content[i].y = height * 0.90 - (json_integer_value(jY)/HIGHERY) * (height * 0.80);
            } else {
            content[i].y = json_integer_value(jY);
              }
    } //ORDENANDO OS PONTOS ---
    int cont1;
    int cont2;
    Point buffer;
    for(cont1 = 0; cont1 <  json_array_size(jPoints) - 2 ; cont1++){
        for(cont2 = cont1 + 1; cont2 <= json_array_size(jPoints) - 2; cont2++){
            if(content[cont2].x < content[cont1].x){            
                buffer = content[cont2];
                content[cont2] = content[cont1];
                content[cont1] = buffer;
            }
        }
    }

    return content;//RETORNA OS PONTOS ORDENADOS---
    
}      