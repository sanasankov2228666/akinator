#ifndef GRAPH_INTRFACCE_H_
#define GRAPH_INTRFACCE_H_

#include <TXLib.h>


struct Button
{
    double x0;
    double y0;
    double x1;
    double y1;
    COLORREF color;
    const char* text;
};


Button create_button(double x1, double y1, double x2, double y2, COLORREF color, const char* text = "Button");

void draw_button(Button btn);

bool is_button_clicked(Button btn);

int main_menu();

void draw_centered_text(const char* text, int y, int fontSize, COLORREF color);

int akinator(node_t* node);

int defenition();

int graphic_interface(tree* data);

#endif