    #include <iostream>  
    #include <stdlib.h>  
    #include <time.h>  
    using namespace std;  
      
    typedef int key_t;  
    typedef int value_t;  
    #define MAX_LEVEL 16  
    #define SKIPLIST_P 0.25  
      
    struct node_t {  
        key_t key;  
        value_t val;  
        node_t *forward[];  
    };  
      
    class SkipList {  
        protected:  
            int m_level;  
            int m_length;  
            node_t *header;  
      
            node_t *creatNode(int level, key_t key, value_t val) {  
                node_t *node = (node_t*)malloc(sizeof(node_t)+level*sizeof(node_t*));  
                if (node == NULL) {  
                    return NULL;  
                }  
                node->key = key;  
                node->val = val;  
                srand(time(NULL));  
                return node;  
            }  
        public:  
            SkipList() {  
                header = creatNode(MAX_LEVEL, 0, 0);  
                if (header == NULL)  
                    exit(-1);  
                m_length = 0;  
                m_level = 0;  
      
                for (int i = 0; i < MAX_LEVEL; ++i) {  
                    header->forward[i] = NULL;  
                }  
            }  
      
            value_t *getValue(key_t key) {  
                int beg = m_level - 1;  
                node_t *p = header;  
                for (; beg >=0; --beg) {  
                      
                    while (p->forward[beg] && p->forward[beg]->key <= key) {  
                        if (p->forward[beg]->key == key)  
                            return &p->forward[beg]->val;  
                        p = p->forward[beg];  
                    }  
                    //p = p->forward[beg-1];  
                }  
      
                return NULL;  
            }  
      
            int randomLevel() {  
                int level = 1;  
                while ((rand()&0xffff) < 0xffff*SKIPLIST_P)  
                    ++level;  
                if(level > MAX_LEVEL) level = MAX_LEVEL;  
                return level;  
            }  
      
            void insert(key_t key, value_t val) {  
                node_t *update[MAX_LEVEL];  
                int beg = m_level - 1;  
                node_t *p = header;  
                node_t *last = NULL;  
                for (; beg >=0; --beg) {  
                    while( (last = p->forward[beg]) && last->key < key) {  
                        p = p->forward[beg];  
                    }  
                    update[beg] = p;  
                }  
      
                if (last && last->key == key) {  
                    last->val = val;  
                    return;  
                }  
      
                m_length++;  
                int level = randomLevel();  
                  
                if (level > m_level) {  
                    for(int i = m_level; i < level; ++i)  
                        update[i] = header;  
                    m_level = level;  
                }  
                node_t *node = creatNode(level, key, val);  
                for (beg = level - 1; beg >=0; --beg) {  
                    node->forward[beg] = update[beg]->forward[beg];  
                    update[beg]->forward[beg] = node;  
                }  
      
      
            }  
      
            void erase(key_t key) {  
                node_t *update[MAX_LEVEL];  
                int beg = m_level - 1;  
                node_t *p = header;  
                node_t *last = NULL;  
      
                for (; beg >=0; --beg) {  
                    while ((last = p->forward[beg]) && last->key < key) {  
                        p = p->forward[beg];  
                    }  
                }  
      
                if (last && last->key != key)  
                    return;  
      
                for (beg = m_level; beg >=0; --beg) {  
                    if (update[beg]->forward[beg] == last){  
                        update[beg]->forward[beg] = last->forward[beg];  
                        if (header->forward[beg] == NULL)  
                            m_level--;  
                    }  
                }  
      
                free(last);  
      
                m_length--;  
            }  
      
            void display() {  
                node_t *p = header->forward[0];  
                while (p) {  
                    cout << p->key << ":"<<p->val<<" ";  
                    p = p->forward[0];  
                }  
      
                cout <<endl;  
             
            }  
      
            ~SkipList() {  
                node_t *p = header;  
                while (p){  
                    node_t *next = p->forward[0];  
                    free(p);  
                    p = next;  
                }      
            }  
      
      
    };  
      
    int main() {  
        SkipList sl;  
        /*for (int i = 0; i < 1000; ++i){ 
            cout << i <<endl; 
            sl.insert(rand(),i); 
        }*/  
        sl.insert(0,10);  
        sl.insert(5, 50);  
        sl.insert(6, 60);  
        sl.insert(0, 11);  
        sl.insert(5, 51);  
        sl.insert(7,70);  
      
        sl.insert(3, 30);  
        sl.insert(4,40);  
        sl.insert(3,31);  
        sl.display();  
        return 1;  
    }  