
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

enum bool{false,true};
typedef enum bool bool;

const GLchar* vertexSource =
"#version 330 core\n"
"in vec2 position;"
"in vec3 color;"
"out vec3 Color;"
"void main()"
"{"
"   Color=color;"
"   gl_Position = vec4(position, 0.0, 1.0);"
"}";


const GLchar* fragmentSource =
"#version 330 core\n"
"in vec3 Color;"
"out vec4 outColor;"
"void main()"
"{"
"    outColor = vec4(Color, 1.0);"
"}";

int main(){
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_Window* window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_OPENGL);
    
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_Event windowEvent;
    
    bool window_is_open=true;
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    
     GLfloat vertices[] = {
     0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
     -0.5f, -0.5f, 1.0f, 0.0f, 1.0f,
     -0.5f, 0.5f, 1.0f, 0.0f, 0.0f
     };
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };
    
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    GLuint ebo;
    glGenBuffers(1, &ebo);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    
    
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,5*sizeof(float), 0);
    
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE,5*sizeof(float), (void*)(2*sizeof(float)));
    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        SDL_GL_SwapWindow(window);
        
    }
    
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    
    glDeleteBuffers(1, &vbo);
    
    glDeleteVertexArrays(1, &vao);
    
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    
    return 0;
}


