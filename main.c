#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_TITLE "SDL Hello World!"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define IMAGE_FLAGS IMG_INIT_PNG

struct Game {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
};

void game_cleanup(struct Game *game, int exit_status);
bool load_media(struct Game *game);
bool sdl_initialize(struct Game *game);

int main()
{
    struct Game game = {
        .window = NULL,
        .renderer = NULL,
        .background = NULL
    };

    if (sdl_initialize(&game))
    {
        game_cleanup(&game, EXIT_FAILURE);
    }
    
    if (load_media(&game))
    {
        game_cleanup(&game, EXIT_FAILURE);
    }

    while (true)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type) 
            {
                case SDL_QUIT:
                    game_cleanup(&game, EXIT_SUCCESS);
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_ESCAPE: 
                            game_cleanup(&game, EXIT_SUCCESS);
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        SDL_RenderClear(game.renderer);
        
        SDL_RenderCopy(game.renderer, game.background, NULL, NULL);

        SDL_RenderPresent(game.renderer);

        SDL_Delay(16);
    }

    game_cleanup(&game, EXIT_SUCCESS);
    return 0;
}

void game_cleanup(struct Game *game, int exit_status)
{
    SDL_DestroyTexture(game->background);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    IMG_Quit();
    SDL_Quit();
    exit(exit_status);
}

bool load_media(struct Game *game)
{
    game->background = IMG_LoadTexture(game->renderer, "pixil-frame-0.png");
    if (!game->background)
    {
        fprintf(stderr, "Error creating Texture: %s\n", SDL_GetError());
        return true;
    }

    return false;
}

bool sdl_initialize(struct Game *game)
{
    //intialize only vido part of sdl because audio doesnt word on wsl: dsp error
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        fprintf(stderr, "SDL Could not be Inilialized: %s\n", SDL_GetError());
        return true;
    }

    int img_init = IMG_Init(IMAGE_FLAGS);
    if ((img_init & IMAGE_FLAGS) != IMAGE_FLAGS)
    {
        fprintf(stderr, "Error loading SDL_image: %s\n", SDL_GetError());
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
