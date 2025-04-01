#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <iostream>
#include <stb_image.h>
#include <stb_image_write.h>

using namespace std;

class QuadTree {
    private:
        int width, height;
        int minBlockSize;
        int blockSize;
        int* imageData; // Flattened array for RGB channels
        QuadTree* children[4]; // Pointers to child nodes
        int x, y; // Position of the node in the image
        
    public:
        QuadTree(int w, int h, int minSize) : width(w), height(h), minBlockSize(minSize) {
            blockSize = w*h;
            imageData = new int[width * height * 3]; // Initialize flattened imageData array
        }

        ~QuadTree() {
            delete[] imageData; // Clean up memory
        }
        QuadTree(const QuadTree& other, int quadrant) : width(other.width / 2), height(other.height / 2), minBlockSize(other.minBlockSize) {
            blockSize = other.blockSize / 2;
            imageData = new int[width * height * 3]; // Initialize flattened imageData array
            x = other.x + (quadrant % 2) * blockSize;
            y = other.y + (quadrant / 2) * blockSize;
            for (int i = 0; i < width * height * 3; ++i) {
                imageData[i] = other.imageData[i];
            }
            *other.children[quadrant-1] = *this;
        }
};