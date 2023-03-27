#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdlib.h>
#include <stdio.h>

#define ROOT_POSITION 1

void throw_error(const char *msg)
{
    printf("ERROR: %s\n", msg);
    exit(EXIT_FAILURE);
}

#define define_priority_queue(type)                                                      \
    struct priority_queue_##type;                                                        \
    typedef struct                                                                       \
    {                                                                                    \
        void (*enqueue)(struct priority_queue_##type *, type);                           \
        type (*dequeue)(struct priority_queue_##type *);                                 \
        int (*empty)(const struct priority_queue_##type);                                \
        type (*front)(const struct priority_queue_##type);                               \
        unsigned (*size)(const struct priority_queue_##type);                            \
    } FUNCS_PRIORITY_QUEUE_##type;                                                       \
    typedef struct priority_queue_##type                                                 \
    {                                                                                    \
        unsigned size, no_elements;                                                      \
        type *values;                                                                    \
        int (*condition)(type, type);                                                    \
        FUNCS_PRIORITY_QUEUE_##type funcs;                                               \
    } PRIORITY_QUEUE_##type;                                                             \
    void swap_priority_queue_##type(type *a, type *b)                                    \
    {                                                                                    \
        type aux = *a;                                                                   \
        *a = *b;                                                                         \
        *b = aux;                                                                        \
    }                                                                                    \
    void enqueue_priority_queue_##type(PRIORITY_QUEUE_##type *pq, type elem)             \
    {                                                                                    \
        ++pq->no_elements;                                                               \
        if (pq->no_elements == pq->size)                                                 \
        {                                                                                \
            pq->size *= 2;                                                               \
            type *aux = pq->values;                                                      \
            pq->values = (type *)realloc(pq->values, pq->size * sizeof(type));           \
            if (pq->values == NULL)                                                      \
            {                                                                            \
                free(aux);                                                               \
                throw_error("Not enough space available");                               \
            }                                                                            \
        }                                                                                \
        pq->values[pq->no_elements] = elem;                                              \
        unsigned child_position = pq->no_elements;                                       \
        unsigned parent_position = child_position >> 1;                                  \
        type *child, *parent;                                                            \
        while (child_position != ROOT_POSITION)                                          \
        {                                                                                \
            child = &(pq->values[child_position]);                                       \
            parent = &(pq->values[parent_position]);                                     \
            if (pq->condition(*parent, *child) < 0)                                      \
            {                                                                            \
                swap_priority_queue_##type(parent, child);                               \
            }                                                                            \
            child_position >>= 1;                                                        \
            parent_position >>= 1;                                                       \
        }                                                                                \
    }                                                                                    \
    int empty_priority_queue_##type(const PRIORITY_QUEUE_##type pq)                      \
    {                                                                                    \
        return pq.no_elements == 0;                                                      \
    }                                                                                    \
    unsigned size_priority_queue_##type(const PRIORITY_QUEUE_##type pq)                  \ 
    {                                                                                    \ 
        return pq.no_elements;                                                           \ 
    }                                                                                    \
    type front_priority_queue_##type(const PRIORITY_QUEUE_##type pq)                     \
    {                                                                                    \
        if (pq.funcs.empty(pq))                                                          \
        {                                                                                \
            throw_error("front() called on empty priority queue");                       \
        }                                                                                \
        return pq.values[1];                                                             \
    }                                                                                    \
    type dequeue_priority_queue_##type(PRIORITY_QUEUE_##type *pq)                        \
    {                                                                                    \ 
        if (pq->funcs.empty(*pq))                                                        \
        {                                                                                \
            throw_error("dequeue() called on empty priority queue");                     \
        }                                                                                \
        type front = pq->funcs.front(*pq);                                               \
        pq->values[1] = pq->values[pq->no_elements];                                     \
        --pq->no_elements;                                                               \
        unsigned parent_position = 1;                                                    \
        unsigned child1_position = 2;                                                    \
        unsigned child2_position = 3;                                                    \
        type *parent, *child1, *child2;                                                  \
        int parent_child1_compare, parent_child2_compare;                                \
        while (child2_position <= pq->no_elements)                                       \
        {                                                                                \
            parent = &(pq->values[parent_position]);                                     \
            child1 = &(pq->values[child1_position]);                                     \
            child2 = &(pq->values[child2_position]);                                     \
            parent_child1_compare = pq->condition(*parent, *child1);                     \
            parent_child2_compare = pq->condition(*parent, *child2);                     \
            if (parent_child1_compare >= 0 && parent_child2_compare >= 0)                \
            {                                                                            \
                break;                                                                   \
            }                                                                            \
            else if (parent_child1_compare < 0 && parent_child2_compare < 0)             \
            {                                                                            \
                if (pq->condition(*child1, *child2) > 0)                                 \
                {                                                                        \
                    swap_priority_queue_##type(parent, child1);                          \
                    parent_position = child1_position;                                   \
                }                                                                        \
                else                                                                     \
                {                                                                        \
                    swap_priority_queue_##type(parent, child2);                          \
                    parent_position = child2_position;                                   \
                }                                                                        \
            }                                                                            \
            else if (parent_child1_compare < 0)                                          \
            {                                                                            \
                swap_priority_queue_##type(parent, child1);                              \
                parent_position = child1_position;                                       \
            }                                                                            \
            else                                                                         \
            {                                                                            \
                swap_priority_queue_##type(parent, child2);                              \
                parent_position = child2_position;                                       \
            }                                                                            \
            child1_position = parent_position * 2;                                       \
            child2_position = child1_position + 1;                                       \
        }                                                                                \
        parent = &(pq->values[parent_position]);                                         \
        child1 = &(pq->values[child1_position]);                                         \
        if (child1_position <= pq->no_elements)                                          \
        {                                                                                \
            if (pq->condition(*parent, *child1) < 0)                                     \
            {                                                                            \
                swap_priority_queue_##type(parent, child1);                              \
            }                                                                            \
        }                                                                                \
        return front;                                                                    \
    }                                                                                    \
    PRIORITY_QUEUE_##type initialize_priority_queue_##type(int (*condition)(type, type)) \
    {                                                                                    \
        PRIORITY_QUEUE_##type pq;                                                        \
        pq.size = 2;                                                                     \
        pq.no_elements = 0;                                                              \
        pq.values = (type *)malloc(2 * sizeof(type));                                    \
        if (pq.values == NULL)                                                           \
        {                                                                                \
            throw_error("Not enough space available");                                   \
        }                                                                                \
        pq.condition = condition;                                                        \
        pq.funcs.enqueue = &enqueue_priority_queue_##type;                               \
        pq.funcs.empty = &empty_priority_queue_##type;                                   \
        pq.funcs.front = &front_priority_queue_##type;                                   \
        pq.funcs.dequeue = &dequeue_priority_queue_##type;                               \
        pq.funcs.size = &size_priority_queue_##type;                                     \
        return pq;                                                                       \
    }

#define priority_queue(type) \
    PRIORITY_QUEUE_##type

#define new_priority_queue(type, condition) \
    initialize_priority_queue_##type(condition);

#define empty_priority_queue(pq) \
    pq.funcs.empty(pq)

#define front_priority_queue(pq) \
    pq.funcs.front(pq)

#define size_priority_queue(pq) \
    pq.funcs.size(pq)

#define enqueue_priority_queue(pq, elem) \
    pq.funcs.enqueue(&pq, elem)

#define dequeue_priority_queue(pq) \
    pq.funcs.dequeue(&pq)

#define dealloc_priority_queue(pq) \
    free(pq.values)

#endif