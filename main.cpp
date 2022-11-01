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
using namespace cs221util;
using namespace std;

#include "lab_intro.h"

string img_input = "img-input/coco.png";

void Flip(string img_path)
{
   PNG ht;
   ht.readFromFile(img_path);
   Block b;
   b.build(ht, 1, 1, 500, 281);
   b.flipHoriz();

   PNG ht_p = ht;
   b.render(ht_p, 1, 1);
   ht_p.writeToFile("soln-img/jdlargeflipcorner.png");
}

void Rotate(string img_path) {
   PNG img;
   img.readFromFile(img_path);
   int cols = 5;
   int rows = 1;

   Chain c(img, cols,rows);
   c.rotate(2);

   PNG res = c.render(cols,rows);
   res.writeToFile("soln-img/rotate.png");
}

void OddReverse(string img_path) {
   PNG img;
   img.readFromFile(img_path);

   int cols = 10;
   int rows = 5;
   Chain c(img, cols,rows);

   c.reverse();
   PNG res = c.render(cols,rows);
   res.writeToFile("soln-img/Odd_Reverse.png");
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
   res.writeToFile("soln-img/Encoded.png");
}


int main()
{
   Flip(img_input);
   Rotate(img_input);
   OddReverse(img_input);
   Encoded(img_input);


   // adding features 
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

   return 0;  
}
