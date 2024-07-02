#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

struct Node {
    struct Node *left;
    struct Node *right;
    int value; 
};

void print_tree(struct Node *node) {
    if(node == NULL) return;

    printf("\n%3d|", node->value);

    if(node->left != NULL) {
        printf("<-%d ", node->left->value);
    }
    if(node->right != NULL) {
        printf("%d->", node->right->value);
    }
    print_tree(node->left);
    print_tree(node->right);
}

void insert_value(struct Node *node, int value) {
    if(node->value == 0) {
        node->value = value; 
        return;
    }
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->value = value;

    if(value >= node->value) {
        if(node->right == NULL) {
            node->right = new_node;
            return;
        }

        insert_value(node->right, value);
    } 
    if(value <= node->value) {
        if(node->left == NULL) {
            node->left = new_node;
            return;
        }
        insert_value(node->left, value);
    } 
}

struct Node* search(struct Node *root, int value) {
    if(root == NULL || root->value == value) return root;

    if(value > root->value && root->right != NULL) return search(root->right, value);

    if(value < root->value && root->left != NULL) return search(root->left, value);
    
}

struct Node* max_value(struct Node *root) {
    if(root->right == NULL) return root;

    if(root->right != NULL) return max_value(root->right); 
}

struct Node* min_value(struct Node *root) {
    if(root->left == NULL) return root;

    if(root->left != NULL) return min_value(root->left); 
}



void remove_value(struct Node **node, int value) {
    struct Node *helper = *node;
    if((*node)->value == value && (*node)->left != NULL) {
        *node = (*node)->left;
        (*node)->right = helper->right;
        return;
    }
    if((*node)->value == value && (*node)->right != NULL) {
        *node = (*node)->right;
        (*node)->left = helper->left;
        return;
    }

    if(value > (*node)->value) remove_value(&(*node)->right, value);
    if(value < (*node)->value) remove_value(&(*node)->left, value);
}

int find_height(struct Node *node) {
    if(node == NULL) return 0;    
    int right_side = find_height(node->right);
    int left_side = find_height(node->left);

    return 1 + MAX(right_side, left_side);
}

void invert(struct Node *root) {
    if(root->left == NULL && root->right == NULL) {
        return;
    }

    struct Node helper = *root;
    root->left = root->right;
    root->right = helper.left;

    if(root->left != NULL) invert(root->left);
    if(root->right != NULL) invert(root->right);
} 


int main(void) {
    srand(time(NULL));
    struct Node *root = (struct Node*)malloc(sizeof(struct Node));

    insert_value(root, 5); 
    insert_value(root, 3); 
    insert_value(root, 4); 
    insert_value(root, 1); 
    insert_value(root, 0); 
    insert_value(root, 2); 
    insert_value(root, 7); 
    insert_value(root, 6); 
    insert_value(root, 8); 
    insert_value(root, 9); 
    insert_value(root, 10); 
    
    print_tree(root);
    struct Node *value = search(root, 5);
    printf("\n\n------------\n");
    print_tree(value);

    
    printf("\n\n------------\n");
    struct Node *max_v = max_value(root);
    printf("O maior valor é %d\n", max_v->value);

    printf("\n\n------------\n");
    struct Node *min_v = min_value(root);
    printf("O menor valor é %d\n", min_v->value);
 
    printf("\n\n------------\n");
    remove_value(&root, 8);
    print_tree(root);
    
    printf("\n\n------------\n");
    int tree_height = find_height(root);
    printf("O tamano da árvore é %d\n", tree_height);

    printf("\n\n------------\n");
    invert(root);
    print_tree(root);
}