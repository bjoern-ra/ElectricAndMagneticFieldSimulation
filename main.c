#include <SDL2/SDL.h>
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

void run_main_menu(SDL_Renderer *renderer, AppState *current_state);

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Simulation Selector",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    AppState current_state = MAIN_MENU;

    while (current_state != QUIT) {
        switch (current_state) {
            case MAIN_MENU:
                run_main_menu(renderer, &current_state);
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

    return 0;
}

void run_main_menu(SDL_Renderer *renderer, AppState *current_state) {
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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect electric_button = {100, 100, 200, 50};
        SDL_Rect magnetic_button = {100, 200, 200, 50};
        SDL_Rect flow_button = {100, 300, 200, 50};

        SDL_RenderFillRect(renderer, &electric_button);
        SDL_RenderFillRect(renderer, &magnetic_button);
        SDL_RenderFillRect(renderer, &flow_button);

        SDL_RenderPresent(renderer);
    }
}
