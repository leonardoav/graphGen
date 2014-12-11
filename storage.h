#ifndef STORAGE_H
#define STORAGE_H

#include <jansson.h>
#include "utils.h"

double JSON_getDouble(json_t *node, const char * varName);

int JSON_getInt(json_t *node, const char * varName);

const char * JSON_getString(json_t *node, const char * varName);

int JSON_getBool(json_t *node, const char * varName);

Color JSON_getColor(json_t *node);

Point * JSON_getPoints(json_t *root, float width, float height, double HIGHERX, double HIGHERY);

double higherX(json_t *root);
    
double higherY(json_t *root);

Point * sortPoints(json_t *root, Point *content);

#endif
