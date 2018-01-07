#pragma once
#include <iostream>

typedef bool funcRemoveItem(__int64 key, void* ptr, void* content);
typedef struct node_data
{
    __int64 key;           /* 唯一ID */
    int idx;               /* 记录在数组中的位置 */
    void* ptr;             /* 用于记录下一个空闲节点 */
    unsigned int order;
}node_data_t;

typedef struct min_heap
{
    node_data_t **p;
    unsigned int capacity;
    unsigned int size;
}min_heap_t;
class MinHeap{
public:
    MinHeap();
    ~MinHeap();
public:
    void* top(__int64* key);
    bool push(__int64 key, void* ptr);
    void* pop(__int64* key);
    int getSize();
    bool isEmpty();
    void remove(funcRemoveItem func, void* content);
private:
    static bool compareNode(const node_data_t* x, const node_data_t* y);
    int reserveSize(unsigned int n);
    void shiftUp(unsigned int hole_index, node_data_t *data);
    void shiftDown(unsigned int hole_index, node_data_t* data);
    int push(node_data_t *data);
    int erase(node_data_t* data);
    node_data_t* top();
    node_data_t* pop();
    node_data_t* erase(unsigned int idx);
    node_data_t* getNode();
    void freeNode(node_data_t* node);
private:

    min_heap_t mHeap;
    node_data_t* mFreeHead;
    unsigned int mCurrOrder;
};