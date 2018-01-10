#include "Storge/MinHeap.h"

MinHeap::MinHeap(){
    mCurrOrder = 1;
    mHeap.p = NULL;
    mHeap.size = 0;
    mHeap.capacity = 0;
    reserveSize(4096 / sizeof(node_data_t*));
    mFreeHead = NULL;
}

MinHeap::~MinHeap(){
    if (mHeap.p)
    {
        mHeap.size = 0;
        mHeap.capacity = 0;
        free(mHeap.p);
    }
    while(mFreeHead)
    {
        node_data_t *p = mFreeHead;
        mFreeHead = (node_data_t*)mFreeHead->ptr;
        delete p;
    }
}

bool MinHeap::compareNode(const node_data_t* x, const node_data_t* y){
    if (x->key > y->key || (x->key == y->key && x->order > y->order))
    {
        return true;
    }
    return false;
}

void MinHeap::shiftDown(unsigned int hole_index, node_data_t* data){
    unsigned int min_child = 2 * (hole_index + 1);
    while(min_child <= mHeap.size)
    {
        if (compareNode(mHeap.p[min_child], mHeap.p[min_child - 1]))
        {
            min_child--;
        }
        if (compareNode(mHeap.p[min_child], data))
        {
            break;
        }
        mHeap.p[hole_index] = mHeap.p[min_child];
        mHeap.p[hole_index]->idx = hole_index;
        hole_index = min_child;
        min_child = 2 * (hole_index + 1);
    }
    data->idx = hole_index;
    mHeap.p[hole_index] = data;
}

void MinHeap::shiftUp(unsigned int hole_index, node_data_t *data){
    unsigned int parent = hole_index % 2 ? hole_index / 2 : hole_index / 2 - 1;
    while(hole_index && compareNode(mHeap.p[parent], data))
    {
        mHeap.p[parent] = mHeap.p[hole_index];
        mHeap.p[parent]->idx = hole_index;
        hole_index = parent;
        parent = hole_index % 2 ? hole_index / 2 : hole_index / 2 - 1;
    }
    data->idx = hole_index;
    mHeap.p[hole_index] = data;
}

node_data_t* MinHeap::top(){
    if (mHeap.size)
    {
        return *mHeap.p;
    }
    return NULL;
}

void* MinHeap::top(__int64 * key) {
    node_data_t * p = top();
    if (p != NULL) 
    {
        if (key != NULL)
        {
            *key = p->key;
        }
        return p->ptr;
    }
    return NULL;
}

bool MinHeap::push(__int64 key, void * ptr) {
    node_data_t * p = getNode();
    p->ptr = ptr;
    p->key = key;
    p->order = mCurrOrder++;

    return push(p) == 0;
}

void * MinHeap::pop(__int64 * key) {
    node_data_t* node = pop();
    void * res = node->ptr;
    if (key != NULL)
    {
        *key = node->key;
    }
    freeNode(node);
    return res;
}

node_data_t *MinHeap::pop() {
    if (mHeap.size > 0) 
    {
        node_data_t *d = *mHeap.p;
        shiftDown(0u, mHeap.p[--mHeap.size]);
        d->idx = -1;
        return d;
    }
    return NULL;
}

int MinHeap::getSize() {
    return mHeap.size;
}

bool MinHeap::isEmpty(){
	return mHeap.size == 0;
}

int MinHeap::reserveSize(unsigned int n){
    if (mHeap.capacity < n)
    {
        node_data_t **p = NULL;
        unsigned int size = mHeap.capacity ? mHeap.capacity * 2 : 8;
        if (size < n)
        {
            size = n;
        }
        p = (node_data_t**)realloc(mHeap.p, sizeof(*p) * size);
        if (p == NULL)
        {
            return -1;
        }
        mHeap.p = p;
        mHeap.capacity = size;
    }
    return 0;
}

int MinHeap::push(node_data_t *data) 
{
    if (reserveSize(mHeap.size + 1) < 0) {
        return -1;
    }

    shiftUp(mHeap.size++, data);
    return 0;
}

int MinHeap::erase(node_data_t* data){
    if (data->idx > 0 && mHeap.size > 0)
    {
        node_data_t *last = mHeap.p[--mHeap.size];
        unsigned int parent = (data->idx - 1) / 2;
        if (compareNode(mHeap.p[parent], last))
        {
            shiftUp(data->idx, last);
        }
    }
	return 0;
}

node_data_t* MinHeap::erase(unsigned int idx){
    node_data_t* result = NULL;
    if (idx > 0 && idx < mHeap.size)
    {
        result = mHeap.p[idx];
        node_data_t* last = mHeap.p[--mHeap.size];
        unsigned int parent = (idx - 1) / 2;
        if (compareNode(mHeap.p[parent], last))
        {
            shiftUp(idx, last);
        }
        else
        {
            shiftDown(idx, last);
        }
        result->idx = -1;
        return result;
    }
    else if (idx == 0)
    {
        return pop();
    }
    return result;
}

node_data_t* MinHeap::getNode(){
    node_data_t* res = NULL;
    if (mFreeHead != NULL)
    {
        res = mFreeHead;
        mFreeHead = (node_data_t*)res->ptr;
    }
    else
    {
        res = new node_data_t();
    }
    return res;
}

void MinHeap::freeNode(node_data_t* node){
    node->ptr = mFreeHead;
    mFreeHead = node;
}

void MinHeap::remove(funcRemoveItem func, void* context){
    node_data_t* free_list = NULL;
    for (unsigned int i = 0; i < mHeap.size; i++)
    {
        if (func(mHeap.p[i]->key, mHeap.p[i]->ptr, context))
        {
            mHeap.p[i]->ptr = free_list;
            free_list = mHeap.p[i];
        }
    }
    node_data_t* tmp = free_list;
    while(free_list != NULL)
    {
        tmp = free_list;
        free_list = (node_data_t*)free_list->ptr;
        erase(tmp);
        freeNode(tmp);
    }
}