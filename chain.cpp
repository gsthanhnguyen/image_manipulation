#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
    /* YOUR CODE HERE */
    // cout << "start ~chain" << endl;
    // clear();
    // delete head_;
    // head_ = NULL;
    // cout << "end ~chain" << endl;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
    /* YOUR CODE HERE */
    Node *cur = head_; // cur = sentinel node
    Node *new_block = new Node(ndata);
    new_block->next = head_;

    if (length_ == 0)
    {
        cur->next = new_block;
    }
    else
    {
        for (int i = 0; i < length_; i++)
        {
            cur = cur->next;
        }
        cur->next = new_block;
    }
    length_ += 1;
}

/**
 * Swaps the two nodes at the indexes "node1" and "node2".
 * The indexes of the nodes are 1 based.
 * assumes i and j are valid (in {1,length_} inclusive)
 *
 */
void Chain::swap(int i, int j)
{
    /* YOUR CODE HERE */
    Node *first_node = head_->next;
    Node *node_i = walk(first_node, i - 1);
    Node *node_j = walk(first_node, j - 1);

    // get Node before i
    Node *node_before_i = walk(first_node, i - 1 - 1);
    // get Node before j
    Node *node_before_j = walk(first_node, j - 1 - 1);

    // swap
    Node *node_after_i = walk(first_node, i);
    Node *node_after_j = walk(first_node, j);

    node_before_i->next = node_j;
    node_j->next = node_after_i;

    node_before_j->next = node_i;
    node_i->next = node_after_j;

}

/**
 * Reverses the chain
 */
void Chain::reverse()
{
    /* YOUR CODE HERE */
    Node *prev = NULL;
    Node *cur = head_;
    Node *next = NULL;
    for (int i = 0; i <= length_; i++)
    {
        next = cur->next;
        cur->next = prev;

        prev = cur;
        cur = next;
    }

    head_->next = prev;
}

/*
 * Modifies the current chain by "rotating" every k nodes by one position.
 * In every k node sub-chain, remove the first node, and place it in the last
 * position of the sub-chain. If the last sub-chain has length less than k,
 * then don't change it at all.
 * Some examples with the chain a b c d e:
 *   k = 1: a b c d e
 *   k = 2: b a d c e
 *   k = 3: b c a d e
 *   k = 4: b c d a e
 */
void Chain::rotate(int k)
{
    /* YOUR CODE HERE */
    if (k == 1)
    {
        return;
    }

    Node *cur = head_;
    for (int steps = 1; steps <= length_; steps += k)
    {
        if (steps + (k - 1) > length_)
        {
            return;
        }
        Node *first_node_subchain = walk(cur, steps);
        Node *before_first_node_subchain = (steps == 1) ? head_ : (walk(cur, steps - 1));
        Node *after_first_node_subchain = first_node_subchain->next;

        Node *last_node_subchain = walk(cur, steps + k - 1);
        // Node* before_last_node_subchain = walk(cur, steps + k -1 -1);
        Node *after_last_node_subchain = last_node_subchain->next;

        before_first_node_subchain->next = after_first_node_subchain;
        last_node_subchain->next = first_node_subchain;
        first_node_subchain->next = after_last_node_subchain;

    }
}

/**
 * Destroys ALL dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::clear()
{   
    // cout << "start clear" << endl;
    // Node *cur = head_->next;
    // Node *next = NULL;
    // for (int i = 0; i < length_ - 1; i++)
    // {
    //     next = cur->next;
    //     delete cur;
    //     cur = next;
    // }
    // next = NULL;
    // delete cur;
    // cur = NULL;

    // head_->next = head_;

    // length_ = 0;

    // cout << "end clear" << endl;




    // cout << "start clear" << endl;
    // Node *cur = head_;
    // Node *next = NULL;
    // for (int i = 0; i < length_; i++)
    // {   
    //     cout << "deleted block at index: " << i << endl;
    //     next = cur->next;
    //     delete cur;
    //     cur = next;
    // }
    // // cur = NULL;
    // delete next;
    // // next = NULL;
    // length_ = 0;

    // cout << "end clear" << endl;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */
void Chain::copy(Chain const &other)
{
    /* YOUR CODE HERE */


    Node *copyBlock = other.head_->next;

    head_ = other.head_;
    // head_ = new Node(*(other.head_));
    // head_ = new Node();

    for (int i = 1; i <= other.length_; i++)
    {
        insertBack(copyBlock->data);
        copyBlock = copyBlock->next;
    }

    length_ = other.length_;
    width_ = other.width_;
    height_ = other.height_;

}