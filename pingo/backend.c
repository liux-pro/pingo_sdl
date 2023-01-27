#include "backend.h"

#include "render/renderer.h"
#include "render/texture.h"
#include "render/pixel.h"
#include "render/depth.h"
#include "fast_hsv2rgb.h"



Vec4i rect;
Vec2i totalSize;

PingoDepth * zetaBuffer;
Pixel * frameBuffer;




void init( Renderer * ren, BackEnd * backEnd, Vec4i _rect) {

}

void beforeRender( Renderer * ren, BackEnd * backEnd) {
}



void afterRender( Renderer * ren,  BackEnd * backEnd) {


}

Pixel * getFrameBuffer( Renderer * ren,  BackEnd * backEnd) {
    return frameBuffer;
}

PingoDepth * getZetaBuffer( Renderer * ren,  BackEnd * backEnd) {
    return zetaBuffer;
}
uint16_t rgb888torgb565(uint8_t *rgb888Pixel)
{
    uint8_t red   = rgb888Pixel[0];
    uint8_t green = rgb888Pixel[1];
    uint8_t blue  = rgb888Pixel[2];

    uint16_t b = (blue >> 3) & 0x1f;
    uint16_t g = ((green >> 2) & 0x3f) << 5;
    uint16_t r = ((red >> 3) & 0x1f) << 11;

    return (uint16_t) (r | g | b);
}

void drawPixel(Texture * f, Vec2i pos, Pixel color, float illumination){
    uint8_t r,g,b;

    fast_hsv2rgb_32bit(color.h*illumination,color.s,color.v,&r,&g,&b);
     ;

    ((uint16_t *)f->frameBuffer)[pos.x + pos.y * f->size.x] = ((r & 0b11111000) << 8) | ((g & 0b11111100) << 3) | (b >> 3);

}

void linuxWindowBackEndInit( LinuxWindowBackEnd * this, Vec2i size) {
    totalSize = size;
    this->backend.init = &init;
    this->backend.beforeRender = &beforeRender;
    this->backend.afterRender = &afterRender;
    this->backend.getFrameBuffer = &getFrameBuffer;
    this->backend.getZetaBuffer = &getZetaBuffer;
    this->backend.drawPixel = &drawPixel;

    zetaBuffer = malloc(size.x*size.y*sizeof (PingoDepth));
    frameBuffer = malloc(size.x*size.y*sizeof (Pixel));
    
}
