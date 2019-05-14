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
//返回一个指向新树根的指针
TreeNode *Insert(int x, TreeNode *node)
{
    if(node == nullptr){
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

//返回指向根节点的指针
TreeNode *Insert_tree(int x, TreeNode *node)
{
    if(node == nullptr){
        node = (TreeNode*)malloc(sizeof(TreeNode));
        if(node == nullptr)
            printf("Out of space!!");
        else{
            node->data = x;
            node->leftchild = node->rightchild = nullptr;
        }
    }
    else if(x < node->data)
        node->leftchild = Insert_tree(x, node->leftchild);
    else if(x > node->data)
        node->rightchild = Insert_tree(x, node->rightchild);

    return node;
}

//构建一棵二叉树
TreeNode *build_tree(char *str, TreeNode *node)
{
    int i = 0;
    int num = 0;
//    TreeNode *T;
    while(str[i]){
        if(str[i] >= '0' && str[i] <= '9'){
            num = str[i]-'0';
            node = Insert_tree(num, node);
        }
        else{
            printf("请输入0~9的数字");
            break;
        }
        i++;
    }
    return node;
}

//删除节点,返回根节点
TreeNode *Delete(int x, TreeNode *node)
{
    TreeNode *T;
    if(node == nullptr)
        printf("未找到节点");
    else if(x < node->data){
        node->leftchild = Delete(x, node->leftchild);
    }
    else if(x > node->data){
        node->rightchild = Delete(x, node->rightchild);
    }
    //如果被删除的节点有左右孩子
    else if(node->leftchild && node->rightchild){
        T = FindMin(node->rightchild);//将该节点右子树中的最小节点赋给新节点T
        node->data = T->data;//将值赋值给即将被删除的节点
        //将右子树中最小的节点递归删除,因为该节点已经提到了被删除的节点的位置
        //删除后返回当前节点的右节点
        node->rightchild = Delete(node->data, node->rightchild);
    }
    //如果被删除的节点只有一个孩子或者没有孩子节点
    else{
        T = node;//将指向即将被删除的节点的指针赋给T
        if(node->rightchild == nullptr)
            //如果该节点没有右孩子则把指向左孩子的指针赋给指向被删除节点的指针
            //这样被删除的节点就变成了该节点的父节点的孩子,而该节点也只有T指针指向它
            node = node->leftchild;
        else if(node->leftchild == nullptr)
            node = node->rightchild;
        free(T);//将T指针释放,完成删除节点操作
    }
    return node;
}

//打印节点
void print(TreeNode *T)
{
    printf("%d", T->data);
}

//先序遍历节点
void PreOrder(TreeNode *T)
{
    if(T != nullptr){
        print(T);
        PreOrder(T->leftchild);
        PreOrder(T->rightchild);
    }
}

//中序遍历节点
void InOrder(TreeNode *T)
{
    if(T != nullptr){
        InOrder(T->leftchild);
        print(T);
        InOrder(T->rightchild);
    }
}

//后序遍历节点
void PostOrder(TreeNode *T)
{
    if(T != nullptr){
        PostOrder(T->leftchild);
        PostOrder(T->rightchild);
        print(T);
    }
}

TreeNode *menu_insert(TreeNode *T)
{
    int a;
    TreeNode *node;
    printf("请输入要插入的数字:");
    scanf("%d", &a);
    node = Insert_tree(a, T);
    printf("中序遍历二叉树:");
    InOrder(T);
    printf("\n");
    return node;
}

void menu_Findmin(TreeNode *T)
{
    TreeNode *min_node;
    printf("这棵树中最小值为:");
    min_node = FindMin(T);
    printf("%d\n", min_node->data);
}

void menu_Findmax(TreeNode *T)
{
    TreeNode *max_node;
    printf("这棵树中最大值为:");
    max_node = FindMax(T);
    printf("%d\n", max_node->data);
}

void menu_Find(TreeNode *T)
{
    int num = 0;
    TreeNode *node;
    printf("请输入想要查找的值:");
    scanf("%d", &num);
    node = Find(num, T);
    if(node != nullptr)
        printf("找到了%d节点\n", node->data);
    else
        printf("未找到该节点\n");

}

TreeNode *menu_Delete(TreeNode *T)
{
    int num = 0;
    TreeNode *node;
    printf("请输入要删除的节点:");
    scanf("%d", &num);
    node = Delete(num, T);
    printf("已删除该节点:\n中序遍历该树:\n");
    InOrder(node);
    printf("\n");
    return node;
}

void menu(int flag, TreeNode *T)
{
    switch (flag) {
    case 1:
        T = menu_insert(T);
        break;
    case 2:
        menu_Find(T);
        break;
    case 3:
        menu_Findmax(T);
        break;
    case 4:
        menu_Findmin(T);
        break;
    case 5:
        T = menu_Delete(T);
        break;
    default:
        break;
    }
}

int main()
{
    TreeNode *T = (TreeNode*)malloc(sizeof(TreeNode));
    T = MakeEmpty(T);
    char buf[100];
    printf("请输入节点值构建二叉树:");
    scanf("%s", buf);
    T = build_tree(buf, T);
    printf("中序遍历二叉树:");
    InOrder(T);
    printf("\n");

    printf("1. 插入节点\n");
    printf("2. 查询节点\n");
    printf("3. 查询最大节点\n");
    printf("4. 查询最小节点\n");
    printf("5. 删除节点");

    int flag = 0;
    while(flag < 6){
        printf("请输入要进行的操作:\n");
        scanf("%d", &flag);
        menu(flag, T);
    }

    return 0;
}
