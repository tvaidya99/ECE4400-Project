#include <iostream>
#include <string.h>
using namespace std;

template <typename T>
class Product
{
public:
    int count, expiry;
    float price;
    T key;
    string name;
};

template <typename T>
class BTreeNode
{
public:
    Product<T> *products; // An array of products
    int t;                // Minimum degree (defines the range for number of keys)
    BTreeNode **C;        // An array of child pointers
    int n;                // Current number of keys
    bool leaf;            // Is true when node is leaf. Otherwise false

    BTreeNode(int degree, bool isLeaf)
    {
        t = degree;
        products = new Product<T>[2 * degree - 1];
        leaf = isLeaf;
        C = new BTreeNode<T> *[2 * degree];
        n = 0;
    }

    // A utility function that returns the index of the first key that is
    // greater than or equal to k
    int findKey(int key)
    {
        int idx = 0;
        while (idx < n && products[idx].key < key)
            ++idx;
        return idx;
    }

    // Remove the idx product from this leaf node
    void removeFromLeaf(int idx)
    {
        // Move all the products after the idx-th pos one place backward
        for (int i = idx + 1; i < n; ++i)
            products[i - 1] = products[i];

        // Reduce the count of keys
        n--;

        return;
    }

    // Remove the idx product from this non-leaf node
    void removeFromNonLeaf(int idx)
    {

        Product<T> product = products[idx];

        // If the child that precedes product (C[idx]) has atleast t products,
        // find the predecessor of product in the subtree rooted at
        // C[idx]. Replace product by pred. Recursively delete predecessor
        // in C[idx]
        if (C[idx]->n >= t)
        {
            Product<T> predecessor = getPredecessor(idx);
            products[idx] = predecessor;
            C[idx]->deleteProduct(predecessor.key, predecessor.name);
        }

        // If the child C[idx] has less that t keys, examine C[idx+1].
        // If C[idx+1] has atleast t keys, find the successor of the product in
        // the subtree rooted at C[idx+1]
        // Replace product by successor
        // Recursively delete successor in C[idx+1]
        else if (C[idx + 1]->n >= t)
        {
            Product<T> successor = getSuccessor(idx);
            products[idx] = successor;
            C[idx + 1]->deleteProduct(successor.key, successor.name);
        }

        // If both C[idx] and C[idx+1] has less that t keys,merge product and all of C[idx+1]
        // into C[idx]
        // Now C[idx] contains (2t-1) keys
        // Free C[idx+1] and recursively delete product from C[idx]
        else
        {
            merge(idx);
            C[idx]->deleteProduct(product.key, product.name);
        }
        return;
    }

    // A function to get predecessor of products[idx]
    Product<T> getPredecessor(int idx)
    {
        // Keep going to the right most node till we reach a leaf
        BTreeNode *cur = C[idx];
        while (!cur->leaf)
            cur = cur->C[cur->n];

        // Return the last key of the leaf
        return cur->products[cur->n - 1];
    }

    Product<T> getSuccessor(int idx)
    {

        // Keep going the left most node starting from C[idx+1] till we reach a leaf
        BTreeNode *cur = C[idx + 1];
        while (!cur->leaf)
            cur = cur->C[0];

        // Return the first key of the leaf
        return cur->products[0];
    }

    // Fill child C[idx] having less than t-1 keys
    void fill(int idx)
    {
        // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
        // from that child
        if (idx != 0 && C[idx - 1]->n >= t)
            borrowFromPrev(idx);

        // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
        // from that child
        else if (idx != n && C[idx + 1]->n >= t)
            borrowFromNext(idx);

        // Merge C[idx] with its sibling
        // If C[idx] is the last child, merge it with its previous sibling
        // Otherwise merge it with its next sibling
        else
        {
            if (idx != n)
                merge(idx);
            else
                merge(idx - 1);
        }
        return;
    }

    // A function to borrow a key from C[idx-1] and insert it
    // into C[idx]
    void borrowFromPrev(int idx)
    {

        BTreeNode *child = C[idx];
        BTreeNode *sibling = C[idx - 1];

        // The last key from C[idx-1] goes up to the parent and key[idx-1]
        // from parent is inserted as the first key in C[idx]. Thus, the  loses
        // sibling one key and child gains one key

        // Moving all key in C[idx] one step ahead
        for (int i = child->n - 1; i >= 0; --i)
            child->products[i + 1] = child->products[i];

        // If C[idx] is not a leaf, move all its child pointers one step ahead
        if (!child->leaf)
        {
            for (int i = child->n; i >= 0; --i)
                child->C[i + 1] = child->C[i];
        }

        // Setting child's first key equal to products[idx-1] from the current node
        child->products[0] = products[idx - 1];

        // Moving sibling's last child as C[idx]'s first child
        if (!child->leaf)
            child->C[0] = sibling->C[sibling->n];

        // Moving the key from the sibling to the parent
        // This reduces the number of keys in the sibling
        products[idx - 1] = sibling->products[sibling->n - 1];

        child->n += 1;
        sibling->n -= 1;

        return;
    }

    // A function to borrow a key from the C[idx+1] and place
    // it in C[idx]
    void borrowFromNext(int idx)
    {

        BTreeNode *child = C[idx];
        BTreeNode *sibling = C[idx + 1];

        // products[idx] is inserted as the last key in C[idx]
        child->products[(child->n)] = products[idx];

        // Sibling's first child is inserted as the last child
        // into C[idx]
        if (!(child->leaf))
            child->C[(child->n) + 1] = sibling->C[0];

        //The first key from sibling is inserted into products[idx]
        products[idx] = sibling->products[0];

        // Moving all keys in sibling one step behind
        for (int i = 1; i < sibling->n; ++i)
            sibling->products[i - 1] = sibling->products[i];

        // Moving the child pointers one step behind
        if (!sibling->leaf)
        {
            for (int i = 1; i <= sibling->n; ++i)
                sibling->C[i - 1] = sibling->C[i];
        }

        // Increasing and decreasing the key count of C[idx] and C[idx+1]
        // respectively
        child->n += 1;
        sibling->n -= 1;

        return;
    }

    // A function to merge C[idx] with C[idx+1]
    // C[idx+1] is freed after merging
    void merge(int idx)
    {
        BTreeNode *child = C[idx];
        BTreeNode *sibling = C[idx + 1];

        // Taking a key from the current node and inserting it into (t-1) position of C[idx]
        child->products[t - 1] = products[idx];

        // Copying the keys from C[idx+1] to C[idx] at the end
        for (int i = 0; i < sibling->n; ++i)
            child->products[i + t] = sibling->products[i];

        // Copying the child pointers from C[idx+1] to C[idx]
        if (!child->leaf)
        {
            for (int i = 0; i <= sibling->n; ++i)
                child->C[i + t] = sibling->C[i];
        }

        // Move all keys after idx in the current node one step before -
        // to fill the gap created after moving products[idx] to C[idx]
        for (int i = idx + 1; i < n; ++i)
            products[i - 1] = products[i];

        // Moving the child pointers after (idx+1) in the current node one
        // step before
        for (int i = idx + 2; i <= n; ++i)
            C[i - 1] = C[i];

        // Updating the key count of child and the current node
        child->n += sibling->n + 1;
        n--;

        // Freeing the memory occupied by sibling
        delete (sibling);
        return;
    }

    // Delete a product with key and a "name" rooted with this node
    void deleteProduct(T key, string name)
    {
        int idx = findKey(key);

        // check if product to be removed is present in the current node
        if (idx < n && products[idx].key == key)
        {
            bool found = false;
            int index = idx;
            while (index < n)
            {
                if (products[index].key == key)
                {
                    if (products[index].name == name)
                    {
                        found = true;
                        break;
                    }
                    else
                        index++;
                }
            }
            if (found)
            {
                // If the node is a leaf node - removeFromLeaf is called
                // Otherwise, removeFromNonLeaf function is called
                if (leaf)
                    removeFromLeaf(index);
                else
                    removeFromNonLeaf(index);
                return;
            }
        }
        // product not in the current node
        // If it's a leaf, the product doesn't exist
        if (leaf)
        {
            cout << "Product " << name << " does not exist in the store. Select one of the available products. \n";
            return;
        }

        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ((idx == n) ? true : false);

        // If the child where the key is supposed to exist has less than t keys,
        // we fill that child
        if (C[idx]->n < t)
            fill(idx);

        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > n)
            C[idx - 1]->deleteProduct(key, name);
        else
            C[idx]->deleteProduct(key, name);
        return;
    }

    // In-order traversal rooted with this node
    void sortedTraverse()
    {
        // There are n keys and n+1 children, traverse through n keys
        // and first n children
        int i;
        for (i = 0; i < n; i++)
        {
            // If not leaf, then before printing products[i],
            // traverse the subtree rooted with child C[i].
            if (leaf == false)
                C[i]->sortedTraverse(); // recurse through the subchildren

            cout << " " << products[i].name << " - $" << products[i].price << " - expires on " << products[i].expiry << "\n";
        }

        // Print the subtree rooted with last child
        if (leaf == false)
            C[i]->sortedTraverse();
    }

    /*

    template <typename T2>
    BTree<T2> sortWithKey(string sortToKey)
    {
        if (sortToKey == "price")
        {
            BTree<float> btreePrice(3, sortToKey);
            sort(btreePrice);
            return btreePrice;
        } else {
            BTree<int> btreeExpiry(3, sortToKey);
            sort(btreeExpiry);
            return btreeExpiry;
        }
    }

    template <typename T2>
    void sort(BTree<T2> btree)
    {
        // There are n keys and n+1 children, traverse through n keys
        // and first n children
        int i;
        for (i = 0; i < n; i++)
        {
            // If not leaf, then before printing products[i],
            // traverse the subtree rooted with child C[i].
            if (leaf == false)
                C[i]->sort(btree); // recurse through the subchildren

            btree.insert(products[i]);
        }

        // Print the subtree rooted with last child
        if (leaf == false)
            C[i]->sort(btree);
    }*/

    /*
    // Breadth first traversal rooted with this node
    void levelsTraverse()
    {
        // There are n keys and n+1 children
        // traverse through n keys
        int i;
        for (i = 0; i < n; i++)
        {
            // If not leaf, then print all keys
            cout << " " << products[i].name << "\n";
        }

        // print the next level
        if (leaf == false)
        {
            for (i = 0; i < n + 1; i++)
            {
                C[i]->levelsTraverse(); // recurse through the subchildren
            }
        }
    }*/

    // split the given node into two child
    void splitChild(int indexOfSplitNode, BTreeNode *splitNode)
    {
        // Create a node that will store (t-1) keys of splitNode
        BTreeNode<T> *x = new BTreeNode<T>(splitNode->t, splitNode->leaf);
        x->n = t - 1;

        // Copy the last t children (half of the total children) of splitNode to x
        if (splitNode->leaf == false)
        {
            for (int j = 0; j < t; j++)
                x->C[j] = splitNode->C[j + t];
        }

        // Copy the last (t-1) keys of splitNode to x
        for (int j = 0; j < t - 1; j++)
            x->products[j] = splitNode->products[j + t];

        // Reduce the number of keys in splitNode to prepare for split
        splitNode->n = t - 1;

        // Create space for new child after split
        for (int j = n; j >= indexOfSplitNode + 1; j--)
            C[j + 1] = C[j];

        // Add the new child after split to the current node
        C[indexOfSplitNode + 1] = x;

        // A key of splitNode will move to this node.
        // Find the location of new key and move all greater keys one space ahead
        for (int j = n - 1; j >= indexOfSplitNode; j--)
            products[j + 1] = products[j];

        // Copy the middle key of splitNode to this node
        products[indexOfSplitNode] = splitNode->products[t - 1];

        // Increment count of keys in this node
        n = n + 1;
    }

    // insert a element in a non full node
    void insertNonFull(Product<T> product)
    {
        // index of the rightmost element
        int i = n - 1;

        // if current node is a leaf node
        if (leaf == true)
        {
            // find the position for the new key
            while (i >= 0 && products[i].key > product.key)
            {
                // shift all greater keys one position to the right
                products[i + 1] = products[i];
                i--;
            }

            // insert the key at the found position
            products[i + 1] = product;

            // increment number of keys
            n = n + 1;
        }
        // not a leaf
        else
        {
            // find the position for the new key
            while (i >= 0 && products[i].key > product.key)
                i--;

            // check if the child of the selected key is full
            if (C[i + 1]->n == 2 * t - 1)
            {
                // If the child is full, then split it
                splitChild(i + 1, C[i + 1]);

                // After the child is split in two, check which one is going to have the new key
                if (products[i + 1].key < product.key)
                    i++;
            }
            // dig deeper into the child of child until a leaf is found
            C[i + 1]->insertNonFull(product);
        }
    }
};

template <typename T>
class BTree
{
    int t;

public:
    BTreeNode<T> *root;
    string key; // dictates whether the tree is sorted by "price" or "expiry"
    BTree(int degreeArg, string keyLocal)
    {
        root = NULL;
        t = degreeArg;
        key = keyLocal;
    }

    void insert(Product<T> product)
    {
        // If tree is empty
        if (root == NULL)
        {
            // Allocate memory for root
            root = new BTreeNode<T>(t, true);
            // set key of the product using which the tree will be sorted
            if (key == "price")
            {
                root->products[0].key = product.price;
            }
            else
            {
                root->products[0].key = product.expiry;
            }

            root->products[0].price = product.price;
            root->products[0].expiry = product.expiry;
            root->products[0].name = product.name;
            root->products[0].count = product.count;
            root->n = 1; // Update number of keys in root
        }
        // If tree is not empty
        else
        {
            // If root is full, then tree grows in height
            if (root->n == 2 * t - 1)
            {
                // Allocate memory for new root
                BTreeNode<T> *s = new BTreeNode<T>(t, false);
                // Make old root a child of new root
                s->C[0] = root;
                // Split the old root and move 1 key to the new root
                s->splitChild(0, root);
                // New root has two children now. Decide which of the
                // two children is going to have new key
                int i = 0;
                if (s->products[0].key < product.key)
                    i++;
                s->C[i]->insertNonFull(product);
                // Change root
                root = s;
            }
            // If root is not full, call insertNonFull for root
            else
                root->insertNonFull(product);
        }
    }
};
