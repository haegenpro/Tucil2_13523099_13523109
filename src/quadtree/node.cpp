#include "node.hpp"

Node::Node(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
    avgColor = Pixel();
    for (auto& childNode : childrenNode) {
        childNode = nullptr;
    }
}

Node::~Node() {
    for (auto* childNode : childrenNode) {
        delete childNode;
    }
}

bool Node::canSplit(int minBlockSize) const {
    int halfWidth = width / 2;
    int halfHeight = height / 2;
    return (halfWidth * halfHeight >= minBlockSize) && (width >= 2) && (height >= 2);
}