#include "quadtree.hpp"

QuadTree::QuadTree(const Image& image, const EMM& errorMethod, double threshold, int minBlockSize) : image(image), errorMethod(errorMethod), threshold(threshold), minBlockSize(minBlockSize) {}

QuadTree::~QuadTree() {
    delete root;
}

void QuadTree::construct() {
    
}