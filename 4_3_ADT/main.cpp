#include <iostream>

using namespace std;

typedef struct node TreeNode;

struct node{
    int data;

    TreeNode *leftchild;
    TreeNode *rightchild;
};

//初始化
TreeNode *MakeEmpty(TreeNode *node)
{
    if(node != nullptr){
        MakeEmpty(node->leftchild);
        MakeEmpty(node->rightchild);
        free(node);
    }
    return nullptr;
}

//查找
TreeNode *Find(int x, TreeNode *node)
{
    if(node == nullptr)
        return nullptr;
    if(x < node->data)
        return Find(x, node->leftchild);
    else if(x > node->data)
        return Find(x, node->rightchild);
    else
        return node;
}

//查找最小元(递归算法)
TreeNode *FindMin(TreeNode *node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->leftchild == nullptr)
        return node;
    else
        return FindMin(node->leftchild);
}

//查找最小元(非递归算法)
TreeNode *FindMin_(TreeNode *node)
{
    if(node == nullptr)
        return nullptr;
    while (node->leftchild != nullptr)
        node = node->leftchild;
    return node;
}

//查找最大元(递归算法)
TreeNode *FindMax(TreeNode *node)
{
    if(node == nullptr)
        return nullptr;
    else if(node->rightchild == nullptr)
        return node;
    else
        return FindMax(node->rightchild);
}


//插入
TreeNode *Insert(int x, TreeNode *node)
{
    if(x == node->data)
        return node;
    else if(node == nullptr){
        node = (TreeNode*)malloc(sizeof(TreeNode));
        if(node == nullptr)
            printf("Out of space!!");
        else{
            node->data = x;
            node->leftchild = node->rightchild = nullptr;
        }
    }
    else if(x < node->data)
        return Insert(x, node->leftchild);
    else if(x > node->data)
        return Insert(x, node->rightchild);

    return node;
}

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
