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

void TestFlip()
{
   PNG ht;
   ht.readFromFile("img-input/JDP_MV_Road.png");
   Block b;
   b.build(ht, 0, 0, 800, 1120);
   cout << "got here" << endl;
   b.flipHoriz();
   cout << "got here" << endl;

   PNG ht_p = ht;
   b.render(ht_p, 0, 0);
   cout << "got here" << endl;
   ht_p.writeToFile("soln-img/jdlargeflipcorner.png");
}


int main()
{
   /**
    * Write your own functions to print out variants of different images!
    * You'll find the outputs in the "images" folder.
    * A sample function has been written for you. 
    */
   TestFlip();

   // adding features 
   cs221util::PNG png, png2, result;

   png.readFromFile("img-input/smiling-cat.png");
   result = grayscale(png);
   result.writeToFile("soln-img/out-grayscale.png"); 

   result = createSpotlight(png, 300, 300);
   result.writeToFile("soln-img/out-spotlight.png");

   result = ubcify(png);
   result.writeToFile("soln-img/out-ubcify.png");

   png2.readFromFile("overlay.png");
   result = watermark(png, png2);
   result.writeToFile("soln-img/out-watermark.png");

   return 0;  
}
