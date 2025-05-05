#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_TITLE "SDL Hello World!"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
};

void game_cleanup(struct Game *game);
bool sdl_initialize(struct Game *game);

int main()
{
    struct Game game = {
        .window = NULL,
        .renderer = NULL
    };

    if (sdl_initialize(&game))
    {
        game_cleanup(&game);
        printf("All, bad");
        exit(1);
    }

    SDL_RenderClear(game.renderer);

    SDL_RenderPresent(game.renderer);

    SDL_Delay(5000);

    game_cleanup(&game);

    printf("All, good\n");

    return 0;
}

void game_cleanup(struct Game *game)
{
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
}

bool sdl_initialize(struct Game *game)
{
    //intialize only vido part of sdl because audio doesnt word on wsl: dsp error
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "SDL Could not be Inilialized: %s\n", SDL_GetError());
        return true;
    }

    game->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (!game->window)
    {
        fprintf(stderr, "SDL Window not be Inilialized: %s\n", SDL_GetError());
        return true;
    }

    game->renderer = SDL_CreateRenderer(game->window, -1, 0);
    if (!game->renderer)
    {
        fprintf(stderr, "SDL Window not be Inilialized: %s\n", SDL_GetError());
        return true;
    }

    return false;
}