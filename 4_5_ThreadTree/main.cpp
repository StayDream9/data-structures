#include <iostream>

using namespace std;
typedef char TElemType;

typedef enum {Link, Thread} PointerTag;// Link(0):指针,Thread(1):线索
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *leftchild;
    struct BiThrNode *rightchild;
    PointerTag LTag, RTag;// 左右标志
}BiThrNode, *BiThrTree;
TElemType Nil = ' ';// 字符型以空格符为空
BiThrTree pre;// 全局变量,始终指向刚刚访问过的结点


//按先序输入二叉线索树中节点的值,构造二叉线索树T
//第一种创建方式：通过返回指针创建二叉树(有返回值)
BiThrTree Create_BiThrTree_1(BiThrTree T)
{
    TElemType ch;
    scanf("%c", &ch);
    if(ch == Nil)
        T = nullptr;
    else {
        T = (BiThrTree)malloc(sizeof(BiThrNode));
        if(!T)
            exit(0);
        T->data = ch;//生成根节点（先序）
        T->leftchild = Create_BiThrTree_1(T->leftchild);
        if(T->leftchild)
            T->LTag = Link;
        T->rightchild = Create_BiThrTree_1(T->rightchild);
        if(T->rightchild)
            T->RTag = Link;
    }
    return T;
}

//第二种方法,传入BiThrTree的指针的地址进入函数
void Create_BiThrTree_2(BiThrTree &T)
{
    TElemType ch;
    scanf("%c", &ch);
    if(ch == Nil)
        T = nullptr;
    else {
        T = (BiThrTree)malloc(sizeof(BiThrNode));
        if(!T)
            exit(0);
        T->data = ch;//生成根节点（先序）
        Create_BiThrTree_2(T->leftchild);
        if(T->leftchild)
            T->LTag = Link;
        Create_BiThrTree_2(T->rightchild);
        if(T->rightchild)
            T->RTag = Link;
    }
}

//第三种创建方式:通过传入指向指针的指针创建二叉树(二级指针)(无返回值)
void Create_BiThrTree_3(BiThrTree *T)
{
    TElemType ch;
    scanf("%c", &ch);
    if(ch == Nil)
        *T = nullptr;
    else{
        *T = (BiThrTree)malloc(sizeof(BiThrNode));
        if(!*T)
            exit(0);
        (*T)->data = ch;//生成根节点(先序)
        Create_BiThrTree_3(&(*T)->leftchild);//递归构造左子树
        if((*T)->leftchild)//有左孩子
            (*T)->LTag = Link;
        Create_BiThrTree_3(&(*T)->rightchild);//递归构造右子树
        if((*T)->rightchild)//有右孩子
            (*T)->RTag = Link;
    }
}

//中序遍历进行中序线索化(没带头结点)
void InThreading(BiThrTree p)
{
    if(p){
        InThreading(p->leftchild);
        if(!p->leftchild){ //没有左孩子
            p->LTag = Thread; //前驱线索
            p->leftchild = pre; //左孩子指针指向前驱
        }
        else
            p->LTag = Link;
        if(!pre->rightchild){ //前驱没有右孩子
            pre->RTag = Thread;//后继线索
            pre->rightchild = p;//前驱右孩子指针指向后继(当前节点p)
        }
        else
            pre->RTag = Link;
        pre = p; //保持pre指向p的前驱
        InThreading(p->rightchild); //递归右子树线索化
    }
}

//第一种方法:传入指针地址
//带头节点的二叉树中序线索化
void InOrderThreading(BiThrTree &Thrt, BiThrTree T)
{
    Thrt = (BiThrTree)malloc(sizeof(BiThrNode));//建头结点
    if(!Thrt)
        exit(0);
    Thrt->LTag = Link;//头结点有左孩子,若树非空,则其左孩子为树根
    Thrt->RTag = Link;//头结点的右孩子指针为右线索
    Thrt->rightchild = Thrt;//初始化时右指针指向自己
    if(!T)
        Thrt->leftchild = Thrt;//若树为空,则左指针也指向自己
    else{
        Thrt->leftchild = T;
        pre = Thrt;//头结点的左孩子指向根,pre初始指向头结点
        InThreading(T);
        pre->RTag = Thread;
        pre->rightchild = Thrt;

        Thrt->rightchild = pre;//头结点的右线索指向pre
    }
}

//第二种方法:传入指向指针的指针
// 中序遍历二叉树T,并将其中序线索化,Thrt指向头结点。
void InOrderThreading(BiThrTree *Thrt,BiThrTree T)
{
    *Thrt=(BiThrTree)malloc(sizeof(BiThrNode)); // 建头结点
    if(!*Thrt)
    exit(0);
    (*Thrt)->LTag=Link; //标志左孩子为指针
    (*Thrt)->RTag=Thread; //标志右孩子为线索
    (*Thrt)->rightchild=*Thrt; // 右指针回指
    if(!T) // 若二叉树空，则左指针回指
    (*Thrt)->leftchild=*Thrt;
    else
    {
    (*Thrt)->leftchild=T; //头结点左指针指向树的根
    pre = *Thrt;
    InThreading(T); // 中序遍历进行中序线索化
    pre->RTag=Thread; // 最后一个结点线索化
    pre->rightchild=*Thrt;
    (*Thrt)->rightchild=pre;
    }
}

//中序遍历二叉线索树的非递归算法
void InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p=T->leftchild; // p指向根结点
    while(p != T)
    { // 空树或遍历结束时,p==T
        while(p->LTag == Link)
            p = p->leftchild;
        cout << p->data;
        while(p->RTag == Thread && p->rightchild != T)
        {
            p = p->rightchild;
            cout << p->data;
        }
        p = p->rightchild;
    }
}

// 中序遍历二叉线索树T(头结点)的非递归算法。
int InOrderTraverse_Thr(BiThrTree T,int(*Visit)(TElemType))
{
    BiThrTree p;
    p=T->leftchild; // p指向根结点
    while(p != T)
    { // 空树或遍历结束时,p==T
        while(p->LTag == Link)
            p = p->leftchild;
        if(!Visit(p->data)) // 访问其左子树为空的结点
            return 0;
        while(p->RTag == Thread && p->rightchild != T)
        {
            p = p->rightchild;
            Visit(p->data); // 访问后继结点
        }
        p = p->rightchild;
    }
    return 1;
}
int vi(TElemType c)
{
    printf("%c ",c);
    return 1;
}

int main()
{
    BiThrTree H,T;
    T = (BiThrTree)malloc(sizeof(BiThrNode));
    printf("请按先序输入二叉树(如:ab三个空格,表示a为根结点,"
    "b为左子树的二叉树)\n");
//    T = Create_BiThrTree_1(T);
//    Create_BiThrTree_2(T);
    Create_BiThrTree_3(&T); // 按先序产生二叉树
    InOrderThreading(H,T); // 中序遍历，并中序线索化二叉树
    printf("中序遍历(输出)二叉线索树:\n");
    InOrderTraverse_Thr(H);
//    InOrderTraverse_Thr(H,vi); // 中序遍历(输出)二叉线索树
    printf("\n");
//    system("pause");
    return 0;
}
