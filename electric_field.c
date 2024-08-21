#include "electric_field.h"
#include <SDL2/SDL.h>
#include <math.h>

#define POINT_RADIUS 10
#define NUM_CIRCLES 5  // Anzahl der konzentrischen Kreise
#define CIRCLE_SPACING 20  // Abstand zwischen den Kreisen

typedef struct {
    float x, y;
} Point;

void draw_point(SDL_Renderer *renderer, int cx, int cy, int radius) {
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

void draw_concentric_circles(SDL_Renderer *renderer, int cx, int cy, int num_circles, int spacing) {
    for (int i = 1; i <= num_circles; i++) {
        int radius = i * spacing;
        for (int w = 0; w < radius * 2; w++) {
            for (int h = 0; h < radius * 2; h++) {
                int dx = radius - w;
                int dy = radius - h;
                if ((dx * dx + dy * dy) <= (radius * radius) && (dx * dx + dy * dy) >= ((radius - 1) * (radius - 1))) {
                    SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
                }
            }
        }
    }
}

void run_electric_field_simulation(SDL_Renderer *renderer) {
    Point point1 = {300, 300};
    Point point2 = {500, 300};

    SDL_Event event;
    int running = 1;
    Point *selected_point = NULL;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouse_x = event.button.x;
                int mouse_y = event.button.y;
                if (sqrt(pow(mouse_x - point1.x, 2) + pow(mouse_y - point1.y, 2)) < POINT_RADIUS) {
                    selected_point = &point1;
                } else if (sqrt(pow(mouse_x - point2.x, 2) + pow(mouse_y - point2.y, 2)) < POINT_RADIUS) {
                    selected_point = &point2;
                }
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                selected_point = NULL;
            } else if (event.type == SDL_MOUSEMOTION && selected_point) {
                selected_point->x = event.motion.x;
                selected_point->y = event.motion.y;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw concentric circles around the points
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        draw_concentric_circles(renderer, point1.x, point1.y, NUM_CIRCLES, CIRCLE_SPACING);
        draw_concentric_circles(renderer, point2.x, point2.y, NUM_CIRCLES, CIRCLE_SPACING);

        // Draw the points
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        draw_point(renderer, point1.x, point1.y, POINT_RADIUS);
        draw_point(renderer, point2.x, point2.y, POINT_RADIUS);

        SDL_RenderPresent(renderer);
    }
}
