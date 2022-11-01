#include "block.h"
#include <cmath>
#include <iostream>

int Block::width() const
{
    /* YOUR CODE HERE */
    return data.size();
}
int Block::height() const
{
    /* YOUR CODE HERE */
    return data[0].size();
}
 
void Block::render(PNG &im, int column, int row) const
{
    /* YOUR CODE HERE */
    for (int x = column; x < column + width(); x++)
    {
        for (int y = row; y < row + height(); y++)
        {
            RGBAPixel *pixel = im.getPixel(x, y);

            // get r,g,b,a value from block's pixel
            unsigned char block_pixel_red = data[x - column][y - row].r;
            unsigned char block_pixel_green = data[x - column][y - row].g;
            unsigned char block_pixel_blue = data[x - column][y - row].b;
            double block_pixel_alpha = data[x - column][y - row].a;

            // render block's pixel onto image's pixel
            pixel->r = block_pixel_red;
            pixel->g = block_pixel_green;
            pixel->b = block_pixel_blue;
            pixel->a = block_pixel_alpha;
        }
    }
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
    /* YOUR CODE HERE */
    for (int x = column; x < column + width; x++)
    {
        vector<RGBAPixel> block_column;
        for (int y = row; y < row + height; y++)
        {
            RGBAPixel *pixel = im.getPixel(x, y);
            block_column.push_back(*pixel);
        }
        data.push_back(block_column);
    }
}

void Block::flipVert()
{
    /* YOUR CODE HERE */
    vector<vector<RGBAPixel>> temp_data;
    for (int x = 0; x < width(); x++)
    {
        vector<RGBAPixel> block_column;
        for (int y = height() - 1; y >= 0; y--)
        {
            block_column.push_back(data[x][y]);
        }
        temp_data.push_back(block_column);
    }
    data.swap(temp_data);
}

void Block::flipHoriz()
{
    /* YOUR CODE HERE */
    vector<vector<RGBAPixel>> temp_data;
    for (int x = width() - 1; x >= 0; x--)
    {
        temp_data.push_back(data[x]);
    }
    data.swap(temp_data);
}

void Block::rotateRight()
{
    /* YOUR CODE HERE */
    vector<vector<RGBAPixel>> temp_data;
    for (int x = 0; x < width(); x++)
    {
        vector<RGBAPixel> temp_column;
        temp_data.push_back(temp_column);
    }

    for (int x = 0; x < width(); x++)
    {
        for (int y = height() - 1; y >= 0; y--)
        {
            temp_data[(height() - 1) - y].push_back(data[x][y]);
        }
    }
    data.swap(temp_data);
}
