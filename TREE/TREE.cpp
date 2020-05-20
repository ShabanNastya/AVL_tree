#include <iostream>
using namespace std;


class Node
{
public:
	int key;
	Node* left;
	Node* right;
	int depth;
};

int max(int, int);
int depth(Node*);
Node* new_node(int);
Node* rotate_left(Node*);
Node* rotate_right(Node*);
int getBalance(Node*);
Node* insert(Node*, int);
Node* min_value_node(Node*);
Node* delete_node(Node*, int);
void LNR(Node*);
void LRN(Node*);
void in_order(Node*);


int main()
{
	setlocale(LC_ALL, "Russian");
	Node* root = NULL;

	root = insert(root, 35);
	root = insert(root, 82);
	root = insert(root, 9);
	root = insert(root, 18);
	root = insert(root, 2);
	root = insert(root, 1);
	root = insert(root, 44);

	in_order(root);
	return 0;
}


int max(int a, int b) {
	return (a > b) ? a : b;
}

int depth(Node* n)
{
	if (n == NULL)
		return 0;
	return n->depth;
}

Node* new_node(int key)
{
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->depth = 1;
	return(node);
}

Node* rotate_left(Node* x)
{
	Node* y = x->right;
	Node* T2 = y->left;

	y->left = x;
	x->right = T2;
	x->depth = max(depth(x->left),
		depth(x->right)) + 1;
	y->depth = max(depth(y->left),
		depth(y->right)) + 1;

	return y;
}

Node* rotate_right(Node* y)
{
	Node* x = y->left;
	Node* T2 = x->right;

	x->right = y;
	y->left = T2;
	y->depth = max(depth(y->left),
		depth(y->right)) + 1;
	x->depth = max(depth(x->left),
		depth(x->right)) + 1;

	return x;
}

int getBalance(Node* N)
{
	if (N == NULL)
		return 0;
	return depth(N->left) -
		depth(N->right);
}

Node* insert(Node* node, int key) {

	if (node == NULL)
		return(new_node(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;

	node->depth = 1 + max(depth(node->left), depth(node->right));

	int balance = getBalance(node);

	if (balance > 1 && key < node->left->key)
		return rotate_right(node);

	if (balance < -1 && key > node->right->key)
		return rotate_left(node);
	if (balance > 1 && key > node->left->key)
	{
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	if (balance < -1 && key < node->right->key)
	{
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}

Node* min_value_node(Node* node)
{
	Node* current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}

Node* delete_node(Node* root, int key)
{
	if (root == NULL)
		return root;

	if (key < root->key)
		root->left = delete_node(root->left, key);

	else if (key > root->key)
		root->right = delete_node(root->right, key);

	else
	{
		if ((root->left == NULL) ||
			(root->right == NULL))
		{
			Node* temp = root->left ?
				root->left :
				root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			Node* temp = min_value_node(root->right);

			root->key = temp->key;

			root->right = delete_node(root->right,
				temp->key);
		}
	}

	if (root == NULL)
		return root;

	root->depth = 1 + max(depth(root->left),
		depth(root->right));

	int balance = getBalance(root);

	if (balance > 1 &&
		getBalance(root->left) >= 0)
		return rotate_right(root);

	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = rotate_left(root->left);
		return rotate_right(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return rotate_left(root);

	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}
	return root;
}

void LNR(Node* root)
{
	if (root) {
		cout << root->key << " ";
		LNR(root->left);
		LNR(root->right);
	}
}

void LRN(Node* root)
{
	if (root) {
		LRN(root->left);
		LRN(root->right);
		cout << root->key << " ";
	}
}

void in_order(Node* root)
{
	if (root != NULL)
	{
		in_order(root->left);
		cout << root->key << " ";
		in_order(root->right);
	}
}
