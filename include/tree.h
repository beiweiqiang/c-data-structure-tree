#ifndef TREE_TREE_H
#define TREE_TREE_H

#include <stdlib.h>
#include <stdbool.h>

typedef int Item;

typedef struct trnode {
  Item item;
  struct trnode * left;
  struct trnode * right;
} Trnode;

typedef struct tree {
  Trnode * root;
  int size;
} Tree;

typedef struct pair {
  Trnode * parent;
  Trnode * child;
} Pair;

void initialize_tree(Tree * ptree);
bool tree_is_empty(const Tree * ptree);
bool tree_is_full(const Tree * ptree);
int tree_item_count(const Tree * ptree);
bool add_item(const Item * pi, Tree * ptree);
bool in_tree(const Item * pi, const Tree * ptree);
bool delete_item(const Item * pi, Tree * ptree);
void traverse(const Tree * ptree, void (*pfunc) (Item item));
void delete_all(Tree * ptree);

#endif //TREE_TREE_H
