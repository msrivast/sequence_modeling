#include "BRT.h"
#include <tuple>
#include <assert.h>
using namespace std;

BRT::BRT()
{
  T = NULL;
}

BRT::~BRT()
{
  for(int i = T->size-1; i >= 0; i--) T=remove(T, i);
}


void BRT::update_size(Node *n)
{
  n->size = 1;
  if (n->left != NULL) n->size += n->left->size;
  if (n->right != NULL) n->size += n->right->size;
}

int BRT::select(int r) {
  Node *N = select(T,r);
  return N->key;
}
// Return a pointer to the rank-r element 
BRT::Node *BRT::select(Node *root, int r)
{
  assert (r >= 0 && r < root->size);
  int root_rank = root->left == NULL ? 0 : root->left->size;
  if (r == root_rank) return root;
  if (r <  root_rank) return select(root->left, r);
  return select(root->right, r - root_rank - 1);
}


void BRT::print_inorder(){print_inorder(T);}
void BRT::print_inorder(Node *root)
{
  if (root == NULL) return;
  print_inorder(root->left);
  cout << root->key << "\t";
  print_inorder(root->right);
}

// Split tree on rank r into tree L (containing keys of ranks < r) and tree R
pair<BRT::Node *, BRT::Node *> BRT::split(Node *root, int r)
{
  pair <Node *, Node *> result = make_pair (root, root);
  if (root == NULL) return result;
  assert (r >= 0 && r <= root->size);
  int root_rank = root->left == NULL ? 0 : root->left->size;
  if (r <= root_rank) tie (result.first, root->left)   = split (root->left, r);
  else tie (root->right, result.second) = split (root->right, r - root_rank - 1);
  update_size (root);
  return result;
}

void BRT::insert(int r, int v)  {T = insert(T, r,v);}
// Insert new value v so it becomes the element at rank r
BRT::Node *BRT::insert(Node *root, int r, int v)
{
  if (root == NULL) return new Node(v);
  assert (r >= 0 && r <= root->size);
  int root_rank = root->left == NULL ? 0 : root->left->size;
  if (rand() % (1 + root->size) == 0) {
    Node *new_root = new Node(v);
    tie (new_root->left, new_root->right) = split (root, r);
    update_size (new_root);
    return new_root;
  } 
  if (r <= root_rank) root->left  = insert(root->left,  r, v);
  else root->right = insert(root->right, r - root_rank - 1, v);
  update_size (root);
  return root;
}

BRT::Node *BRT::join(Node *L, Node *R)
{
  if (L == NULL) return R;
  if (R == NULL) return L;
  Node *root = (rand() % (L->size + R->size) < L->size) ? L : R;
  if (root == L) L->right = join(L->right, R); 
  else           R->left  = join(L, R->left);   
  update_size (root);
  return root;
}

void BRT::remove(int r) {T = remove(T, r);}
// Remove the rank-r element from a tree (should only be called on a non-empty tree)
BRT::Node *BRT::remove(Node *root, int r)
{
  assert (root != NULL);
  assert (r >= 0 && r < root->size);
  int root_rank = root->left == NULL ? 0 : root->left->size;
  if (r == root_rank) {
    Node *result = join(root->left, root->right);
    delete root;
    return result;
  }
  if (r < root_rank) root->left  = remove (root->left, r);
  else               root->right = remove (root->right, r - root_rank - 1);
  update_size (root);
  return root;
}

