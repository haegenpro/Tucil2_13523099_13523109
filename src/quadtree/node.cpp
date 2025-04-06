#include "node.hpp"

Node::Node(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
    avgColor = Pixel();
    isLeafNode = true;
    for (auto& childNode : childrenNode) {
        childNode = nullptr;
    }
}

Node::~Node() {
    for (auto* childNode : childrenNode) {
        delete childNode;
    }
}

bool Node::isSplit() const {
    return !isLeafNode;
}

bool Node::canSplit(int minBlockSize) const {
    return (width * height >= minBlockSize);
}