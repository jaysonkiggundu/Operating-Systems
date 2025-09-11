// list/list.c
//
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// ===== Allocation and cleanup =====

list_t *list_alloc() {
    list_t *list = malloc(sizeof(list_t));
    if (!list) return NULL;
    list->head = NULL;
    return list;
}

void list_free(list_t *l) {
    node_t *p;
    for (p = l->head; p;) {
        node_t *tmp = p->next;
        free(p);
        p = tmp;
    }
    l->head = NULL;
}

// ===== Insert operations =====

void list_add_to_front(list_t *l, elem value) {
    node_t *n = malloc(sizeof(node_t));
    n->value = value;
    n->next = l->head;
    l->head = n;
}

void list_add_to_back(list_t *l, elem value) {
    if (!l->head) {
        list_add_to_front(l, value);
        return;
    }
    node_t *p = l->head;
    while (p->next) p = p->next;
    node_t *n = malloc(sizeof(node_t));
    n->value = value;
    n->next = NULL;
    p->next = n;
}

void list_add_at_index(list_t *l, elem value, int index) {
    if (index == 1) {
        list_add_to_front(l, value);
        return;
    }

    int pos = 1;
    node_t *p = l->head, *prev = NULL;
    while (p) {
        if (pos == index) {
            node_t *n = malloc(sizeof(node_t));
            n->value = value;
            n->next = p;
            prev->next = n;
            return;
        }
        prev = p;
        p = p->next;
        pos++;
    }
    if (pos == index) list_add_to_back(l, value);
}

// ===== Remove operations =====

elem list_remove_from_front(list_t *l) {
    if (!l->head) return -1;
    node_t *p = l->head;
    elem v = p->value;
    l->head = p->next;
    free(p);
    return v;
}

elem list_remove_from_back(list_t *l) {
    if (!l->head) return -1;

    node_t *p = l->head, *prev = NULL;
    if (!p->next) {
        elem v = p->value;
        free(p);
        l->head = NULL;
        return v;
    }
    while (p->next) {
        prev = p;
        p = p->next;
    }
    elem v = p->value;
    prev->next = NULL;
    free(p);
    return v;
}

elem list_remove_at_index(list_t *l, int index) {
    if (index == 1) return list_remove_from_front(l);

    int pos = 1;
    node_t *p = l->head, *prev = NULL;
    while (p) {
        if (pos == index) {
            elem v = p->value;
            prev->next = p->next;
            free(p);
            return v;
        }
        prev = p;
        p = p->next;
        pos++;
    }
    return -1;
}

// ===== Queries =====

int list_length(list_t *l) {
    int count = 0;
    node_t *p;
    for (p = l->head; p; p = p->next) count++;
    return count;
}

bool list_is_in(list_t *l, elem value) {
    node_t *p;
    for (p = l->head; p; p = p->next)
        if (p->value == value) return true;
    return false;
}

elem list_get_elem_at(list_t *l, int index) {
    int pos = 1;
    node_t *p;
    for (p = l->head; p; p = p->next, pos++)
        if (pos == index) return p->value;
    return -1;
}

int list_get_index_of(list_t *l, elem value) {
    int pos = 1;
    node_t *p;
    for (p = l->head; p; p = p->next, pos++)
        if (p->value == value) return pos;
    return -1;
}

// ===== Printing and string conversion =====

void list_print(list_t *l) {
    node_t *p;
    if (!l->head) {
        printf("NULL\n");
        return;
    }
    for (p = l->head; p; p = p->next) {
        printf("%d", p->value);
        if (p->next) printf("->");
    }
    printf("->NULL\n");
}

char *listToString(list_t *l) {
    char *buf = malloc(1024);
    buf[0] = '\0';

    if (!l->head) {
        strcat(buf, "NULL");
        return buf;
    }

    char tmp[20];
    node_t *p;
    for (p = l->head; p; p = p->next) {
        sprintf(tmp, "%d", p->value);
        strcat(buf, tmp);
        if (p->next) strcat(buf, "->");
    }
    strcat(buf, "->NULL");
    return buf;
}
