#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>

Uint32 getPixelFromSurface(SDL_Surface* surface, unsigned int x, unsigned int y);

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface* surface;
    surface = SDL_LoadBMP("file.bmp");
    if(!surface)
        return 1;

    std::cout << "SDL_Surface* surface;" << std::endl;
    std::cout << "unsigned char pixels[] = {" << std::endl;

    for(int i = 0; i < surface->h; i++)
    {
        for(int j = 0; j < surface->w; j++)
        {
            if(j) // If not first
                std::cout << " ";
            Uint32 pixel = getPixelFromSurface(surface, j, i);
            std::cout << ( (pixel >> 16) & 0xff  ) << ", ";
            std::cout << ( (pixel >> 8) & 0xff  ) << ", ";
            std::cout << ( (pixel >> 0) & 0xff  ); //<< ", ";
            //std::cout << 255;
            if( (i != (surface->w-1)) || (j != (surface->h-1)) )
                std::cout << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "};" << std::endl;
/// surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, surface->w, surface->h, 32, surface->w*4, SDL_PIXELFORMAT_RGBA32);
    std::cout << "surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, " << surface->w << ", " << surface->h << ", 24, " << surface->w << "*3, SDL_PIXELFORMAT_RGB24);" << std::endl;

    SDL_Quit();
    return 0;
}

Uint32 getPixelFromSurface(SDL_Surface* surface, unsigned int x, unsigned int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8* pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    return *(Uint32*)pixel;
}
