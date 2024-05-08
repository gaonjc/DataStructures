#include <stdlib.h>
#include <stdio.h>

#define NOT_FOUND 8 //precompiled directives

typedef struct _node{
    int data;
    char name;
    struct _node *left;
    struct _node *right;
    
} Node;

typedef struct _tree
{
    int count;
    Node* root;
} Tree;

Node* create_node(int val, char c) {
    
    Node* n0;
    n0 = NULL;
    n0 = (Node*)malloc(sizeof(Node)); 
    n0->data = val;
    n0->left = NULL;
    n0->right = NULL;
    n0->name = c;
    return n0;
} 


Tree* create_tree() {
    Tree* my_new_tree = (Tree*)malloc(sizeof(Tree)); 
    my_new_tree->count = 0;
    my_new_tree->root = NULL;
    return my_new_tree;
} 
int add2node(Node **tmp, Node* n)   //** address to data// The double pointer allows the function to modify the pointer that is passed to it, type Node, stores the memory address of a pointer to node
/*The pointer to a pointer in C is used when we want to store the address of another pointer.
 The first pointer is used to store the address of the variable. And the second pointer is used to store the address of the first pointer*/
{
    if (*tmp == NULL){
        *tmp = n;
        return 0;
    }
    if ((*tmp)->data < n->data)
        return add2node(&(*tmp)->right, n); //&* returns the address of a pointer to a node
    else
        return add2node(&(*tmp)->left, n);
}
int add_node(Tree* t, Node* n) {
    if (t == NULL)
        return -1;
    if (t->root == NULL) {
        t->root = n;
        ++t->count;  
        return 0;
    }
    Node* tmp = t->root;
    
        if (n->data > tmp->data) {
            add2node(&tmp->right, n);
            
        }
        else
            add2node(&tmp->left, n);
        
        ++t->count;
        return 0;
    

}

Node* copy_tree_n(Node* roote)
{   
    if (roote == NULL)
        return NULL;
    
    
    Node* tmp = create_node(roote->data, roote->name);
    
    tmp->left = copy_tree_n(roote->left);
    tmp->right = copy_tree_n(roote->right);

    return tmp;

} 

Tree* copy_tree(Tree* t)
{   
    if (t->root == NULL)
        return NULL;
    Tree* copy = create_tree();
    copy->root = copy_tree_n(t->root);
    copy->count = t->count;
    return copy;
}

int print_tree(Node* roote) {
    if (roote == NULL)
        return 0;

    
    print_tree(roote->right);
    
    printf(" %d ", roote->data);
    
    print_tree(roote->left);

    return 0;
}



int find_max(Node* roote) {
    if (roote == NULL)
        return 0;
    
    int left = find_max(roote->left);
    int right = find_max(roote->right);

    if(left > right)
        return 1 + left;
    return 1 + right;
}

int find_max_b(Node* roote) {
    if (roote == NULL)
        return 0;
    
    int left = find_max_b(roote->left);
    int right = find_max_b(roote->right);

    if(left > right)
        return roote->data + left;
    return roote->data + right;
}

int find_pid(Node* roote, int val) {
    if (roote == NULL)
        return 0;

    int count = 0;
    if(roote->data == val)
        ++count;
    

    count += find_pid(roote->left, val);
    count += find_pid(roote->right, val);


    return count;
}

int find_char(Node* roote, char c) {
    if (roote == NULL)
        return 0;

    int count = 0;
    if(roote->name == c)
        ++count;
    

    count += find_char(roote->left, c);
    count += find_char(roote->right, c);


    return count;
}

void print_even_pids(Node* roote)
{
    if(roote==NULL)
        return;
    if (roote->data % 2 == 0)
        printf("DATA %d is even with name %c \n", roote->data, roote->name);
    
    print_even_pids(roote->left);
    print_even_pids(roote->right);

}



void print_lvl(Node* roote, int lvl)
{
    if (roote==NULL)
        return;
    if (lvl == 1)   {
        printf(" %d ", roote->data);
    }
    else
    {
        print_lvl(roote->left, lvl-1);
        print_lvl(roote->right, lvl-1);      
    }


}


void print_all_lvls(Node* roote){
    for (int ix=0; ix<=find_max(roote); ++ix)
    {
        print_lvl(roote, ix);
        printf("\n");
    }
}

/*int sum_tree(Node* roote) {       //also works
    if (roote == NULL)
        return 0;
    
 
    


    return sum_tree(roote->right)+roote->data+sum_tree(roote->left);

}*/

int sum_tree(Node* roote) {
    if (roote == NULL)
        return 0;
    int sum = 0;
    sum += sum_tree(roote->right);
    sum += sum_tree(roote->left);
    sum+=(roote->data);

    return sum;
}


int remove_node(Tree* t, int val) {
    if (t == NULL)
        return -1;
    if (t->root == NULL)
        return -1;

    Node** pre = &t->root;
    Node* item = t->root;

    while(item->data != val && item != NULL) {
        if(val > item->data) {
            pre = &item->right;
            item = item->right;
        } else {
            pre = &item->left;
            item = item->left;
        }
    }

    if(item == NULL)
        return NOT_FOUND;

    --t->count;

    if(item->left == NULL && item->right == NULL) {
        *pre = NULL;
        free(item);
        return 0;
    }

    if(item->left == NULL) {
        *pre = item->right;
        free(item);
        return 0;
    }

    if(item->right == NULL) {
        *pre = item->left;
        free(item);
        return 0;
    }

    Node** preMinNode = &item->right;
    Node* minNode = item->right;

    while(minNode->left != NULL) {
        preMinNode = &minNode->left;
        minNode = minNode->left;
    }

    *preMinNode = minNode->right;
    *pre = minNode;
    minNode->left = item->left;
    minNode->right = item->right;

    free(item);

    return 0;
}

/*

functions that prints all the nodes that are n levels down from the root element.
print_lvl_down and print_lvls_down
 */

void print_lvl_down(Node* roote, int lvl) // same as print lvl
{
    if (roote==NULL)
        return;
    if (lvl == 0)   {
        printf(" %d ", roote->data);
    }
    else
    {
        print_lvl_down(roote->left, lvl-1);
        print_lvl_down(roote->right, lvl-1);      
    }


}

void print_lvls_down_n(Node* roote, int n){ //prints only the one level n
    print_lvl_down(roote, n);
}


int main() {

    Tree* tree = create_tree();
    Node* n1 = create_node(4, 'a');
    
    add_node(tree, n1);
    add_node(tree, create_node(7,'a'));
    add_node(tree, create_node(9,'b'));
    add_node(tree, create_node(3,'a'));
    add_node(tree, create_node(8,'d'));
    add_node(tree, create_node(6,'a'));
    add_node(tree, create_node(-3,'c'));
    add_node(tree, create_node(15,'a'));
    add_node(tree, create_node(9,'b'));

    //printf("%d \n\n", find_max(n1));
    
    //Tree* copied = copy_tree(tree);

    print_all_lvls(tree->root);
    printf("\n");
    print_lvls_down_n(tree->root, 2);

    /*print_tree(copied->root);
    printf("\n  %d ", copied->count);
    printf("\n  %d is the max branch value \n", find_max_b(tree->root));
    print_even_pids(tree->root);
    printf("find how many pid Nodes at 9: (%d) \n", find_pid(tree->root, 9));
    printf("find how many char Nodes with b: (%d) \n", find_char(tree->root, 'b'));
    */
    
    /*print_tree(n1);
    remove_node(tree, 7);

    print_tree(n1);

    printf("\n %d ",sum_tree(n1));*/

    return 0;
}