#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *l;
    struct node *r;
};
typedef struct node n;
n* new_tree_3(int val, n* right, n* left) {
    n* tree = (n *) malloc(sizeof(n));
    tree -> val = val;
    tree -> l = left;
    tree -> r = right;
    return tree;
}
n* newtree(int val) {
    return new_tree_3(val, NULL, NULL);
}
int in(n* tree, int val) {
    if (val <= tree -> val) { if (tree -> l != NULL) {
            return 1 + in(tree -> l, val);
        } else {
            tree -> l = newtree(val);
            return 2;
        }
    } else {
        if (tree -> r != NULL) {
            return 1 + in(tree -> r, val);
        } else {
            tree -> r = newtree(val);
            return 2;
        }
    }
}
int con(n* tree, int val) {
    if (tree == NULL) {
        return 0;
    }
    if (tree -> val == val) {
        return 1;
    }
    if (val <= tree -> val) {
        int r = con(tree -> l, val);
        if (r == 0) {
            return 0;
        } else {
            return 1 + r;
        }
    } else {
        int r = con(tree -> r, val);
        if (r == 0) {
            return 0;
        } else {
            return 1+r;
        }
    }
}
int error() {
    printf("error\n");
    return 0;
}
int main(int argc, char** args) {
    if (argc != 2) {
        return error();
    }
    FILE* file = fopen(args[1], "r");
    if (file == NULL) {
        return error();
    }
    int val= 0;
    char op = 0;
    n* tree = NULL;
    while (fscanf(file, "%c %d\n", &op, &val) == 2) {
        if (op == 'i') {
            if (tree != NULL) {
                if (con(tree, val)) {
                    printf("duplicate\n");
                } else {
                    printf("inserted %d\n", in(tree, val));
                }
            } else {
                tree = newtree(val);
                printf("inserted 1\n");
            }
        } else if (op=='s') {
            int level=con(tree, val);
            if (level== 0) {
                printf("absent\n");
            } else {
                printf("present %d\n", level);
            }

        }
    }
    return 0;
}

