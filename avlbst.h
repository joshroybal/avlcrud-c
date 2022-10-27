#ifndef AVLBST_H
#define AVLBST_H

struct node {
    char *key;
    char *value;
    int ht;
    struct node *left;
    struct node *right;
};

struct node *initialize(struct node*, char *, char *);
struct node *delete_node(struct node *);
struct node *update_node(struct node *, char *, char *);
struct node *deallocate(struct node*);
int balance_factor(struct node *);
struct node *rotate_left(struct node *);
struct node *rotate_right(struct node *);
struct node *insert(struct node *, char *, char *);
struct node *retrieve(struct node *, char *);
struct node *min(struct node *);
struct node *max(struct node *);
struct node *erase(struct node *, char *);
struct node *predecessor(struct node *, struct node *, char *);
struct node *successor(struct node *, struct node *, char *);
int leaf(struct node *);
struct node *defoliate(struct node *);
int size(struct node *);
int leaves(struct node *);
int imax(int, int);
int height(struct node *);
void printnode(struct node *);
void preorder(struct node *);
void inorder(struct node *);
void postorder(struct node *);
void serialize(FILE *, struct node *);
struct node *deserialize(FILE *, struct node *);

#endif
