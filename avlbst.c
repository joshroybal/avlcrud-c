#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlbst.h"

#define RECSIZ 256

struct node *initialize(struct node *root, char *k, char *v)
{
    root = (struct node *) malloc(sizeof(struct node));
    root->key = (char *) malloc((strlen(k)+1)*sizeof(char));
    root->value = (char *) malloc((strlen(v)+1)*sizeof(char));
    strcpy(root->key, k);
    strcpy(root->value, v);
    root->ht = 0;
    root->left = (struct node *) NULL;
    root->right = (struct node *) NULL;
    return(root);
}

struct node *delete_node(struct node *root)
{
    free(root->value);
    free(root->key);
    free(root);
    return((struct node *) NULL);
}

struct node *update_node(struct node *root, char *k, char *v)
{
    free(root->value);
    free(root->key);
    root->key = (char *) malloc((strlen(k) + 1) * sizeof(char));
    root->value = (char *) malloc((strlen(v) + 1) * sizeof(char));
    strcpy(root->key, k);
    strcpy(root->value, v);
    return(root);
}

struct node *deallocate(struct node *root)
{
    if (root == (struct node *) NULL)
        return((struct node *) NULL);
    root->left = deallocate(root->left);
    root->right = deallocate(root->right);
    free(root->value);
    free(root->key);
    free(root);
    return((struct node *) NULL);
}

int balance_factor(struct node *root)
{
    return(height(root->left) - height(root->right));
}

struct node *rotate_left(struct node *root)
{
    struct node *p = root->right, *q = root->right->left;

    p->left = root;
    root->right = q;
    /* adjust heights */
    root->ht = 1 + imax(height(root->left), height(root->right));
    p->ht = 1 + imax(height(p->left), height(p->right));
    return(p);
}

struct node *rotate_right(struct node *root)
{
    struct node *p = root->left, *q = root->left->right;

    p->right = root;
    root->left = q;
    /* adjust heights */
    root->ht = 1 + imax(height(root->left), height(root->right));
    p->ht = 1 + imax(height(p->left), height(p->right));
    return(p);
}

struct node *insert(struct node *root, char *k, char *v)
{
    if (root == (struct node *) NULL) {
        root = initialize(root, k, v);
        return(root);
    }

    if (strcmp(k, root->key) < 0)
        root->left = insert(root->left, k, v);
    else if (strcmp(k, root->key) > 0)
        root->right = insert(root->right, k, v);
    else
       return(root);

    /* left left case */
    if (balance_factor(root) > 1 && balance_factor(root->left) > 0)
        return(rotate_right(root));

    /* right right case */
    if (balance_factor(root) < -1 && balance_factor(root->right) < 0)
        return(rotate_left(root));

    /* left right case */
    if (balance_factor(root) > 1 && balance_factor(root->left) < 0) {
        root->left = rotate_left(root->left);
        return(rotate_right(root));
    }

    /* right left case */
    if (balance_factor(root) < -1 && balance_factor(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    root->ht = 1 + imax(height(root->left), height(root->right));

    return(root);
}

struct node *retrieve(struct node *root, char *k)
{
    if (root == (struct node *) NULL)
        return(root);

    if (strcmp(k, root->key) < 0)
        return(retrieve(root->left, k));
    else if (strcmp(k, root->key) > 0)
        return(retrieve(root->right, k));
    else
        return(root);
}

struct node *min(struct node *root)
{
    return(root->left != (struct node *) NULL ? min(root->left) : root);
}

struct node *max(struct node *root)
{
    return(root->right != (struct node *) NULL ? max(root->right) : root);
}

struct node *erase(struct node *root, char *k)
{
    static struct node *leaf = (struct node *) NULL;

    if (root == (struct node *) NULL)
        return(root);

    if (strcmp(k, root->key) < 0)
        root->left = erase(root->left, k);
    else if (strcmp(k, root->key) > 0)
        root->right = erase(root->right, k);
    else {
        if (root->left == (struct node *) NULL) {
            leaf = root->right;
            root = delete_node(root);
            return(leaf);
        }
        else if (root->right == (struct node *) NULL) {
            leaf = root->left;
            root = delete_node(root);
            return(leaf);
        }
        leaf = max(root->left);
        root = update_node(root, leaf->key, leaf->value);
        root->left = erase(root->left, root->key);
    }

    /* left left case */
    if (balance_factor(root) > 1 && balance_factor(root->left) > 0)
        return(rotate_right(root));

    /* right right case */
    if (balance_factor(root) < -1 && balance_factor(root->right) < 0)
        return(rotate_left(root));

    /* left right case */
    if (balance_factor(root) > 1 && balance_factor(root->left) < 0) {
        root->left = rotate_left(root->left);
        return(rotate_right(root));
    }

    /* right left case */
    if (balance_factor(root) < -1 && balance_factor(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    root->ht = 1 + imax(height(root->left), height(root->right));

    return(root);
}

struct node *predecessor(struct node *root, struct node *prec, char *k)
{
    if (root == (struct node *) NULL)
        return(prec);

    if (strcmp(k, root->key) < 0)
        return(predecessor(root->left, prec, k));
    else if (strcmp(k, root->key) > 0)
        return(predecessor(root->right, root, k));
    else
        if (root->left != (struct node *) NULL)
            return(max(root->left));
        else
            return(prec);
}

struct node *successor(struct node *root, struct node *succ, char *k)
{
    if (root == (struct node *) NULL)
        return(succ);

    if (strcmp(k, root->key) < 0)
        return(successor(root->left, root, k));
    else if (strcmp(k, root->key) > 0)
        return(successor(root->right, succ, k));
    else
        if (root->right != (struct node *) NULL)
            return(min(root->right));
        else
            return(succ);
}

int leaf(struct node *root)
{
    if (root->left == (struct node *)NULL && root->right == (struct node *)NULL)
        return(1);
    else
        return(0);
}

struct node *defoliate(struct node *root)
{
    if (root == (struct node *) NULL)
        return(root);

    if (leaf(root)) {
        free(root);
        return((struct node *) NULL);
    }
    root->left = defoliate(root->left);
    root->right = defoliate(root->right);
    root->ht = 1 + imax(height(root->left), height(root->right));
    return(root);
}

int size(struct node *root)
{
    if (root == (struct node *) NULL)
        return(0);
    return(1 + size(root->left) + size(root->right));
}

int leaves(struct node *root)
{
    if (root == (struct node *) NULL)
        return(0);
    else if (leaf(root))
        return(1);
    else
        return(leaves(root->left) + leaves(root->right));
}

int imax(int a, int b)
{
    return(a > b ? a : b);
}

int height(struct node *root)
{
    if (root == (struct node *) NULL)
        return(-1);
    else
        return(root->ht);
}

void printnode(struct node *root)
{
    printf("%s: %s\n", root->key, root->value);
}

void preorder(struct node *root)
{
    if (root == (struct node *) NULL)
        return;
    printnode(root);
    preorder(root->left);
    preorder(root->right);
}

void inorder(struct node *root)
{
    if (root == (struct node *) NULL)
        return;
    inorder(root->left);
    printnode(root);
    inorder(root->right);
}

void postorder(struct node *root)
{
    if (root == (struct node *) NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printnode(root);
}

void serialize(FILE *fp, struct node *root)
{
    if (root == (struct node *) NULL) {
        fputs("\n", fp);
        return;
    }
    fprintf(fp, "%s\t%s\n", root->key, root->value);
    serialize(fp, root->left);
    serialize(fp, root->right);
}

struct node *deserialize(FILE *fp, struct node *root)
{
    static char *pc;
    static char record[RECSIZ];

    memset(record, 0, sizeof(record));
    if (fgets(record, sizeof(record), fp) == NULL || strcmp(record, "\n") == 0)
        return((struct node *) NULL);
    pc = strtok(record, "\n");
    pc = strtok(record, "\t");
    root = initialize(root, pc, pc + strlen(pc) + 1);
    root->left = deserialize(fp, root->left);
    root->right = deserialize(fp, root->right);
    root->ht = 1 + imax(height(root->left), height(root->right));
    return(root);
}
