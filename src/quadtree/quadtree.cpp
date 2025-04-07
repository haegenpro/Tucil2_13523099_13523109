#include "quadtree.hpp"

QuadTree::QuadTree(const Image& image, const EMM& errorMethod, double threshold, int minBlockSize, double compressionRatio) : image(image), errorMethod(errorMethod), threshold(threshold), minBlockSize(minBlockSize) {
    if (compressionRatio != 0){
        this->threshold = threshold * compressionRatio;
    }
}

QuadTree::~QuadTree() {
    delete root;
}

void QuadTree::construct() {
    root = new Node(0, 0, image.getWidth(), image.getHeight());

    std::queue<std::pair<Node*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        auto [node, tempdepth] = q.front(); q.pop();
        nodeCount++;
        depth = std::max(depth, tempdepth);

        node->avgColor = meanColorBlock(node->x, node->y, node->width, node->height);

        double error = errorMethod.computeBlockError(image, node->x, node->y, node->width, node->height);

        if (error <= threshold || !node->canSplit(minBlockSize)) {
            node->isLeafNode = true;
            leafCount++;
            continue;
        }

        node->isLeafNode = false;

        int halfW = node->width / 2;
        int halfH = node->height / 2;

        node->childrenNode[0] = new Node(node->x, node->y, halfW, halfH); // TL
        node->childrenNode[1] = new Node(node->x + halfW, node->y, node->width - halfW, halfH); // TR
        node->childrenNode[2] = new Node(node->x, node->y + halfH, halfW, node->height - halfH); // BL
        node->childrenNode[3] = new Node(node->x + halfW, node->y + halfH, node->width - halfW, node->height - halfH); // BR

        for (auto* child : node->childrenNode) {
            q.push({child, tempdepth + 1});
        }
    }
}

void QuadTree::render(Image& output) const {
    auto draw = [&](const Node* node, auto&& self) -> void {
        if (node->isLeafNode) {
            for (int i = node->x; i < node->x + node->width; ++i) {
                for (int j = node->y; j < node->y + node->height; ++j) {
                    output.setPixelAt(i, j, node->avgColor);
                }
            }
        } else {
            for (auto* child : node->childrenNode) {
                if (child) self(child, self);
            }
        }
    };
    draw(root, draw);
}

Pixel QuadTree::meanColorBlock(int x, int y, int width, int height){
    long long r = 0, g = 0, b = 0;
    int count = width * height;

    for (int i = x; i < x + width; ++i) {
        for (int j = y; j < y + height; ++j) {
            Pixel p = image.getPixelAt(i, j);
            r += p.getRed();
            g += p.getGreen();
            b += p.getBlue();
        }
    }
    return Pixel(r / count, g / count, b / count, 255);
}

int QuadTree::getTotalNodes() const { return nodeCount; }
int QuadTree::getTotalLeaves() const { return leafCount; }
int QuadTree::getDepth() const { return depth; }
