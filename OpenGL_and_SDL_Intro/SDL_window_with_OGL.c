
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

enum bool{false,true};
typedef enum bool bool;

int main(){
    
    SDL_Init(SDL_INIT_VIDEO);
    
    SDL_Window* window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_Event windowEvent;
    
    bool window_is_open=true;
    
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
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
    
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
        
    }
    
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    
    return 0;
}


