#include "RogueTerm/RT_Window.h"

RT_Window::RT_Window(RT_Font* _font, int _width, int _height, const char *_title) {
    font = _font;
    cwidth = _width;
    cheight = _height;
    title = _title;

    init_window();
}

bool RT_Window::init_window() {
    // Generate pixel dimensions of window from character dimensions
    RT_Rect fdim = font->get_font_dimensions();
    pwidth = fdim.width * cwidth;
    pheight = fdim.height * cheight;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }

    // Create window
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, pwidth, pheight, SDL_WINDOW_SHOWN);
    
    // Exit if window creation failed
    if(window == NULL) {
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    character_matrix = new RT_CharacterMatrix(cwidth, cheight);

    // Get the window surface
    surface = SDL_GetWindowSurface(window);
}

void RT_Window::clear() {
    // Fill surface with the color black
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));
}

void RT_Window::update() {
    SDL_UpdateWindowSurface(window);
}

// Draws a character at the given coordinates
void RT_Window::draw_char(char c, int cx, int cy, RT_Colour *colour) {
    RT_Rect fdim = font->get_font_dimensions();

    font->blit_char(c, surface, cx*fdim.width, cy*fdim.height, colour);
}

// Draws a string at the given coordinates
void RT_Window::draw_string(const char* string, int cx, int cy, RT_Colour *colour) {
    RT_Rect fdim = font->get_font_dimensions();

    int i = 0;
    char c;
    while((c = string[i++]) != '\0') {
        font->blit_char(c, surface, (cx + i)*fdim.width, cy*fdim.height, colour);
    }
}