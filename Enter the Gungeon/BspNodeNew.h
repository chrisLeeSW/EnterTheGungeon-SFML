#pragma once
#include "Defines.h"

struct Rect {
    int x;
    int y;
    int width;
    int height;

    Rect() : x(0), y(0), width(0), height(0) {}
    Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
};

class BSPNode {
public:
    BSPNode* left;
    BSPNode* right;
    Rect rect;
    Rect room;

    BSPNode(Rect rect) : rect(rect), left(nullptr), right(nullptr) {}
    ~BSPNode() {
        delete left;
        delete right;
    }
};

class Room1 {
public:
    void Divide(BSPNode* node, int min_width, int min_height, int max_depth, int depth = 0) 
    {
        if (depth >= max_depth || node->rect.width < 2 * min_width || node->rect.height < 2 * min_height)
        {
            node->room.width = node->rect.width * 0.75;
            node->room.height = node->rect.height * 0.75;
            node->room.x = node->rect.x + (node->rect.width - node->room.width) / 2;
            node->room.y = node->rect.y + (node->rect.height - node->room.height) / 2;
            return;
        }

        int hDivider = node->rect.height / 2;
        int wDivider = node->rect.width / 2;

        if (rand() % 2 == 0)
        {
            // 수평 분할
            if (hDivider < 2 * min_height) return;
            node->left = new BSPNode({ node->rect.x, node->rect.y, node->rect.width, hDivider });
            node->right = new BSPNode({ node->rect.x, node->rect.y + hDivider, node->rect.width, node->rect.height - hDivider });
        }
        else
        {
            // 수직 분할
            if (wDivider < 2 * min_width) return;
            node->left = new BSPNode({ node->rect.x, node->rect.y, wDivider, node->rect.height });
            node->right = new BSPNode({ node->rect.x + wDivider, node->rect.y, node->rect.width - wDivider, node->rect.height });
        }

        Divide(node->left, min_width, min_height, max_depth, depth + 1);
        Divide(node->right, min_width, min_height, max_depth, depth + 1);

       
    }
};