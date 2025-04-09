#include "quadtree.hpp"

QuadTree::QuadTree(const Image& image, const EMM& errorMethod, double threshold, int minBlockSize, Animation* animation) : image(image), frame(image), errorMethod(errorMethod), threshold(threshold), minBlockSize(minBlockSize), animation(animation), root(nullptr) { }

QuadTree::~QuadTree() {
    clearTree();
}

void QuadTree::setThreshold(double threshold) {
    this->threshold = threshold;
}

double QuadTree::getThreshold() const {
    return threshold;
}

void QuadTree::clearTree() {
    if (!root) return;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            if (current->childrenNode[i]) {
                q.push(current->childrenNode[i]);
                current->childrenNode[i] = nullptr;
            }
        }

        delete current;
    }

    root = nullptr;
    depth = 0;
    nodeCount = 0;
    leafCount = 0;
}

void QuadTree::construct() {
    if (root) {
        clearTree();
    }
    root = new Node(0, 0, image.getWidth(), image.getHeight());
    root->avgColor = meanColorBlock(root->x, root->y, root->width, root->height);

    std::queue<std::pair<Node*, int>> q;
    q.push({root, 0});

    nodeCount = 1;
    depth = 0;

    while (!q.empty()) {
        auto [node, currentDepth] = q.front(); q.pop();
        depth = std::max(depth, currentDepth);

        double error = errorMethod.computeBlockError(image, node->x, node->y, node->width, node->height);

        if (errorMethod.isWithinThreshold(error, threshold) || !node->canSplit(minBlockSize)) {
            leafCount++;
            continue;
        }

        int halfW = node->width / 2;
        int halfH = node->height / 2;

        node->childrenNode[0] = new Node(node->x, node->y, halfW, halfH); // TL
        node->childrenNode[1] = new Node(node->x + halfW, node->y, node->width - halfW, halfH); // TR
        node->childrenNode[2] = new Node(node->x, node->y + halfH, halfW, node->height - halfH); // BL
        node->childrenNode[3] = new Node(node->x + halfW, node->y + halfH, node->width - halfW, node->height - halfH); // BR

        for (auto* child : node->childrenNode) {
            child->avgColor = meanColorBlock(child->x, child->y, child->width, child->height);
            q.push({child, currentDepth + 1});
            nodeCount++;
        }
    }
}

void QuadTree::generateAnimation() {
    if (!animation || !root) return;

    std::queue<const Node*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();

        for (int i = 0; i < size; i++) {
            const Node* node = q.front(); q.pop();

            for (int j = node->x; j < node->x + node->width && j < frame.getWidth(); j++) {
                for (int k = node->y; k < node->y + node->height && k < frame.getHeight(); k++) {
                    frame.setPixelAt(j, k, node->avgColor);
                }
            }
            for (auto* child : node->childrenNode) {
                if (child) q.push(child);
            }
        }

        animation->addFrame(frame);
    }
}

void QuadTree::render(Image& output) {
    if (!root) return;

    std::queue<const Node*> q;
    q.push(root);

    while (!q.empty()) {
        const Node* node = q.front();
        q.pop();

        bool hasChildren = node->childrenNode[0] != nullptr;

        if (!hasChildren) {
            for (int j = node->x; j < node->x + node->width && j < output.getWidth(); j++) {
                for (int k = node->y; k < node->y + node->height && k < output.getHeight(); k++) {
                    output.setPixelAt(j, k, node->avgColor);
                }
            }
        } else {
            for (auto* child : node->childrenNode) {
                if (child != nullptr) {
                    q.push(child);
                }
            }
        }
    }
}

Pixel QuadTree::meanColorBlock(int x, int y, int width, int height){
    long long r = 0, g = 0, b = 0;
    int count = width * height;

    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
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

