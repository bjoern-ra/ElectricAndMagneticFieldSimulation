#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "electric_field.h"
#include "magnetic_field.h"
#include "flow_field.h"

typedef enum {
    MAIN_MENU,
    ELECTRIC_FIELD,
    MAGNETIC_FIELD,
    FLOW_FIELD,
    QUIT
} AppState;

// Updated function declaration to include the font parameter
void run_main_menu(SDL_Renderer *renderer, TTF_Font *font, AppState *current_state);

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Simulation Selector",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    TTF_Font *font = TTF_OpenFont("path_to_your_font.ttf", 24);
    if (!font) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    AppState current_state = MAIN_MENU;

    while (current_state != QUIT) {
        switch (current_state) {
            case MAIN_MENU:
                run_main_menu(renderer, font, &current_state);  // Pass the font parameter
                break;
            case ELECTRIC_FIELD:
                run_electric_field_simulation(renderer);
                current_state = MAIN_MENU;
                break;
            case MAGNETIC_FIELD:
                run_magnetic_field_simulation(renderer);
                current_state = MAIN_MENU;
                break;
            case FLOW_FIELD:
                run_flow_field_simulation(renderer);
                current_state = MAIN_MENU;
                break;
            case QUIT:
                break;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_CloseFont(font);
    TTF_Quit();

    return 0;
}

void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest_rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void run_main_menu(SDL_Renderer *renderer, TTF_Font *font, AppState *current_state) {
    SDL_Event event;
    int running = 1;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                *current_state = QUIT;
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;

                if (x > 100 && x < 300) {
                    if (y > 100 && y < 150) {
                        *current_state = ELECTRIC_FIELD;
                        running = 0;
                    } else if (y > 200 && y < 250) {
                        *current_state = MAGNETIC_FIELD;
                        running = 0;
                    } else if (y > 300 && y < 350) {
                        *current_state = FLOW_FIELD;
                        running = 0;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Background color: Black
        SDL_RenderClear(renderer);

        // Draw Electric Field button - Red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect electric_button = {100, 100, 200, 50};
        SDL_RenderFillRect(renderer, &electric_button);

        // Draw Magnetic Field button - Green
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect magnetic_button = {100, 200, 200, 50};
        SDL_RenderFillRect(renderer, &magnetic_button);

        // Draw Flow Field button - Blue
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_Rect flow_button = {100, 300, 200, 50};
        SDL_RenderFillRect(renderer, &flow_button);

        // Render text
        SDL_Color white = {255, 255, 255, 255}; // Text color: White
        render_text(renderer, font, "Electric Field", white, 130, 115);
        render_text(renderer, font, "Magnetic Field", white, 130, 215);
        render_text(renderer, font, "Flow Field", white, 130, 315);

        SDL_RenderPresent(renderer);
    }
}
