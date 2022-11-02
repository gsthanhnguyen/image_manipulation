/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
 **/

#include "chain.h"
#include "block.h"
#include <iostream>
#include "cs221util/PNG.h"
#include "sketchify.h"
using namespace cs221util;
using namespace std;

#include "lab_intro.h"

string img_input = "img-input/coco.png";

void Rotate(string img_path) {
   PNG img;
   img.readFromFile(img_path);
   int cols = 5;
   int rows = 1;

   Chain c(img, cols,rows);
   c.rotate(2);

   PNG res = c.render(cols,rows);
   res.writeToFile("soln-img/out-rotate.png");
   cout << "Exported Rotate" << endl;
}

void OddReverse(string img_path) {
   PNG img;
   img.readFromFile(img_path);

   int cols = 10;
   int rows = 5;
   Chain c(img, cols,rows);

   c.reverse();
   PNG res = c.render(cols,rows);
   res.writeToFile("soln-img/out-reverse.png");
   cout << "Exported Reverse" << endl;
}


void Encoded(string img_path) {
   PNG img, png2;
   img.readFromFile(img_path);
   png2.readFromFile("img-input/locked_icon.png");

   int cols = 40;
   int rows = 20;
   Chain c(img, cols,rows);

   c.reverse();
   c.rotate(2);
   PNG res = c.render(cols,rows);
   res = grayscale(res);
   res = watermark(res, png2);
   res.writeToFile("soln-img/out-encoded.png");
   cout << "Exported Encoded" << endl;
}


int main()
{
   Rotate(img_input);
   OddReverse(img_input);
   Encoded(img_input);


   cs221util::PNG png, png2, result;

   png.readFromFile(img_input);
   result = grayscale(png);
   result.writeToFile("soln-img/out-grayscale.png"); 
   cout << "Exported GrayScale" << endl;

   result = createSpotlight(png, 250, 50);
   result.writeToFile("soln-img/out-spotlight.png");
   cout << "Exported SpotLight" << endl;

   result = ubcify(png);
   result.writeToFile("soln-img/out-ubcify.png");
   cout << "Exported UBCify" << endl;

   png2.readFromFile("img-input/coco_watermark.png");
   result = watermark(png, png2);
   result.writeToFile("soln-img/out-watermark.png");
   cout << "Exported WaterMark" << endl;

   sketchify(img_input, "soln-img/out-sketchify.png");
   cout << "Exported Sketchify" << endl;

   return 0;  
}
