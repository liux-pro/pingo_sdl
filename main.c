#include <SDL.h>


#include "render/material.h"
#include "render/mesh.h"
#include "render/object.h"
#include "render/pixel.h"
#include "render/renderer.h"
#include "render/scene.h"
#include "assets/teapot.h"
#include "assets/cube.h"
#include "assets/pingo.h"
#include "backend.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "stdbool.h"

#define WINDOW_WIDTH 240
#define WINDOW_HEIGHT 240

SDL_Window *window;
SDL_Renderer *_renderer;
SDL_Surface *surface;
SDL_Event e;
SDL_Texture *texture;
bool quit;


void loop() {

}

void sdl_simple_init() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &_renderer);

    //flag 和 depth 实际上没用，并且它们会在sdl3中被删除
    surface = SDL_CreateRGBSurfaceWithFormat(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_PIXELFORMAT_BGRA32);
    if (surface == NULL) {
        SDL_Log("SDL_CreateRGBSurfaceWithFormat() failed: %s", SDL_GetError());
        exit(1);
    }
    texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_BGRA32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH,
                                WINDOW_HEIGHT);
}




void pingo_init() {




    // optional hide cursor
//    while (1) {
//
//    }

}

int main(int argc, char *argv[]) {
    sdl_simple_init();
    pingo_init();
    ///////////
    Vec2i size = {WINDOW_WIDTH, WINDOW_HEIGHT};

    LinuxWindowBackEnd backend;
    linuxWindowBackEndInit(&backend, size);


    Renderer renderer;
    rendererInit(&renderer, size, (BackEnd *) &backend);
    rendererSetCamera(&renderer, (Vec4i) {0, 0, size.x, size.y});

    Scene s;
    sceneInit(&s);
    rendererSetScene(&renderer, &s);


    Object object;
    object.mesh = &mesh_cube;


    float phi = 0;
    Mat4 t;


#define N  1
    Texture tex;
    texture_init(&tex, (Vec2i) {N, N}, malloc(N * N * sizeof(Pixel)));


    for (int i = 0; i < N; i++)
        for (int y = 0; y < N; y++) {
//            ((uint8_t *) tex.frameBuffer)[4 * (i * N + y) + 0] = y == 0xff;
            ((uint8_t *) tex.frameBuffer)[4 * (i * N + y) + 0] = y == 0 ? 0xff : 00;
            ((uint8_t *) tex.frameBuffer)[4 * (i * N + y) + 1] = y == 1 ? 0xff : 00;
            ((uint8_t *) tex.frameBuffer)[4 * (i * N + y) + 2] = y == 2 ? 0xff : 00;
            ((uint8_t *) tex.frameBuffer)[4 * (i * N + y) + 3] = 0xff;
        }

    Material m;
    m.texture = &tex;
    object.material = &m;


    sceneAddRenderable(&s, object_as_renderable(&object));
    /////////////


#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
#endif

#ifndef __EMSCRIPTEN__
    // repeatedly calling mainloop on desktop
    while (!quit) {
        loop();
        ////////
        while (SDL_PollEvent(&e)) {
            // window close event
            if (e.type == SDL_QUIT) {
                quit = true;
                break;
            }
        } // end poll events


        if (SDL_MUSTLOCK(surface)) SDL_LockSurface(surface);

        Uint8 *pixels = (Uint8 *) (surface->pixels);


        //11111111111111111111111
        // PROJECTION MATRIX - Defines the type of projection used
        renderer.camera_projection = mat4Perspective(1, 2500.0, (float) size.x / (float) size.y, 0.6);

        //VIEW MATRIX - Defines position and orientation of the "camera"
        Mat4 v = mat4Translate((Vec3f) {0, 50, -250});
        Mat4 rotateDown = mat4RotateX(0.40); //Rotate around origin/orbit
        renderer.camera_view = mat4MultiplyM(&rotateDown, &v);

        //TEA TRANSFORM - Defines position and orientation of the object
        object.transform = mat4RotateZ(3.142128);
        t = mat4Scale((Vec3f) {80, 80, 80});
        object.transform = mat4MultiplyM(&object.transform, &t);
        t = mat4Translate((Vec3f) {0, 45, 0});
        object.transform = mat4MultiplyM(&object.transform, &t);
        t = mat4RotateX(3.14);
        object.transform = mat4MultiplyM(&object.transform, &t);

        //SCENE
        s.transform = mat4RotateY(phi);
        phi += 0.02;

        rendererRender(&renderer);
        //111111111111111111111111111111111

        Pixel * getFrameBuffer( Renderer * ren,  BackEnd * backEnd);

//        memcpy(pixels, WorkFrame, WINDOW_WIDTH * WINDOW_HEIGHT * 2);
        memcpy(pixels, getFrameBuffer(0,0), WINDOW_WIDTH * WINDOW_HEIGHT * 4);

        if (SDL_MUSTLOCK(surface)) SDL_UnlockSurface(surface);

        SDL_UpdateTexture(texture, NULL, surface->pixels, surface->pitch);

        SDL_RenderClear(_renderer);
        SDL_RenderCopy(_renderer, texture, NULL, NULL);
        SDL_RenderPresent(_renderer);
        ////////
        SDL_Delay(16);
    };
#endif
}