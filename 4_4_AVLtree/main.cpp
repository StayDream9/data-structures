#include <iostream>

using namespace std;

typedef int ElementType;
typedef struct AvlNode *AvlTree;
typedef struct AvlNode *Position;

AvlTree MakeEmpty(AvlTree T);//初始化树
Position Find(ElementType x, AvlTree T);//查找节点
Position FindMin(AvlTree T);//查找最小节点
Position FindMax(AvlTree T);//查找最大节点
AvlTree Insert(ElementType x, AvlTree T);//插入节点
AvlTree Delete(ElementType x, AvlTree T);//删除节点
ElementType Retrieve(Position P);

struct AvlNode{
    ElementType Element;
    AvlTree leftchild;
    AvlTree rightchild;
    int height;
};

static int Height(Position P)
{
    if(P == nullptr)
        return -1;
    else
        return P->height;
}

//初始化树
AvlTree MakeEmpty(AvlTree T)
{
    if(T != nullptr){
        MakeEmpty(T->leftchild);
        MakeEmpty(T->rightchild);
        free(T);
    }
    return T;
}

//查找节点
Position Find(ElementType x, AvlTree T)
{
    if(T == nullptr)
        return nullptr;
    else if(x < T->Element)
        return Find(x, T->leftchild);
    else if(x > T->Element)
        return Find(x, T->rightchild);
    else
        return T;
}

//查找最小节点(递归)
Position FindMin(AvlTree T)
{
    if(T == nullptr)
        return nullptr;
    else if(T->leftchild != nullptr)
        return FindMin(T->leftchild);
    else
        return T;
}

//查找最大节点(非递归)
Position FindMax(AvlTree T)
{
    if(T != nullptr)
        while (T->rightchild != nullptr)
            T = T->rightchild;
    return T;
}

//左右子树的最大高度
static int Max(int left, int right)
{
    return left > right ? left : right;
}

//左子树的单旋转
static Position SingleRotateWithLeft(Position k2)
{
    Position k1;
    k1 = k2->leftchild;
    k2->leftchild = k1->rightchild;
    k1->rightchild = k2;

    k2->height = Max(Height(k2->leftchild), Height(k2->rightchild)) + 1;
    k1->height = Max(Height(k1->leftchild), k2->height) + 1;

    return k1;
}

//右子树的单旋转
static Position SingleRotateWithRight(Position k1)
{
    Position k2;
    k2 = k1->rightchild;
    k1->rightchild = k2->leftchild;
    k2->leftchild = k1;

    k1->height = Max(Height(k1->leftchild), Height(k1->rightchild)) + 1;
    k2->height = Max(k1->height,Height(k2->rightchild)) + 1;

    return k2;
}

//左子树的双旋转
static Position DoubleRotateWithLeft(Position k3)
{
    k3->leftchild = SingleRotateWithRight(k3->leftchild);

    return SingleRotateWithLeft(k3);
}

//右子树的双旋转
static Position DoubleRotateWithRight(Position k1)
{
    k1->rightchild = SingleRotateWithLeft(k1->rightchild);

    return SingleRotateWithRight(k1);
}


//节点的插入
AvlTree Insert(ElementType x, AvlTree T)
{
    if(T == nullptr){
        T = (AvlTree)malloc(sizeof(struct AvlNode));
        if(T == nullptr)
            printf("Out of space!!");
        else{
            T->Element = x;
            T->height = 0;
            T->leftchild = T->rightchild = nullptr;
        }
    }
    //x插入左子树中
    else if(x < T->Element){
        T->leftchild = Insert(x, T->leftchild);
        if(Height(T->leftchild) - Height(T->rightchild) == 2){
            if(x < T->leftchild->Element)
                T = SingleRotateWithLeft(T);//单旋转
            else
                T = DoubleRotateWithLeft(T);//双旋转
        }
    }
    //x插入右子树中
    else if(x > T->Element){
        T->rightchild = Insert(x, T->rightchild);
        if(Height(T->rightchild) - Height(T->leftchild) == 2){
            if(x > T->rightchild->Element)
                T = SingleRotateWithRight(T);//单旋转
            else
                T = DoubleRotateWithRight(T);//双旋转
        }
    }

    T->height = Max(Height(T->leftchild), Height(T->rightchild)) + 1;
    return T;
}

ElementType Retrieve( Position P )
{
    return P->Element;
}

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
