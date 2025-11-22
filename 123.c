#include <TXLib.h>
#include <stdio.h>

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

int akinator();

int defenition();

int main() 
{
    txCreateWindow(1024, 768);
    
    int currentScreen = 0;
    int selection = 0;

    while (!txGetAsyncKeyState(VK_ESCAPE))
    {        
        txClear();
        txSetFillColor(TX_WHITE);
        txClear();
        
        if (currentScreen == 0) 
        {
            selection = main_menu();
            if (selection == 1) currentScreen = 1;
            if (selection == 2) currentScreen = 2;

            else if (selection == 5) break;
        }

        else if (currentScreen == 1) 
        {
            selection = akinator();
            if (selection == 3) currentScreen = 0;
        }

        else if (currentScreen == 2) 
        {
            selection = defenition();
            if (selection == 3) currentScreen = 0;
        }
        
        txSleep(10);
    }
    
    return 0;
}

int main_menu()
{
    static Button btn1 = create_button(100, 600, 200, 650, TX_RED, "Guesser");
    static Button btn2 = create_button(250, 600, 380, 650, TX_RED, "Defenition");
    static Button btn3 = create_button(430, 600, 530, 650, TX_RED, "Compare");
    static Button btn4 = create_button(580, 600, 680, 650, TX_GREEN, "Options");
    static Button btn5 = create_button(730, 600, 830, 650, TX_BLUE, "Exit");

    draw_button(btn1);
    draw_button(btn2);
    draw_button(btn3);
    draw_button(btn4);
    draw_button(btn5);
    draw_centered_text("AKINATOR", 100, 72, TX_RED);

    if (is_button_clicked(btn1)) return 1;
    if (is_button_clicked(btn2)) return 2;
    if (is_button_clicked(btn3)) return 3;
    if (is_button_clicked(btn4)) return 4;
    if (is_button_clicked(btn5)) return 5;
    
    return 0;
}

int akinator()
{
    static Button btn1 = create_button(100, 600, 300, 650, TX_GREEN, "YES");
    static Button btn2 = create_button(600, 600, 800, 650, TX_RED, "NO");
    static Button btn3 = create_button(900, 100, 1000, 150, TX_RED, "EXIT");

    draw_button(btn1);
    draw_button(btn2);
    draw_button(btn3);
    
    draw_centered_text("question?", 300, 36, TX_BLACK);

    if (is_button_clicked(btn1)) return 1;
    if (is_button_clicked(btn2)) return 2;
    if (is_button_clicked(btn3)) return 3;
    
    return 0;
}

int defenition()
{
    static Button btn1 = create_button(900, 100, 1000, 150, TX_RED, "EXIT");

    draw_button(btn1);

    if (is_button_clicked(btn1)) return 3;
    
    const char* text_in = txInputBox();
    if (text_in != NULL)
    {
        
    }

    return 0;
}

char* input_bar(double x0, double y0, double x1, double y1)
{
    char str[100] = "abc";
    txTextOut(500, 500, str);

    if ( txGetAsyncKeyState('A') ) txTextOut(520, 500, "A");
 
    return NULL;
}   

void draw_centered_text(const char* text, int y, int fontSize, COLORREF color)
{
    txSelectFont("Arial", fontSize);
    int textWidth = txGetTextExtentX(text);
    int centerX = (950 - textWidth) / 2;
    
    txSetColor(color);
    txTextOut(centerX, y, text);
}

Button create_button(double x1, double y1, double x2, double y2, COLORREF color, const char* text)
{
    Button btn = {};
    btn.x0 = x1;
    btn.y0 = y1;
    btn.x1 = x2;
    btn.y1 = y2;
    btn.color = color;
    btn.text = text;

    return btn;
}

void draw_button(Button btn)
{
    txSetColor(TX_BLACK);
    txSetFillColor(btn.color); 
    txRectangle((int)btn.x0, (int)btn.y0, (int)btn.x1, (int)btn.y1);
    
    txSetColor(TX_WHITE);
    txSelectFont("Arial", 20);
    int textWidth = txGetTextExtentX(btn.text);
    int textX = (int)btn.x0 + ((int)btn.x1 - (int)btn.x0 - textWidth) / 2;
    int textY = (int)btn.y0 + ((int)btn.y1 - (int)btn.y0 - 20) / 2;
    txTextOut(textX, textY, btn.text);
}

bool is_button_clicked(Button btn)
{
    if (txMouseButtons() == 1)
    {
        double mx = txMouseX();
        double my = txMouseY();
        return (mx >= btn.x0 && mx <= btn.x1 && my >= btn.y0 && my <= btn.y1);
    }

    return false;
}