#ifndef TREE234_H
#define TREE234_H

#include <stack>
#include "Node234.h"

template<typename IteratorType>
class Tree234 {
protected:
   Node234* root;
   
   virtual Node234* AllocNode(int key, Node234* leftChild = nullptr,
      Node234* middle1Child = nullptr) {
      return new Node234(key, leftChild, middle1Child);
   }
   
   // Recursively deletes the node's children, then deletes the node itself.
   virtual void DeleteTree(Node234* node) {
      if (node) {
         // Delete all child subtrees first
         for (int i = 0; i < 4; i++) {
            DeleteTree(node->GetChild(i));
         }
         
         // Delete the node itself
         delete node;
      }
   }
   
   // Recursive helper function for search.
   virtual Node234* SearchRecursive(int key, Node234* node) {
      if (node == nullptr) {
         return nullptr;
      }
            
      // Check if the node contains the key
      if (node->HasKey(key)) {
         return node;
      }
        
      // Recursively search the appropriate subtree
      return SearchRecursive(key, node->NextNode(key));
   }
   
   // Splits a full node, moving the middle key up into the parent node.
   // Precondition: nodeParent has one or two keys.
   virtual Node234* Split(Node234* node, Node234* nodeParent) {
      Node234* splitLeft = AllocNode(node->GetKey(0), node->GetChild(0), node->GetChild(1));
      Node234* splitRight = AllocNode(node->GetKey(2), node->GetChild(2), node->GetChild(3));
      if (nodeParent) {
         nodeParent->InsertKeyWithChildren(node->GetKey(1), splitLeft, splitRight);
         delete node;
      }
      else {
         // Split root
         nodeParent = AllocNode(node->GetKey(1), splitLeft, splitRight);
         delete root;
         root = nodeParent;
      }
        
      return nodeParent;
   }
        
   // Fuses a parent node and two children into one node. 
   // Precondition: leftNode and rightNode must have one key each.
   virtual Node234* Fuse(Node234* parent, Node234* leftNode, Node234* rightNode) {
      if (parent == root && parent->GetKeyCount() == 1) {
         return FuseRoot();
      }

      int leftNodeIndex = parent->GetChildIndex(leftNode);
      int middleKey = parent->GetKey(leftNodeIndex);
      Node234* fusedNode = AllocNode(leftNode->GetKey(0));
      fusedNode->SetKey(middleKey, 1);
      fusedNode->SetKey(rightNode->GetKey(0), 2);
      fusedNode->SetKeyCount(3);
      fusedNode->SetChildren(leftNode->GetChild(0), leftNode->GetChild(1),
         rightNode->GetChild(0), rightNode->GetChild(1));
      int keyIndex = parent->GetKeyIndex(middleKey);
      parent->RemoveKey(keyIndex);
      parent->SetChild(fusedNode, keyIndex);
      delete leftNode;
      delete rightNode;
      return fusedNode;
   }

   // Fuses the tree's root node with the root's two children. 
   // Precondition: Each of the three nodes must have one key each.
   virtual Node234* FuseRoot() {
      Node234* oldLeft = root->GetChild(0);
      Node234* oldMiddle1 = root->GetChild(1);
      root->SetKey(root->GetKey(0), 1);
      root->SetKey(oldLeft->GetKey(0), 0);
      root->SetKey(oldMiddle1->GetKey(0), 2);
      root->SetKeyCount(3);
      root->SetChildren(oldLeft->GetChild(0), oldLeft->GetChild(1),
         oldMiddle1->GetChild(0), oldMiddle1->GetChild(1));
      delete oldLeft;
      delete oldMiddle1;
      return root;
   }
   
   virtual int GetHeight(Node234* node) {
      if (node->GetChild(0) == nullptr) {
         return 0;
      }
      return 1 + GetHeight(node->GetChild(0));
   }
   
   // Searches for, and returns, the minimum key in a subtree
   virtual int GetMinKey(Node234* node) {
      Node234* current = node;
      while (current->GetChild(0)) {
         current = current->GetChild(0);
      }
      return current->GetKey(0);
   }
   
   // Finds and replaces one key with another. The replacement key must
   // be known to be a key that can be used as a replacement without violating
   // any of the 2-3-4 tree rules.
   virtual bool KeySwap(Node234* node, int existing, int replacement) {
      if (node == nullptr) {
         return false;
      }

      int keyIndex = node->GetKeyIndex(existing);
      if (keyIndex == -1) {
         Node234* next = node->NextNode(existing);
         return KeySwap(next, existing, replacement);
      }

      node->SetKey(replacement, keyIndex);
      return true;
   }
   
   // Rotates or fuses to add 1 or 2 additional keys to a node with 1 key.
   virtual Node234* Merge(Node234* node, Node234* nodeParent) {
      // Get pointers to node's siblings
      int nodeIndex = nodeParent->GetChildIndex(node);
      Node234* leftSibling = nodeParent->GetChild(nodeIndex - 1);
      Node234* rightSibling = nodeParent->GetChild(nodeIndex + 1);
    
      // Check siblings for a key that can be transferred
      if (leftSibling && leftSibling->GetKeyCount() >= 2) {
         RotateRight(leftSibling, nodeParent);
      }
      else if (rightSibling && rightSibling->GetKeyCount() >= 2) {
         RotateLeft(rightSibling, nodeParent);
      }
      else { // fuse
         if (leftSibling == nullptr) {
            node = Fuse(nodeParent, node, rightSibling);
         }
         else {
            node = Fuse(nodeParent, leftSibling, node);
         }
      }

      return node;
   }
   
   virtual void RotateLeft(Node234* node, Node234* nodeParent) {
      // Get the node's left sibling
      int nodeIndex = nodeParent->GetChildIndex(node);
      Node234* leftSibling = nodeParent->GetChild(nodeIndex - 1);

      // Get the key from the parent that will be copied into the left sibling
      int keyForLeftSibling = nodeParent->GetKey(nodeIndex - 1);

      // Append the key to the left sibling
      leftSibling->AppendKeyAndChild(keyForLeftSibling, node->GetChild(0));

      // Replace the parent's key that was appended to the left sibling
      nodeParent->SetKey(node->GetKey(0), nodeIndex - 1);

      // Remove key A and left child from node
      node->RemoveKey(0);
   }
    
   virtual void RotateRight(Node234* node, Node234* nodeParent) {
      // Get the node's right sibling
      int nodeIndex = nodeParent->GetChildIndex(node);
      Node234* rightSibling = nodeParent->GetChild(nodeIndex + 1);
        
      // Get the key from the parent that will be copied into the right sibling
      int keyForRightSibling = nodeParent->GetKey(nodeIndex);
        
      // Shift key and child pointers in right sibling
      rightSibling->SetKey(rightSibling->GetKey(1), 2);
      rightSibling->SetKey(rightSibling->GetKey(0), 1);
      rightSibling->SetChild(rightSibling->GetChild(2), 3);
      rightSibling->SetChild(rightSibling->GetChild(1), 2);
      rightSibling->SetChild(rightSibling->GetChild(0), 1);
        
      // Set key A and the left child of rightSibling
      rightSibling->SetKey(keyForRightSibling, 0);
      rightSibling->SetChild(node->RemoveRightmostChild(), 0);
      
      // rightSibling has gained a key
      rightSibling->SetKeyCount(rightSibling->GetKeyCount() + 1);
        
      // Replace the parent's key that was prepended to the right sibling
      nodeParent->SetKey(node->RemoveRightmostKey(), nodeIndex);
   }

public:
   // Initializes the tree by assigning the root node pointer with nullptr.
   Tree234() {
      root = nullptr;
   }
   
   virtual ~Tree234() {
      DeleteTree(root);
   }

   // Inserts a new key into this tree, provided the tree doesn't already
   // contain the same key.
   virtual Node234* Insert(int key, Node234* node = nullptr,
      Node234* nodeParent = nullptr) {
      // Special case for empty tree
      if (root == nullptr) {
         root = AllocNode(key);
         return root;
      }

      // If the node argument is null, recursively call with root
      if (node == nullptr) {
         return Insert(key, root, nullptr);
      }

      // Check for duplicate key
      if (node->HasKey(key)) {
         // Duplicate keys are not allowed
         return nullptr;
      }

      // Preemptively split full nodes
      if (node->GetKeyCount() == 3) {
         node = Split(node, nodeParent);
      }

      // If node is not a leaf, recursively insert into child subtree
      if (!node->IsLeaf()) {
         return Insert(key, node->NextNode(key), node);
      }
        
      // key can be inserted into leaf node
      node->InsertKey(key);
      return node;
   }

   // Searches this tree for the specified key. If found, the node containing
   // the key is returned. Otherwise null is returned.
   virtual Node234* Search(int key) {
      return SearchRecursive(key, root);
   }
   
   // Returns the height of this tree.
   virtual int GetHeight() {
      return GetHeight(root);
   }
   
   // Returns the number of keys in this tree.
   virtual int Length() const {
      int count = 0;
      std::stack<Node234*> nodes;
      nodes.push(root);
      
      while (!nodes.empty()) {
         Node234* node = nodes.top();
         nodes.pop();
         if (node) {
            // Add the number of keys in the node to the count
            count = count + node->GetKeyCount();
                
            // Push children
            nodes.push(node->GetChild(0));
            nodes.push(node->GetChild(1));
            nodes.push(node->GetChild(2));
            nodes.push(node->GetChild(3));
         }
      }
      return count;
   }

   // Finds and removes the specified key from this tree.
   virtual bool Remove(int key) {
      // Special case for tree with 1 key
      if (root->IsLeaf() && root->GetKeyCount() == 1) {
         if (root->GetKey(0) == key) {
            delete root;
            root = nullptr;
            return true;
         }
         return false;
      }

      Node234* currentParent = nullptr;
      Node234* current = root;
      while (current) {
         // Merge any non-root node with 1 key
         if (current->GetKeyCount() == 1 && current != root) {
            current = Merge(current, currentParent);
         }

         // Check if current node contains key
         int keyIndex = current->GetKeyIndex(key);
         if (keyIndex != -1) {
            if (current->IsLeaf()) {
               current->RemoveKey(keyIndex);
               return true;
            }

            // The node contains the key and is not a leaf, so the key is
            // replaced with the successor
            Node234* tmpChild = current->GetChild(keyIndex + 1);
            int tmpKey = GetMinKey(tmpChild);
            Remove(tmpKey);
            KeySwap(root, key, tmpKey);
            return true;
         }

         // Current node does not contain key, so continue down tree
         currentParent = current;
         current = current->NextNode(key);
      }
                
      // key not found
      return false;
   }
   
   // Added to support range-based for loops. IteratorType is a template type
   // for the iterator, and will be Tree234Iterator when grading submitted code.
   virtual IteratorType begin() const {
      return IteratorType(root);
   }
   
   virtual IteratorType end() const {
      return IteratorType(nullptr);
   }
};

#endif