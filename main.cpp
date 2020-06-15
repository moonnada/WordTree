#include <iostream>
#include <string>
#include <cassert>
using namespace std;
typedef string ItemType;

struct WordNode {
    ItemType m_data;
    WordNode *m_left;
    WordNode *m_right;
    int count;
    // You may add additional data members and member functions in WordNode
};

class WordTree {
    
private:
    WordNode *root;
    void Insert(WordNode*& node, ItemType item);
    int helpDistinct(WordNode* node) const;
    WordNode* newTree(WordNode* node);
    int CountTreeTotal(WordNode* node) const;
    void Destroy(WordNode*& node);
    
public:
    // default constructor
    WordTree() : root(nullptr) { };
    // copy constructor
    WordTree(const WordTree& rhs);
    // assignment operator
    const WordTree& operator=(const WordTree& rhs);
    // Inserts v into the WordTree
    void add(ItemType v);
    // Returns the number of distince words / nodes
    int distinctWords() const;
    // Returns the total number of words inserted, including duplicate
    // values
    int totalWords() const;
    // Prints the LinkedList
    friend ostream& operator<<(ostream &out, const WordTree& rhs);
    // Destroys all the dynamically allocated memory
    // in the tree.
    ~WordTree();
};


WordNode* WordTree::newTree(WordNode* node) {
    if (node == nullptr)   //if node is empty, the tree is empty too
        return nullptr;
    
    WordNode* temp = new WordNode;
    temp->m_data = node->m_data;
    temp->m_left = newTree(node->m_left);  //recursive call for left pointer
    temp->m_right = newTree(node->m_right);  //recursive call for right pointer
    temp->count = node->count;
    
    return temp;
}

WordTree::WordTree(const WordTree& rhs) {
    this->root = newTree(rhs.root);  //call helper function to make a tree
}

int WordTree::helpDistinct(WordNode* node) const {
    if (node == nullptr)
        return 0;
    return 1 + helpDistinct(node->m_left) + helpDistinct(node->m_right);
}

int WordTree::distinctWords() const {
    if(root == nullptr) //if root is nullptr, the tree is empty
        return 0;
    return helpDistinct(root);  //call helper function and return value
}

int WordTree::CountTreeTotal(WordNode* node) const { //by using pre-order traversal to add up total value
    if (node == nullptr)
        return 0;
    return node->count+CountTreeTotal(node->m_left)+CountTreeTotal(node->m_right);
}


int WordTree::totalWords() const {
    return CountTreeTotal(root);  //call helper function and return value
}


void WordTree::Insert(WordNode*& node, ItemType item) {
    if (node == nullptr) {     //check if node is empty, then insert a value
        node = new WordNode;
        node->m_data = item;
        node->m_right = nullptr;
        node->m_left = nullptr;
        node->count = 1;
        return;
    }
    
    if (node->m_data == item){  //if the value is equal to value of node, then increment
        node->count++;
        return;
    }
    if (item > node->m_data)
        Insert(node->m_right, item); //recursive call to function, passing same value and right pointer
    else
        Insert(node->m_left, item); //recursive call to function, passing same value and left pointer
}


void WordTree::add(ItemType v) {
    Insert(root, v);  //call helper function
}



void helpOperator(ostream& out, WordNode* node) {
    if (node != nullptr){ //if node is not null and left pointer is not null, then helper function.
        if(node->m_left != nullptr)
            helpOperator(out, node->m_left); //call helper function for left function
        out << node->m_data<<" "<<node->count<<endl;
        helpOperator(out, node->m_right); // call helper function for right pointer
    }
}

ostream& operator << (ostream& out, const WordTree& rhs) {
    helpOperator(out, rhs.root);  //call helper function
    return out;
}


void WordTree::Destroy(WordNode*& node) {  //by using post-order traversal, destroy a node
    if (node != nullptr) {  //check node is empty or not
        Destroy(node->m_right);
        Destroy(node->m_left);
        delete node;
    }
    node = nullptr;
}

WordTree::~WordTree() { //destructor
    Destroy(root);  //call helper function
}


const WordTree& WordTree::operator=(const WordTree& rhs) { // assignment operator
    if(&rhs == this) //if left and right side are equal
        return rhs;
    Destroy(root);  //destory the orignal tree
    WordTree *temp = new WordTree(rhs);
    root = temp->root;
    return *this;
}




int main() {
    WordTree t;
    
    t.add("Skyler");
    t.add("Walter");
    t.add("Walter");
    t.add("Walter");
    
    assert(t.distinctWords() == 2);
    assert(t.totalWords() == 4);
    WordTree y;
    
    
    y.add("Skyler");
    y.add("Walter");
    y.add("Walter");
    y.add("Hank");
    y.add("Gus");
    y.add("Walter");
    y.add("Gus");
    
    cout << y;
    
    {
        WordTree tree;
        tree.add("");
        tree.add("");
        
        assert(tree.distinctWords() == 1);
        assert(tree.totalWords() == 2);
    }
    
    {
        
    }
}


