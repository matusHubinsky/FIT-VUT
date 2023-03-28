/**
 * IZG - Zaklady pocitacove grafiky - FIT VUT
 * Lab 01 - Redukce barevneho prostoru
 *
 * Copyright (c) 2022 by Michal Vlnas, ivlnas@fit.vutbr.cz
 *
 * Tato sablona slouzi vyhradne pro studijni ucely, sireni kodu je bez vedomi autora zakazano.
 */

#include "base.h"

void ImageTransform::grayscale()
{
    RGB color;
    for (uint32_t y = 0; y < cfg->height; y++)
    {
        for (uint32_t x = 0; x < cfg->width; x++)
        {
            color = getPixel(x, y);
            float i = round(0.299 * color.r + 0.587 * color.g + 0.144 * color.b);
            setPixel(x, y, RGB(i));
            // deje sa tu ten isty problem ako v skole? 'sus
        }
    } 
}

void ImageTransform::threshold()
{
    RGB color;
    for (uint32_t y = 0; y < cfg->height; y++)
    {
        for (uint32_t x = 0; x < cfg->width; x++)
        {
            color = getPixel(x, y);
     
            float i = round(0.299 * color.r + 0.587 * color.g + 0.144 * color.b);
            if (i < cfg->threshold) i = 0;
            else i = 255;

            setPixel(x, y, RGB(i));
        }
    }
}

void ImageTransform::randomDithering()
{
    grayscale();

    for (uint32_t y = 0; y < cfg->height; y++)
    {
        for (uint32_t x = 0; x < cfg->width; x++)
        {
            auto p = getPixel(x, y);
            uint8_t value = p.r > getRandom() ? 255 : 0;

            setPixel(x, y, RGB(value));
        }
    }
}

void ImageTransform::orderedDithering()
{
    RGB color;
    int m[4][4] = {{0, 204, 51, 255,}, {68, 136, 187, 119}, {34, 238, 17, 221}, {170, 102, 153, 85}};

    for (uint32_t y = 0; y < cfg->height; y++)
    {
        for (uint32_t x = 0; x < cfg->width; x++)
        {
            uint32_t i = x % m_side;
            uint32_t j = y % m_side;

            color = getPixel(x, y);
     
            float l = round(0.299 * color.r + 0.587 * color.g + 0.144 * color.b);
            if (l < m[i][j]) l = 0;
            else l = 255;

            setPixel(x, y, RGB(l));
        }
    }
}

void ImageTransform::updatePixelWithError(uint32_t x, uint32_t y, float err)
{
    // TODO
}

void ImageTransform::errorDistribution()
{
    // TODO
}

