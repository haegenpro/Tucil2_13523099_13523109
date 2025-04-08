#ifndef _NODE_H_
#define _NODE_H_

#include <array>
#include "../pixel/pixel.hpp"

class Node {
public:
    int x;
    int y;
    int width;
    int height;
    Pixel avgColor;

    std::array<Node*, 4> childrenNode;

    Node(int x, int y, int width, int height);
    ~Node();
    bool canSplit(int minBlockSize) const;
};

#endif