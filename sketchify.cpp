#include <cstdlib>
#include <cmath>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "cs221util/RGB_HSL.h"

using namespace cs221util;
using namespace std;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
RGBAPixel* myFavoriteColor(int r, int g, int b) {
    RGBAPixel* pixel = new RGBAPixel(r, g, b);
    return pixel;
}


// Returns a score determining if the pixel is an edge
// requires 1 <= x < width - 1; 1 <= y < height - 1
double edgeScore(PNG* im, unsigned x, unsigned y) {
    double score = 0;
       
    // calculate score based on the (HSL) luminance of the current pixel
    // and the 8 neighboring pixels around it
    for (int i = -1; i < 2; i++){
        for (int j = -1; j < 2; j++){
            if (i == 0 && j == 0) {
                RGBAPixel* px = im->getPixel(x,y);
                rgbaColor rgba = {px->r, px->g, px->b, (unsigned char)(px->a*255.0)};
                hslaColor hsla = rgb2hsl(rgba);
                score += 8 * (hsla.l);
            } else {
                RGBAPixel* px = im->getPixel(x+i,y+j);
                rgbaColor rgba = {px->r, px->g, px->b, (unsigned char)(px->a*255.0)};
                hslaColor hsla = rgb2hsl(rgba);
                score -= hsla.l;
            }
        }
    }
    return score;
}
 
void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();
    original->readFromFile(inputFile);
    unsigned width = original->width();
    unsigned height = original->height();
    // Create out.png
    PNG* output = setupOutput(width, height);

    // Load our favorite color to color the outline
    RGBAPixel* myPixel = myFavoriteColor(0, 102, 204);

    // Go over the whole image, and if a pixel is likely to be an edge,
    // color it my favorite color in the output
    for (unsigned y = 1; y < height-1; y++) {
        for (unsigned x = 1; x < width-1; x++) {
            // calculate how "edge-like" a pixel is
            double score = edgeScore(original, x, y);
            RGBAPixel* currOutPixel = (*output).getPixel(x, y);
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            if (score > 0.3) {
                currOutPixel->r = myPixel->r;
                currOutPixel->g = myPixel->g;
                currOutPixel->b = myPixel->b;
                currOutPixel->a = myPixel->a;
            } else {
                currOutPixel->r = 255.0;
                currOutPixel->g = 255.0;
                currOutPixel->b = 255.0;
                currOutPixel->a = 0.0;
            }
        }
    }


    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}
