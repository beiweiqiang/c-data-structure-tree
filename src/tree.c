#include <stdlib.h>
#include "../include/tree.h"
#define MAX_LEN 100

static void cp_to_node(Item item, Trnode * tn);
static void cp_to_item(Item * item, Trnode * tn);
static Trnode * make_node(const Item * pi);
static bool to_left(const Item * i1, const Item * i2);
static bool to_right(const Item * i1, const Item * i2);
static void add_node(Trnode * new_node, Trnode * root);
static Pair seek_item(const Item * pi, const Tree * ptree);
static void delete_node(Trnode **ptr);
static void in_order(const Trnode * root, void (*pfunc) (Item item));
static void delete_all_node(Trnode * root);

void initialize_tree(Tree * ptree) {
  *ptree = NULL;
}

bool tree_is_empty(const Tree * ptree) {
  return ptree->size == 0;
}

bool tree_is_full(const Tree * ptree) {
  return ptree->size == MAX_LEN;
}

int tree_item_count(const Tree * ptree) {
  return ptree->size;
}

bool add_item(const Item * pi, Tree * ptree) {
  Trnode * new_node;
  if (tree_is_full(ptree)) {
    return false;
  }
  // 在树中已经存在该节点
  if (seek_item(pi, ptree).child != NULL) {
    return false;
  }

  new_node = make_node(pi);
  ptree->size++;
  if (ptree->root == NULL) {
    ptree->root = new_node;
  } else {
    add_node(new_node, ptree->root);
  }
  return true;
}

bool in_tree(const Item * pi, const Tree * ptree) {
  return seek_item(pi, ptree).child != NULL;
}

bool delete_item(const Item * pi, Tree * ptree) {
  Pair look;
  look = seek_item(pi, ptree);
  if (look.child == NULL) {
    return false;
  }
  if (look.parent == NULL) {
    // 证明要删除的节点是 根节点
    delete_node(&ptree->root);
  } else if (look.parent->left == look.child) {
    delete_node(&look.parent->left);
  } else {
    delete_node(&look.parent->right);
  }
  ptree->size--;
  return true;
}

void traverse(const Tree * ptree, void (*pfunc) (Item item)) {
  if (ptree != NULL) {
    in_order(ptree->root, pfunc);
  }
}

/**
 * 负责处理 Tree 类型的结构
 * @param ptree
 */
void delete_all(Tree * ptree) {
  if (ptree != NULL) {
    delete_all_node(ptree->root);
  }
  ptree->root = NULL;
  ptree->size = 0;
}

static void delete_all_node(Trnode * root) {
  Trnode * pright;
  if (root != NULL) {
    // 和 in_order 类似, 中序遍历
    pright = root->right;
    delete_all_node(root->left);
    free(root);
    delete_all_node(pright);
  }
}

static void cp_to_node(Item item, Trnode * tn) {
  tn->item = item;
}
static void cp_to_item(Item * item, Trnode * tn) {
  *item = tn->item;
}

static Trnode * make_node(const Item * pi) {
  Trnode * new_node;
  new_node = (Trnode *) malloc(sizeof(Trnode));

  if (new_node != NULL) {
    new_node->item = *pi;
    new_node->left = NULL;
    new_node->right = NULL;
  }
  return new_node;
}

/**
 * 如果 i1 在 i2 左边, 返回 true
 * @param i1
 * @param i2
 * @return
 */
static bool to_left(const Item * i1, const Item * i2) {
  return *i1 < *i2;
}

/**
 * 如果 i1 在 i2 右边, 返回 true
 * @param i1
 * @param i2
 * @return
 */
static bool to_right(const Item * i1, const Item * i2) {
  return *i1 > *i2;
}

static void add_node(Trnode * new_node, Trnode * root) {
  if (to_left(&new_node->item, &root->item)) {
    if (root->left == NULL) {
      root->left = new_node;
    } else {
      add_node(new_node, root->left);
    }
  } else if (to_right(&new_node->item, &root->item)) {
    if (root->right == NULL) {
      root->right = new_node;
    } else {
      add_node(new_node, root);
    }
  } else {
    exit(1);
  }
}

static Pair seek_item(const Item * pi, const Tree * ptree) {
  Pair look;
  look.parent = NULL;
  look.child = ptree->root;

  if (look.child == NULL) {
    return look;
  }

  while (look.child != NULL) {
    if (to_left(pi, &(look.child->item))) {
      look.parent = look.child;
      look.child = look.child->left;
    } else if (to_right(pi, &(look.child->item))) {
      look.parent = look.child;
      look.child = look.child->right;
    } else {
      break;
    }
  }

  return look;
}

/**
 *
 * @param ptr 目标节点 的父节点指针成员 的地址
 */
static void delete_node(Trnode **ptr) {
  Trnode * tmp;
  // (*ptr) 类型是 Trnode *
  // (*ptr) 是被删除节点的地址
  if ((*ptr)->left == NULL) {
    tmp = *ptr;
    // 将被删除节点的右子树, 放到被删除节点的地址上
    *ptr = (*ptr)->right;
    free(tmp);
  } else if ((*ptr)->right == NULL) {
    tmp = *ptr;
    *ptr = (*ptr)->left;
    free(tmp);
  } else {
    for (tmp = (*ptr)->left; tmp->right != NULL; tmp = tmp->right)
      continue;
    // 将被删除节点的右子树, 放到找到的 左子树上的空位上
    tmp->right = (*ptr)->right;

    tmp = *ptr;

    // 将被删除节点的 左子树, 放到被删除节点的地址上
    *ptr = (*ptr)->left;
    free(tmp);
  }
}

static void in_order(const Trnode * root, void (*pfunc) (Item item)) {
  if (root != NULL) {
    // root 和 root->left 是一样类型的, 都是 Trnode *
    in_order(root->left, pfunc);
    (*pfunc)(root->item);
    in_order(root->right, pfunc);
  }
}












