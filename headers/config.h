#ifdef GRAPHICS_MODE
    #define GRAPHICS(code) code
    #define CONSOLE(code) 
#else
    #define GRAPHICS(code) 
    #define CONSOLE(code) code
#endif