#ifndef AVLTREE_H
#define AVLTREE_H

#include "Student.h"

struct Node {
    Student data;
    Node* left;
    Node* right;
    int height;

    Node(Student s) {
        data = s;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    Node* root;
    int totalNodes;

    int getHeight(Node* node);
    int getBalance(Node* node);

    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);

    Node* insert(Node* node, Student student);

    void inOrder(Node* node, int& position);

    Node* search(Node* node, int skill_score);

public:
    AVLTree();

    void insertStudent(Student student);

    void showRanking();

    void searchBySkillScore(int score);

    void showStatistics();
};

#endif
