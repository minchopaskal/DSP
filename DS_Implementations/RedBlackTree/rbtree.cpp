#include <functional>
#include <iostream>
#include <utility>

#define DEBUG_MODE
//#define HAS_COLOR_MEMBER_DATA

#define BLACK false
#define RED   true

//TODO write remove logic

template <class T, class Compare = std::less<T>>
class red_black_tree {
public:
  using color = bool;

  struct node {
    T data;
#ifdef HAS_COLOR_MEMBER_DATA
    color isRed;
#endif
    node *left, *right;

    node (const T& data = T(),
          color isRed = true,
          node* left = nullptr,
          node* right = nullptr)
      : data(data),
        left(left),
        right(right)
    {
      set_color(isRed);
    }

    
#if defined(HAS_COLOR_MEMBER_DATA)
    inline node*& get_left() { return left; }
    inline void set_color(color colorVal) { isRed = colorVal; }
    inline bool is_red() const { return isRed; } 
#else
    // We ASSUME that the compiler aligns the memory
    
    node*& get_left() {
      std::cout << "got_left from the right place\n";
      left = (node*) (((std::size_t) left) & ~1);
      return left;
    }

    void set_color(color colorVal) {
      if (colorVal == RED) {
        left = (node*) (((std::size_t) left) | 1);
      } else {
        left = (node*) (((std::size_t) left) & ~1);
      }
    }
    
    bool is_red() const {
      return 1 & (std::size_t) left;
    } 
#endif
    inline node*& get_right() { return right; } // for consistency
 };

private:
  node* root;
  Compare compare;
  node** backtrack;

public:
  // ==================== Constructors ==================== //
  red_black_tree() : root(nullptr), backtrack(nullptr)  { }

  red_black_tree(const red_black_tree& other) : root(nullptr), backtrack(nullptr) {
    root = copy(other.root);
  }

  red_black_tree(red_black_tree&& other) : root(std::move(other.root)) {}

  // =============== Assignment Operators ================ //
  red_black_tree& operator=(const red_black_tree& rhs) {
    if (this != &rhs) {
      erase(root);
      root = copy(rhs.root);
    }

    return *this;
  }

  red_black_tree& operator=(red_black_tree&& rhs) {
    if (this != &rhs) {
      erase(root);
      root = nullptr;
      root = std::move(rhs.root);
    }

    return *this;
  }

  // =================== Destructor =================== //
  ~red_black_tree() {
    delete [] backtrack;
    erase(root);
  }

  // ============= Basic Tree Operations ============= //
  void insert(const T& value) {
    int i = 0;
    int size = 20;  // ~ 2 * log(1 000 000 000)
    if (backtrack != nullptr) delete[] backtrack;
    backtrack = new node*[size];
    backtrack[0] = root;

    while (backtrack[i] != nullptr) {
      ++i;
      if (compare(value, backtrack[i-1]->data)) backtrack[i] = backtrack[i-1]->get_left();
      else backtrack[i] = backtrack[i-1]->get_right();
      if (i == size) {
        resize_array(backtrack, size);
      }
    }

    if (i == 0) {
      root = new node(value, false);
      return;
    }

    node* newNode = new node(value);
    if (compare(value, backtrack[i-1]->data)) backtrack[i-1]->get_left() = newNode;
    else backtrack[i-1]->get_right() = newNode;
    backtrack[i] = newNode;
    insert_fix(i);
  }
  
  bool remove(const T& value) {
    return false;
  }

  bool search(const T& value) const {
    node* curr = root;
    while (curr != nullptr) {
      if (curr->data == value) {
        return true;
      }
      
      if (compare(value, curr->data)) {
        curr = curr->get_left();
      } else {
        curr = curr->get_right();
      }
    }

    return false;
  }
#if defined(DEBUG_MODE)
  void print() const {
    print(root);
    std::cout << std::endl;
  }
#endif

private:
    void insert_fix(int curr) {
    /* backtrack[curr] == current node
     * backtrack[curr-1] == it's parent
     * backtrack[curr-2] == curr node's grandparent
     */
    node *parent, *gparent;
    while (curr > 0 && (parent = backtrack[curr-1])->is_red()) {
      if (parent == (gparent = backtrack[curr-2])->get_left()) {
        node* uncle = gparent->get_right();
        if (uncle != nullptr && uncle->is_red()) {
          // Drop the blackness down the tree
          parent->set_color(BLACK);
          uncle->set_color(BLACK);
          gparent->set_color(RED);
          curr = curr - 2;
        } else { // Rotate so that we drop the height by 1
          if (backtrack[curr] == parent->get_right()) {
            rotate_left(parent, gparent);
          }
          parent->set_color(BLACK);
          gparent->set_color(RED);
          rotate_right(gparent, (curr < 3 ? nullptr : backtrack[curr-3]));
          curr -= 3;
        }
      } else { // parent is right child of grand-parent
        node* uncle = gparent->get_left();
        if (uncle != nullptr && uncle->is_red()) {
          parent->set_color(BLACK);
          uncle->set_color(BLACK);
          gparent->set_color(RED);
          curr = curr - 2;
        } else {
          if (backtrack[curr] == parent->get_left()) {
            rotate_right(parent, gparent);
          }
          parent->set_color(BLACK);
          gparent->set_color(RED);
          rotate_left(gparent, (curr < 3 ? nullptr : backtrack[curr-3]));
          curr -= 3;
        }
      }
    }

    
    root->set_color(BLACK);
  }

private:
  // ================== Helper Methods ================== //
#if defined(DEBUG_MODE)
  char name(bool c) const {
    return c ? 'r' : 'b';
  }
  
  void print(node* curr) const {
    if (curr == nullptr) {
      std::cout << "NIL";
      return;
    }
    std::cout << "([" << curr->data << ", " << name(curr->is_red()) << "] ";
    print(curr->get_left());
    std::cout << ' ';
    print(curr->get_right());
    std::cout << ")";
    return;
  }
#endif
  
  node* copy(node* other) {
    if (other == nullptr) {
      return nullptr;
    }

    node* newNode = new node();
    newNode->get_left() = copy(other->get_left());
    newNode->get_right() = copy(other->get_right());
    newNode->data = other->data;
    newNode->set_color(other->get_color());

    return newNode;
  }

  void erase(node* curr) {
    if (curr == nullptr) {
      return;
    }

    erase(curr->get_left());
    erase(curr->get_right());
    delete curr;
    
  }

  void rotate_left(node*& toRotate, node* parent) {
    node* rightChild = toRotate->get_right();

    if (parent == nullptr) {
      root = rightChild;
    } else  if (parent->get_left() == toRotate) {
      parent->get_left() = rightChild;
    } else {
      parent->get_right() = rightChild;
    }
    
    toRotate->get_right() = rightChild->get_left();
    rightChild->get_left() = toRotate;
    toRotate = rightChild;
  }

  void rotate_right(node*& toRotate, node* parent) {
    node* leftChild = toRotate->get_left();

    if (parent == nullptr) {
      root = leftChild;
    } else if (parent->get_left() == toRotate) {
      parent->get_left() = leftChild;
    } else {
      parent->get_right() = leftChild;
    }
    
    toRotate->get_left() = leftChild->get_right();
    leftChild->get_right() = toRotate;
    toRotate = leftChild;
  }

  void resize_array(node**& arr, int& size) {
    node** newArr = new node*[size *= 2];
    for ( int i = 0; i < size; ++i) {
      newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
  }
};
