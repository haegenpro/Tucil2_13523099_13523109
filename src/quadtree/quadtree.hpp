#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include <queue>
#include "../error_measurement/emm.hpp"
#include "../image/image.hpp"
#include "node.hpp"
#include <algorithm>
#include <functional>

class QuadTree {
private:
    const Image& image;
    const EMM& errorMethod;
    double threshold;
    int minBlockSize;
    Node* root;
    int depth = 0;
    int leafCount = 0;
    int nodeCount = 0;

    Pixel meanColorBlock(int x, int y, int width, int height);
    
public:
    QuadTree(const Image& image, const EMM& errorMethod, double threshold, int minBlockSize);
    QuadTree(const Image& image, const EMM& errorMethod, double threshold, int minBlockSize, double compressionRatio);
    ~QuadTree();
    void construct();
    void render(Image& output) const;
    int getTotalNodes() const;
    int getTotalLeaves() const;
    int getDepth() const;
};

#endif