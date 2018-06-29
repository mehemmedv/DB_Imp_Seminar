//
// Created by mahammad on 4/10/18.
//

#ifndef DB_IMP_SEMINAR_ARTGRAPH_H
#define DB_IMP_SEMINAR_ARTGRAPH_H
#define neighbors_size 1000

#include <stdint-gcc.h>
#include <cstring>
#include <emmintrin.h>
#include <vector>
#include <iostream>
#include <functional>
#include <queue>

// Constants for the node types
static const int8_t NodeType4 = 0;
static const int8_t NodeType16 = 1;
static const int8_t NodeType48 = 2;
static const int8_t NodeType256 = 3;
static const int8_t NodeType65536 = 4;


// The maximum prefix length for compressed paths stored in the
// header, if the path is longer it is loaded from the database on
// demand
static const unsigned maxPrefixLength = 9;
static const uint8_t emptyMarker = 48;

struct Edge {
    uint32_t from;
    uint32_t to;

    uint64_t weight;

    uint8_t *getKey() { return reinterpret_cast<uint8_t *>(this); }
};

// Shared header of all inner nodes
struct Node {
    // length of the compressed path (prefix)
    uint32_t prefixLength;
    // number of non-null children
    uint16_t count;
    // node type
    int8_t type;
    // compressed path (prefix)
    uint8_t prefix[maxPrefixLength];

    Node(int8_t type) : prefixLength(0), count(0), type(type) {}
};

// Node with up to 4 children
struct Node4 : Node {
    uint8_t key[4];
    Node *child[4];

    Node4() : Node(NodeType4) {
        memset(key, 0, sizeof(key));
        memset(child, 0, sizeof(child));
    }
};

// Node with up to 16 children
struct Node16 : Node {
    uint8_t key[16];
    Node *child[16];

    Node16() : Node(NodeType16) {
        memset(key, 0, sizeof(key));
        memset(child, 0, sizeof(child));
    }
};

// Node with up to 48 children
struct Node48 : Node {
    uint8_t childIndex[256];
    Node *child[48];

    Node48() : Node(NodeType48) {
        memset(childIndex, emptyMarker, sizeof(childIndex));
        memset(child, 0, sizeof(child));
    }
};

// Node with up to 256 children
struct Node256 : Node {
    Node *child[256];

    Node256() : Node(NodeType256) {
        memset(child, 0, sizeof(child));
    }
};

struct Node65536 : Node {
    Node *child[65536];

    Node65536() : Node(NodeType65536) {
        memset(child, 0, sizeof(child));
    }
};

class ARTGraph {
private:
    class EdgeIter { // ARTGraph new Iterator using limited memory (1000 size)
        class iterator {
        public:
            iterator(std::pair<uint32_t, uint32_t > *ptr, EdgeIter *edgeiter) : ptr(ptr), edgeiter(edgeiter) {
            }

            inline iterator operator++() {
                ++ptr;
                if (ptr == edgeiter->get_end()) {
                    if (ptr == edgeiter->get_last()) {
                        //std::cout<<"full"<<std::endl;
                        edgeiter->recurse();
                        if(edgeiter->get_end() == edgeiter->get_begin())
                            ptr = edgeiter->get_first_end();
                        else
                            ptr = edgeiter->get_begin();
                    } else {
                        ptr = edgeiter->get_first_end();
                    }
                }
                return *this;
            }

            inline bool operator!=(const iterator &other) {
                //std::cout<<(int)(other.ptr - ptr)<<std::endl;
                return ptr != other.ptr;
            }

            inline const std::pair<uint32_t, uint32_t > &operator*() const { return *ptr;}

        private:
            EdgeIter *edgeiter;
            std::pair<uint32_t, uint32_t > *ptr;
        };

    private:
        std::vector<Edge> *edges;
        ARTGraph *graph;
        // Node *tree;
        std::pair<uint32_t, uint32_t > *begin_ptr, *end_ptr, *first_end;
        //std::vector<std::pair<Node *, int> > path;
        Node* path_node[5];
        int path_start_idx[5], path_size, cnt;
        std::pair<uint32_t, uint32_t > neighbors[neighbors_size];

        void init(Node* firstMatchingNode) {
            if (firstMatchingNode == NULL)
                return;
            path_node[0] = firstMatchingNode;
            path_start_idx[0] = -1;
            path_size = 1;
            recurse();
            first_end = neighbors + cnt;
        }

    public:
        EdgeIter(Node *firstMatchingNode, std::vector<Edge> *edge_ptr, ARTGraph *graph) {
            path_size = 0;
            this->graph = graph;
            edges = edge_ptr;
            cnt = 0;
            //this->tree = tree_root;
            begin_ptr = end_ptr = neighbors;

            // calculate the firstMatchingNode
            init(firstMatchingNode);
        }

        inline std::pair<uint32_t, uint32_t > *get_begin() {
            return begin_ptr;
        }

        inline std::pair<uint32_t, uint32_t > *get_first_end() {
            return first_end;
        }

        inline std::pair<uint32_t, uint32_t > *get_end() {
            return end_ptr;
        }

        inline std::pair<uint32_t, uint32_t > *get_last() {
            return begin_ptr + neighbors_size;
        }

        void recurse() {
            cnt = 0;
            while (cnt < neighbors_size && path_size != 0) {
                //std::pair<Node *, int> lastNodePair = path[path.size() - 1];
                Node *current_node = path_node[path_size-1];
                int start_idx = path_start_idx[path_size-1];
                if (graph->isLeaf(current_node)) {
                    uint32_t to = graph->getLeafValue(current_node);
                    neighbors[cnt++] = std::make_pair((edges->at(to).to), edges->at(to).weight);
                    --path_size;
                    continue;
                }

                if (current_node->type == NodeType4) {
                    Node4 *node = static_cast<Node4 *>(current_node);
                    ++start_idx;
                    if (start_idx < node->count) {
                        //path[path.size() - 1].second = start_idx;
                        //path.push_back(std::make_pair(node->child[start_idx], -1));
                        path_start_idx[path_size - 1] = start_idx;
                        path_node[path_size] = node->child[start_idx];
                        path_start_idx[path_size] = -1;
                        ++path_size;
                        continue;
                    }
                } else if (current_node->type == NodeType16) {
                    Node16 *node = static_cast<Node16 *>(current_node);
                    ++start_idx;
                    if (start_idx < node->count) {
                        path_start_idx[path_size - 1] = start_idx;
                        path_node[path_size] = node->child[start_idx];
                        path_start_idx[path_size] = -1;
                        ++path_size;
                        continue;
                    }
                } else if (current_node->type == NodeType48) {
                    Node48 *node = static_cast<Node48 *>(current_node);
                    ++start_idx;
                    if (start_idx < node->count) {
                        path_start_idx[path_size - 1] = start_idx;
                        path_node[path_size] = node->child[start_idx];
                        path_start_idx[path_size] = -1;
                        ++path_size;
                        continue;
                    }
                } else if (current_node->type == NodeType256) {
                    Node256 *node = static_cast<Node256 *>(current_node);
                    int idx = -1;
                    for (unsigned i = start_idx + 1; i < 256; i++) {
                        if (node->child[i] != NULL) {
                            idx = i;
                            break;
                        }
                    }
                    if (idx != -1) {
                        //path[path.size() - 1].second = idx;
                        //path.push_back(std::make_pair(node->child[idx], -1));

                        path_start_idx[path_size - 1] = idx;
                        path_node[path_size] = node->child[idx];
                        path_start_idx[path_size] = -1;
                        ++path_size;
                        continue;
                    }
                }
                //path.pop_back();
                path_size--;
            }
            //std::cout<<cnt<<" "<<path.size()<<std::endl;
            end_ptr = neighbors + cnt;
        }

        inline iterator begin() { return iterator(begin_ptr, this); }

        inline iterator end() { return iterator(end_ptr, this); }
    };

    // This address is used to communicate that search failed
    Node *nullNode = NULL;

    Node *tree;

    Node65536 *tree65536;

    uint64_t edgeId;

    std::vector<Edge> edges;

    inline Node *makeLeaf(uintptr_t tid) {
        // Create a pseudo-leaf
        return reinterpret_cast<Node *>((tid << 1) | 1);
    }

    uint8_t flipSign(uint8_t keyByte) {
        // Flip the sign bit, enables signed SSE comparison of unsigned values, used by Node16
        return keyByte ^ 128;
    }


    static inline unsigned ctz(uint16_t x) {
        // Count trailing zeros, only defined for x>0
#ifdef __GNUC__
        return __builtin_ctz(x);
#else
        // Adapted from Hacker's Delight
   unsigned n=1;
   if ((x&0xFF)==0) {n+=8; x=x>>8;}
   if ((x&0x0F)==0) {n+=4; x=x>>4;}
   if ((x&0x03)==0) {n+=2; x=x>>2;}
   return n-(x&1);
#endif
    }

    Node *minimum(Node *node) {
        // Find the leaf with smallest key
        if (!node)
            return NULL;

        if (isLeaf(node))
            return node;

        switch (node->type) {
            case NodeType4: {
                Node4 *n = static_cast<Node4 *>(node);
                return minimum(n->child[0]);
            }
            case NodeType16: {
                Node16 *n = static_cast<Node16 *>(node);
                return minimum(n->child[0]);
            }
            case NodeType48: {
                Node48 *n = static_cast<Node48 *>(node);
                unsigned pos = 0;
                while (n->childIndex[pos] == emptyMarker)
                    pos++;
                return minimum(n->child[n->childIndex[pos]]);
            }
            case NodeType256: {
                Node256 *n = static_cast<Node256 *>(node);
                unsigned pos = 0;
                while (!n->child[pos])
                    pos++;
                return minimum(n->child[pos]);
            }
        }
        throw; // Unreachable
    }

    Node *maximum(Node *node) {
        // Find the leaf with largest key
        if (!node)
            return NULL;

        if (isLeaf(node))
            return node;

        switch (node->type) {
            case NodeType4: {
                Node4 *n = static_cast<Node4 *>(node);
                return maximum(n->child[n->count - 1]);
            }
            case NodeType16: {
                Node16 *n = static_cast<Node16 *>(node);
                return maximum(n->child[n->count - 1]);
            }
            case NodeType48: {
                Node48 *n = static_cast<Node48 *>(node);
                unsigned pos = 255;
                while (n->childIndex[pos] == emptyMarker)
                    pos--;
                return maximum(n->child[n->childIndex[pos]]);
            }
            case NodeType256: {
                Node256 *n = static_cast<Node256 *>(node);
                unsigned pos = 255;
                while (!n->child[pos])
                    pos--;
                return maximum(n->child[pos]);
            }
        }
        throw; // Unreachable
    }

    bool leafMatches(Node *leaf, uint8_t key[], unsigned keyLength, unsigned depth, unsigned maxKeyLength) {
        // Check if the key of the leaf is equal to the searched key
        if (depth != keyLength) {
            uint8_t leafKey[maxKeyLength];
            loadKey(getLeafValue(leaf), leafKey);
            for (unsigned i = depth; i < keyLength; i++)
                if (leafKey[i] != key[i])
                    return false;
        }
        return true;
    }

    unsigned prefixMismatch(Node *node, uint8_t key[], unsigned depth, unsigned maxKeyLength) {
        // Compare the key with the prefix of the node, return the number matching bytes
        unsigned pos;
        if (node->prefixLength > maxPrefixLength) {
            for (pos = 0; pos < maxPrefixLength; pos++)
                if (key[depth + pos] != node->prefix[pos])
                    return pos;
            uint8_t minKey[maxKeyLength];
            loadKey(getLeafValue(minimum(node)), minKey);
            for (; pos < node->prefixLength; pos++)
                if (key[depth + pos] != minKey[depth + pos])
                    return pos;
        } else {
            for (pos = 0; pos < node->prefixLength; pos++)
                if (key[depth + pos] != node->prefix[pos])
                    return pos;
        }
        return pos;
    }

    Node *lookup(Node *node, uint8_t key[], unsigned keyLength, unsigned depth, unsigned maxKeyLength) {
        // Find the node with a matching key, optimistic version

        bool skippedPrefix = false; // Did we optimistically skip some prefix without checking it?

        while (node != NULL && depth < 4) {
            if (isLeaf(node)) {
                if (!skippedPrefix && depth == keyLength) // No check required
                    return node;

                if (depth != keyLength) {
                    // Check leaf
                    uint8_t leafKey[maxKeyLength];
                    loadKey(getLeafValue(node), leafKey);
                    for (unsigned i = (skippedPrefix ? 0 : depth); i < keyLength; i++)
                        if (leafKey[i] != key[i])
                            return NULL;
                }
                return node;
            }

            if (node->prefixLength) {
                if (node->prefixLength < maxPrefixLength) {
                    for (unsigned pos = 0; pos < node->prefixLength; pos++)
                        if (key[depth + pos] != node->prefix[pos])
                            return NULL;
                } else
                    skippedPrefix = true;
                depth += node->prefixLength;
            }

            node = *findChild(node, key[depth]);
            depth++;
        }
        return node;
        //return NULL;
    }

    Node **findChild(Node *n, uint8_t keyByte) {
        // Find the next child for the keyByte
        switch (n->type) {
            case NodeType4: {
                Node4 *node = static_cast<Node4 *>(n);
                for (unsigned i = 0; i < node->count; i++)
                    if (node->key[i] == keyByte)
                        return &node->child[i];
                return &nullNode;
            }
            case NodeType16: {
                Node16 *node = static_cast<Node16 *>(n);
                __m128i cmp = _mm_cmpeq_epi8(_mm_set1_epi8(flipSign(keyByte)),
                                             _mm_loadu_si128(reinterpret_cast<__m128i *>(node->key)));
                unsigned bitfield = _mm_movemask_epi8(cmp) & ((1 << node->count) - 1);
                if (bitfield)
                    return &node->child[ctz(bitfield)];
                else
                    return &nullNode;
            }
            case NodeType48: {
                Node48 *node = static_cast<Node48 *>(n);
                if (node->childIndex[keyByte] != emptyMarker)
                    return &node->child[node->childIndex[keyByte]];
                else
                    return &nullNode;
            }
            case NodeType256: {
                Node256 *node = static_cast<Node256 *>(n);
                return &(node->child[keyByte]);
            }
        }
        throw; // Unreachable
    }

    Node *lookupPessimistic(Node *node, uint8_t key[], unsigned keyLength, unsigned depth, unsigned maxKeyLength) {
        // Find the node with a matching key, alternative pessimistic version

        while (node != NULL) {
            if (isLeaf(node)) {
                if (leafMatches(node, key, keyLength, depth, maxKeyLength))
                    return node;
                return NULL;
            }

            if (prefixMismatch(node, key, depth, maxKeyLength) != node->prefixLength)
                return NULL;
            else
                depth += node->prefixLength;

            node = *findChild(node, key[depth]);
            depth++;
        }

        return NULL;
    }

// Forward references
/*
    void insertNode4(Node4* node,Node** nodeRef,uint8_t keyByte,Node* child);
    void insertNode16(Node16* node,Node** nodeRef,uint8_t keyByte,Node* child);
    void insertNode48(Node48* node,Node** nodeRef,uint8_t keyByte,Node* child);
    void insertNode256(Node256* node,Node** nodeRef,uint8_t keyByte,Node* child);
*/

    unsigned min(unsigned a, unsigned b) {
        // Helper function
        return (a < b) ? a : b;
    }

    void copyPrefix(Node *src, Node *dst) {
        // Helper function that copies the prefix from the source to the destination node
        dst->prefixLength = src->prefixLength;
        memcpy(dst->prefix, src->prefix, min(src->prefixLength, maxPrefixLength));
    }

    void insert(Node *node, Node **nodeRef, uint8_t key[], unsigned depth, uintptr_t value, unsigned maxKeyLength) {
        // Insert the leaf value into the tree

        if (node == NULL) {
            *nodeRef = makeLeaf(value);
            return;
        }

        if (isLeaf(node)) {
            // Replace leaf with Node4 and store both leaves in it
            uint8_t existingKey[maxKeyLength];
            loadKey(getLeafValue(node), existingKey);
            unsigned newPrefixLength = 0;
            while (existingKey[depth + newPrefixLength] == key[depth + newPrefixLength])
                newPrefixLength++;

            Node4 *newNode = new Node4();
            newNode->prefixLength = newPrefixLength;
            memcpy(newNode->prefix, key + depth, min(newPrefixLength, maxPrefixLength));
            *nodeRef = newNode;

            insertNode4(newNode, nodeRef, existingKey[depth + newPrefixLength], node);
            insertNode4(newNode, nodeRef, key[depth + newPrefixLength], makeLeaf(value));
            return;
        }

        // Handle prefix of inner node
        if (node->prefixLength) {
            unsigned mismatchPos = prefixMismatch(node, key, depth, maxKeyLength);
            if (mismatchPos != node->prefixLength) {
                // Prefix differs, create new node
                Node4 *newNode = new Node4();
                *nodeRef = newNode;
                newNode->prefixLength = mismatchPos;
                memcpy(newNode->prefix, node->prefix, min(mismatchPos, maxPrefixLength));
                // Break up prefix
                if (node->prefixLength < maxPrefixLength) {
                    insertNode4(newNode, nodeRef, node->prefix[mismatchPos], node);
                    node->prefixLength -= (mismatchPos + 1);
                    memmove(node->prefix, node->prefix + mismatchPos + 1, min(node->prefixLength, maxPrefixLength));
                } else {
                    node->prefixLength -= (mismatchPos + 1);
                    uint8_t minKey[maxKeyLength];
                    loadKey(getLeafValue(minimum(node)), minKey);
                    insertNode4(newNode, nodeRef, minKey[depth + mismatchPos], node);
                    memmove(node->prefix, minKey + depth + mismatchPos + 1, min(node->prefixLength, maxPrefixLength));
                }
                insertNode4(newNode, nodeRef, key[depth + mismatchPos], makeLeaf(value));
                return;
            }
            depth += node->prefixLength;
        }

        // Recurse
        Node **child = findChild(node, key[depth]);
        if (*child) {
            insert(*child, child, key, depth + 1, value, maxKeyLength);
            return;
        }

        // Insert leaf into inner node
        Node *newNode = makeLeaf(value);
        switch (node->type) {
            case NodeType4:
                insertNode4(static_cast<Node4 *>(node), nodeRef, key[depth], newNode);
                break;
            case NodeType16:
                insertNode16(static_cast<Node16 *>(node), nodeRef, key[depth], newNode);
                break;
            case NodeType48:
                insertNode48(static_cast<Node48 *>(node), nodeRef, key[depth], newNode);
                break;
            case NodeType256:
                insertNode256(static_cast<Node256 *>(node), nodeRef, key[depth], newNode);
                break;
        }
    }

    void insertNode4(Node4 *node, Node **nodeRef, uint8_t keyByte, Node *child) {
        // Insert leaf into inner node
        if (node->count < 4) {
            // Insert element
            unsigned pos;
            for (pos = 0; (pos < node->count) && (node->key[pos] < keyByte); pos++);
            memmove(node->key + pos + 1, node->key + pos, node->count - pos);
            memmove(node->child + pos + 1, node->child + pos, (node->count - pos) * sizeof(uintptr_t));
            node->key[pos] = keyByte;
            node->child[pos] = child;
            node->count++;
        } else {
            // Grow to Node16
            Node16 *newNode = new Node16();
            *nodeRef = newNode;
            newNode->count = 4;
            copyPrefix(node, newNode);
            for (unsigned i = 0; i < 4; i++)
                newNode->key[i] = flipSign(node->key[i]);
            memcpy(newNode->child, node->child, node->count * sizeof(uintptr_t));
            delete node;
            return insertNode16(newNode, nodeRef, keyByte, child);
        }
    }

    void insertNode16(Node16 *node, Node **nodeRef, uint8_t keyByte, Node *child) {
        // Insert leaf into inner node
        if (node->count < 16) {
            // Insert element
            uint8_t keyByteFlipped = flipSign(keyByte);
            __m128i cmp = _mm_cmplt_epi8(_mm_set1_epi8(keyByteFlipped),
                                         _mm_loadu_si128(reinterpret_cast<__m128i *>(node->key)));
            uint16_t bitfield = _mm_movemask_epi8(cmp) & (0xFFFF >> (16 - node->count));
            unsigned pos = bitfield ? ctz(bitfield) : node->count;
            memmove(node->key + pos + 1, node->key + pos, node->count - pos);
            memmove(node->child + pos + 1, node->child + pos, (node->count - pos) * sizeof(uintptr_t));
            node->key[pos] = keyByteFlipped;
            node->child[pos] = child;
            node->count++;
        } else {
            // Grow to Node48
            Node48 *newNode = new Node48();
            *nodeRef = newNode;
            memcpy(newNode->child, node->child, node->count * sizeof(uintptr_t));
            for (unsigned i = 0; i < node->count; i++)
                newNode->childIndex[flipSign(node->key[i])] = i;
            copyPrefix(node, newNode);
            newNode->count = node->count;
            delete node;
            return insertNode48(newNode, nodeRef, keyByte, child);
        }
    }

    void insertNode48(Node48 *node, Node **nodeRef, uint8_t keyByte, Node *child) {
        // Insert leaf into inner node
        if (node->count < 48) {
            // Insert element
            unsigned pos = node->count;
            if (node->child[pos])
                for (pos = 0; node->child[pos] != NULL; pos++);
            node->child[pos] = child;
            node->childIndex[keyByte] = pos;
            node->count++;
        } else {
            // Grow to Node256
            Node256 *newNode = new Node256();
            for (unsigned i = 0; i < 256; i++)
                if (node->childIndex[i] != 48)
                    newNode->child[i] = node->child[node->childIndex[i]];
            newNode->count = node->count;
            copyPrefix(node, newNode);
            *nodeRef = newNode;
            delete node;
            return insertNode256(newNode, nodeRef, keyByte, child);
        }
    }

    void insertNode256(Node256 *node, Node **nodeRef, uint8_t keyByte, Node *child) {
        // Insert leaf into inner node
        node->count++;
        node->child[keyByte] = child;
    }

// Forward references
/*
    void eraseNode4(Node4* node,Node** nodeRef,Node** leafPlace);
    void eraseNode16(Node16* node,Node** nodeRef,Node** leafPlace);
    void eraseNode48(Node48* node,Node** nodeRef,uint8_t keyByte);
    void eraseNode256(Node256* node,Node** nodeRef,uint8_t keyByte);
*/
    void erase(Node *node, Node **nodeRef, uint8_t key[], unsigned keyLength, unsigned depth, unsigned maxKeyLength) {
        // Delete a leaf from a tree

        if (!node)
            return;

        if (isLeaf(node)) {
            // Make sure we have the right leaf
            if (leafMatches(node, key, keyLength, depth, maxKeyLength))
                *nodeRef = NULL;
            return;
        }

        // Handle prefix
        if (node->prefixLength) {
            if (prefixMismatch(node, key, depth, maxKeyLength) != node->prefixLength)
                return;
            depth += node->prefixLength;
        }

        Node **child = findChild(node, key[depth]);
        if (isLeaf(*child) && leafMatches(*child, key, keyLength, depth, maxKeyLength)) {
            // Leaf found, delete it in inner node
            switch (node->type) {
                case NodeType4:
                    eraseNode4(static_cast<Node4 *>(node), nodeRef, child);
                    break;
                case NodeType16:
                    eraseNode16(static_cast<Node16 *>(node), nodeRef, child);
                    break;
                case NodeType48:
                    eraseNode48(static_cast<Node48 *>(node), nodeRef, key[depth]);
                    break;
                case NodeType256:
                    eraseNode256(static_cast<Node256 *>(node), nodeRef, key[depth]);
                    break;
            }
        } else {
            //Recurse
            erase(*child, child, key, keyLength, depth + 1, maxKeyLength);
        }
    }

    void eraseNode4(Node4 *node, Node **nodeRef, Node **leafPlace) {
        // Delete leaf from inner node
        unsigned pos = leafPlace - node->child;
        memmove(node->key + pos, node->key + pos + 1, node->count - pos - 1);
        memmove(node->child + pos, node->child + pos + 1, (node->count - pos - 1) * sizeof(uintptr_t));
        node->count--;

        if (node->count == 1) {
            // Get rid of one-way node
            Node *child = node->child[0];
            if (!isLeaf(child)) {
                // Concantenate prefixes
                unsigned l1 = node->prefixLength;
                if (l1 < maxPrefixLength) {
                    node->prefix[l1] = node->key[0];
                    l1++;
                }
                if (l1 < maxPrefixLength) {
                    unsigned l2 = min(child->prefixLength, maxPrefixLength - l1);
                    memcpy(node->prefix + l1, child->prefix, l2);
                    l1 += l2;
                }
                // Store concantenated prefix
                memcpy(child->prefix, node->prefix, min(l1, maxPrefixLength));
                child->prefixLength += node->prefixLength + 1;
            }
            *nodeRef = child;
            delete node;
        }
    }

    void eraseNode16(Node16 *node, Node **nodeRef, Node **leafPlace) {
        // Delete leaf from inner node
        unsigned pos = leafPlace - node->child;
        memmove(node->key + pos, node->key + pos + 1, node->count - pos - 1);
        memmove(node->child + pos, node->child + pos + 1, (node->count - pos - 1) * sizeof(uintptr_t));
        node->count--;

        if (node->count == 3) {
            // Shrink to Node4
            Node4 *newNode = new Node4();
            newNode->count = node->count;
            copyPrefix(node, newNode);
            for (unsigned i = 0; i < 4; i++)
                newNode->key[i] = flipSign(node->key[i]);
            memcpy(newNode->child, node->child, sizeof(uintptr_t) * 4);
            *nodeRef = newNode;
            delete node;
        }
    }

    void eraseNode48(Node48 *node, Node **nodeRef, uint8_t keyByte) {
        // Delete leaf from inner node
        node->child[node->childIndex[keyByte]] = NULL;
        node->childIndex[keyByte] = emptyMarker;
        node->count--;

        if (node->count == 12) {
            // Shrink to Node16
            Node16 *newNode = new Node16();
            *nodeRef = newNode;
            copyPrefix(node, newNode);
            for (unsigned b = 0; b < 256; b++) {
                if (node->childIndex[b] != emptyMarker) {
                    newNode->key[newNode->count] = flipSign(b);
                    newNode->child[newNode->count] = node->child[node->childIndex[b]];
                    newNode->count++;
                }
            }
            delete node;
        }
    }

    void eraseNode256(Node256 *node, Node **nodeRef, uint8_t keyByte) {
        // Delete leaf from inner node
        node->child[keyByte] = NULL;
        node->count--;

        if (node->count == 37) {
            // Shrink to Node48
            Node48 *newNode = new Node48();
            *nodeRef = newNode;
            copyPrefix(node, newNode);
            for (unsigned b = 0; b < 256; b++) {
                if (node->child[b]) {
                    newNode->childIndex[b] = newNode->count;
                    newNode->child[newNode->count] = node->child[b];
                    newNode->count++;
                }
            }
            delete node;
        }
    }

    void find_all_neighbors(std::vector<std::pair<uint32_t, uint32_t>> &res, Node *current_node, int height = 0) {

        if (current_node == NULL) {
            std::cout << "Some Bug existed !!!" << std::endl;
            return;
        }

        if (isLeaf(current_node)) {
            if(height > 5)
                std::cout<<"here: "<<height<<std::endl;
            uint32_t to = getLeafValue(current_node);
            //std::cout <<"To: "<< edges[to].to << std::endl;
            res.push_back(std::make_pair(edges[to].to, edges[to].weight));
            return;
        }

        switch (current_node->type) {
            case NodeType4: {
                Node4 *node = static_cast<Node4 *>(current_node);
                for (unsigned i = 0; i < node->count; i++) {
                    find_all_neighbors(res, node->child[i], height + 1);
                }
                return;
            }
            case NodeType16: {
                Node16 *node = static_cast<Node16 *>(current_node);
                for (unsigned i = 0; i < node->count; i++) {
                    find_all_neighbors(res, node->child[i], height + 1);
                }
                return;
            }
            case NodeType48: {
                Node48 *node = static_cast<Node48 *>(current_node);
                for (unsigned i = 0; i < node->count; i++)
                    find_all_neighbors(res, node->child[i], height + 1);
                return;
            }
            case NodeType256: {
                Node256 *node = static_cast<Node256 *>(current_node);
                for (unsigned i = 0; i < 256; i++) {
                    if (node->child[i] != NULL)
                        find_all_neighbors(res, node->child[i], height + 1);
                }
                return;
            }
        }
        throw; // Unreachable
    }

    void loadKey(uintptr_t tid, uint8_t key[]) {
        // Store the key of the tuple into the key vector
        // Implementation is database specific
        reinterpret_cast<uint64_t *>(key)[0] = __builtin_bswap64(getKey(edges[tid].from, edges[tid].to));
    }

    template<typename CB>
    void find_all_neighbors_lambda(Node *current_node, CB &lambdaCallback) {
        //if (current_node == NULL) {
            // std::cout << "Some Bug existed !!!" << std::endl;
        //    return;
        //}

        if (isLeaf(current_node)) {
            uint32_t to = getLeafValue(current_node);
            //std::cout <<"To: "<< edges[to].to << std::endl;
            lambdaCallback(edges[to].to, edges[to].weight);
            //res.push_back(std::make_pair(edges[to].to, edges[to].weight));
            return;
        }

        switch (current_node->type) {
            case NodeType4: {
                Node4 *node = static_cast<Node4 *>(current_node);
                for (unsigned i = 0; i < node->count; ++i) {
                    find_all_neighbors_lambda(node->child[i], lambdaCallback);
                }
                return;
            }
            case NodeType16: {
                Node16 *node = static_cast<Node16 *>(current_node);
                for (unsigned i = 0; i < node->count; ++i) {
                    find_all_neighbors_lambda(node->child[i], lambdaCallback);
                }
                return;
            }
            case NodeType48: {
                Node48 *node = static_cast<Node48 *>(current_node);
                for (unsigned i = 0; i < node->count; ++i)
                    find_all_neighbors_lambda(node->child[i], lambdaCallback);
                return;
            }
            case NodeType256: {
                Node256 *node = static_cast<Node256 *>(current_node);
                for (unsigned i = 0; i < 256; ++i) {
                    if (node->child[i] != NULL)
                        find_all_neighbors_lambda(node->child[i], lambdaCallback);
                }
                return;
            }
        }
        throw; // Unreachable
    }

public:

    ARTGraph(uint64_t v, uint64_t e) : tree(NULL), edgeId(0), tree65536(new Node65536()) {}

    inline uint64_t getKey(int from, int to) {
        return ((from * 1ULL) << 32) + to;
    }

    void convertKey(uintptr_t tid, uint8_t key[]) {
        reinterpret_cast<uint64_t *>(key)[0] = __builtin_bswap64(tid);
    }

    void convertKey_32(uintptr_t tid, uint8_t key[]) {
        reinterpret_cast<uint64_t *>(key)[0] = __builtin_bswap32(tid);
    }

    inline uintptr_t getLeafValue(Node *node) {
        // The the value stored in the pseudo-leaf
        return reinterpret_cast<uintptr_t>(node) >> 1;
    }

    inline bool isLeaf(Node *node) {
        // Is the node a leaf?
        return reinterpret_cast<uintptr_t>(node) & 1;
    }

    void add_edge(uint32_t from, std::vector<uint32_t> &to, std::vector<uint32_t> &w);

    inline void add_edge(uint32_t from, uint32_t to, int weight = 0) {
        uint8_t key[4];
        Edge edge = {from, to, weight};
        edges.push_back(edge);
        //convertKey(getKey(from, to), key);

        convertKey_32(to, key);
        //std::cout<<"to = "<<to<<" : ";
        //for(int i = 0; i < 4; ++i)
        //    std::cout<<(int)key[i]<<" ";
        //std::cout<<std::endl;
        Node65536 *current = static_cast<Node65536 *>(tree65536);
        //std::cout<<from<<" : "<<(from >> 16)<<std::endl;
        if(current->child[from >> 16] == NULL){
            current->child[from >> 16] = new Node65536();
            //std::cout<<"created"<<std::endl;
        }
        current = static_cast<Node65536 *>(current->child[from >> 16]);
        //Node* next_node = current->child[from >> 16];
        //current = static_cast<Node65536 *>(next_node);
        //std::cout<<(from & 65535)<<std::endl;

        //std::cout<<"here1"<<std::endl;
        insert(current->child[from & 65535], &(current->child[from & 65535]), key, 0, edgeId++, 4);
        //std::cout<<"here2"<<std::endl;
        // insert(tree, &tree, key, 0, edgeId++, 8);
    }

    inline void add_edge_old(uint32_t from, uint32_t to, int weight = 0) {
        uint8_t key[8];
        Edge edge = {from, to, weight};
        edges.push_back(edge);
        convertKey(getKey(from, to), key);

        insert(tree, &tree, key, 0, edgeId++, 8);
    }

    void _print(){
        int cnt = 0;
        Node65536 *current = static_cast<Node65536*>(tree65536);
        for(int i = 0; i < 65536; ++i){
            if(current->child[i] != NULL)
                std::cout<<" "<<i;
                ++cnt;
        }
        std::cout<<std::endl;
        std::cout<<"cnt: "<<cnt<<std::endl;
        std::cout<<"sizeof 65536: "<<sizeof(Node65536) << " " << sizeof(int)<<std::endl;
    }

    void print(Node *current_node) {
        switch (current_node->type) {
            case NodeType4: {
                Node4 *node = static_cast<Node4 *>(current_node);
                std::cout << "Keys on root: ";
                for (unsigned i = 0; i < node->count; i++) {
                    std::cout << " " << (int) (node->key[i]);
                }
                std::cout << std::endl;
                return;
            }
            case NodeType16: {
                Node16 *node = static_cast<Node16 *>(current_node);
                std::cout << "Keys on root: ";
                for (unsigned i = 0; i < node->count; i++) {
                    std::cout << " " << (int) (node->key[i]);
                }
                std::cout << std::endl;
                return;
            }

        }

    }

    template<typename CB>
    void applyAllEdges(uint32_t from,  CB &lambdaCallback){
        Node65536 *current = static_cast<Node65536 *>(tree65536);
        Node* firstMatchingNode = current->child[from >> 16];
        current = static_cast<Node65536 *>(firstMatchingNode);
        firstMatchingNode = current->child[from & 65535];

        find_all_neighbors_lambda(firstMatchingNode, lambdaCallback);
    };

    template<typename CB>
    void applyAllEdges_old(uint32_t from,  CB &lambdaCallback){
        uint8_t key[8];
        convertKey(getKey(from, 0), key);
        Node* firstMatchingNode = lookup(tree, key, 4, 0, 8);
        find_all_neighbors_lambda(firstMatchingNode, lambdaCallback);
    };

    EdgeIter get_neighbors_iter(uint32_t from) {
        uint8_t key[8];
        convertKey(getKey(from, 0), key);
        Node* firstMatchingNode = lookup(tree, key, 4, 0, 8);
        return EdgeIter(firstMatchingNode, &(edges), this);
    }

    std::vector<std::pair<uint32_t, uint32_t>> get_neighbors(uint32_t from) {
        std::vector<std::pair<uint32_t, uint32_t>> res;
        Node65536 *current = static_cast<Node65536 *>(tree65536);
        //std::cout<<from<<" : "<<(from >> 16)<<std::endl;
        if(current->child[from >> 16] == NULL){
            current->child[from >> 16] = new Node65536();
            //std::cout<<"created"<<std::endl;
        }
        current = static_cast<Node65536 *>(current->child[from >> 16]);

        find_all_neighbors(res, current->child[from & 65535], 1);

        return res;
    }


    std::vector<std::pair<uint32_t, uint32_t>> get_neighbors_pre(uint32_t idx) {
        std::vector<std::pair<uint32_t, uint32_t>> res;
        int maxKeyLength = 8;
        int depth = 0; // length
        int keyLength = 8;

        // to find first 4 8-bits for node idx
        uint8_t key[8];

        convertKey(getKey(idx, 0), key);

        Node *node = tree; // root

        bool skippedPrefix = false; // Did we optimistically skip some prefix without checking it?

        while (node != NULL && depth < 4) {
            if (isLeaf(node)) {

                std::cout << "Leaf case existed !!!" << std::endl;
                //find_all_neighbors(res, node);
                uint32_t to = getLeafValue(node);
                //std::cout <<"To: "<< edges[to].to << std::endl;
                res.push_back(std::make_pair(edges[to].to, edges[to].weight));
                return res;
            }

            if (node->prefixLength) {
                if (node->prefixLength < maxPrefixLength) {
                    for (unsigned pos = 0; (pos < node->prefixLength) && (depth + pos < 4); pos++) {
                        if (key[depth + pos] != node->prefix[pos]) {
                            return res;
                        }
                    }
                } else
                    skippedPrefix = true;
                depth += node->prefixLength;
            }
            if (depth < 4) {
                node = *findChild(node, key[depth]);
                depth++;
            } else {
                break;
            }
        }

        if (node == NULL) {
            std::cout << "NULL case was hit" << std::endl;
            return res;
        }

        find_all_neighbors(res, node, 1);

        return res;
    }

    void finished() {}

    void sortByEdgesByNodeId() {}

    inline int *begin(int cur_vertex) { // TODO
        return NULL;
    }

    inline int *end(int cur_vertex) { // TODO
        return NULL;
    }

    inline int *begin_weights(int cur_vertex) { // TODO
        return NULL;
    }

};

#endif //DB_IMP_SEMINAR_ARTGRAPH_H