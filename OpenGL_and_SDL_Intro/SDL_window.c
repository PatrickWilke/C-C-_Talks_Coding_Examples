
#include <SDL2/SDL.h>

enum bool{false,true};
typedef enum bool bool;

int main(){
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_Window* window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    
    SDL_Event windowEvent;
    
    bool window_is_open=true;
    
    while (window_is_open){
        
        while (SDL_PollEvent(&windowEvent)){
            
            switch (windowEvent.type) {
                case SDL_QUIT:
                    window_is_open=false;
                    break;
                case SDL_KEYUP:
                    if (windowEvent.key.keysym.sym == SDLK_ESCAPE) {
                        window_is_open=false;
                        break;
                    }
                default:
                    break;
            }
            
        }
        
    }
    
    SDL_Quit();
    
    return 0;
}


