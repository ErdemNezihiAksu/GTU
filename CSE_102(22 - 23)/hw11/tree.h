#ifndef tree_h
#define tree_h
#include "create_tree.h"
node *Deallocate_tree(node *family, char *root_name);
void Deallocate_list(list **liste);
list* Remove_family_tree(list *liste, char *family_name, char *filename);
void Add_new_person(list **iter);
int Remove_person(list **iter, list **liste);
void print_nuclear_family(list *iter);
void Search_relatives(list *iter);
#endif
