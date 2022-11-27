// AVL Tree
#include "bits/stdc++.h"
using namespace std;
#define int long long

class Node
{
public:
	int data;
	Node* left;
	Node* right;
	int height;

	Node()
	{
		data = 0;
		left = right = NULL;
		height = 0;
	}

	Node(int data)
	{
		this->data = data;
		left = right = NULL;
		height = 0;
	}
};

class AVLTree {
public:
	Node* root;

	AVLTree()
	{
		root = NULL;
	}

	int get_height(Node* node)
	{
		if (node == NULL)
			return -1;
		return node->height;
	}

	int set_height(Node* node)
	{
		node->height = 1 + max(get_height(node->left), get_height(node->right));
		return node->height;
	}

	int get_bf(Node* node)
	{
		if (node == NULL)
			return 0;
		return abs(get_height(node->left) - get_height(node->right));
	}

	int get_case(Node* node)
	{
		if (get_height(node->left) > get_height(node->right))
		{
			if (get_height(node->left->left) > get_height(node->left->right))
				return 0;
			else
				return 1;
		}
		else
		{
			if (get_height(node->right->left) > get_height(node->right->right))
				return 2;
			else
				return 3;
		}
		return -1;
	}

	Node* ll_case(Node* node)
	{
		Node* temp = node->left;
		node->left = temp->right;
		temp->right = node;
		set_height(node);
		set_height(temp);
		return temp;
	}

	Node* lr_case(Node* node)
	{
		Node* temp = node->left;
		node->left = temp->right;
		temp->right = node->left->left;
		node->left->left = temp;
		set_height(temp);
		set_height(node->left);
		return ll_case(node);
	}

	Node* rr_case(Node* node)
	{
		Node* temp = node->right;
		node->right = temp->left;
		temp->left = node;
		set_height(node);
		set_height(temp);
		return temp;
	}

	Node* rl_case(Node* node)
	{
		Node* temp = node->right;
		node->right = temp->left;
		temp->left = node->right->right;
		node->right->right = temp;
		set_height(temp);
		set_height(node->right);
		return rr_case(node);
	}

	Node* refactor(Node* node)
	{
		switch (get_case(node))
		{
		case 0: return ll_case(node);
		case 1: return lr_case(node);
		case 2: return rl_case(node);
		case 3: return rr_case(node);
		default: return node;
		}
		return NULL;
	}

	Node* insert_node(Node* node, int data)
	{
		if (node == NULL)
			return new Node(data);
		if (data < node->data)
			node->left = insert_node(node->left, data);
		else if (data > node->data)
			node->right = insert_node(node->right, data);
		if (get_bf(node) > 1)
			node = refactor(node);
		set_height(node);
		return node;
	}

	void insert(int data)
	{
		root = insert_node(root, data);
	}

	bool search_node(Node* node, int data)
	{
		if (node == NULL)
			return false;
		if (data < node->data)
			return search_node(node->left, data);
		else if (data > node->data)
			return search_node(node->right, data);
		else
			return true;
	}

	bool search(int data)
	{
		return search_node(root, data);
	}

	pair<Node*, int> get_inorder_predecessor(Node* node)
	{
		pair<Node*, int> p;
		if (node->left == NULL && node->right == NULL)
			return {NULL, node->data};
		else if (node->right == NULL)
		{
			p = get_inorder_predecessor(node->left);
			node->left = p.first;
		}
		else
		{
			p = get_inorder_predecessor(node->right);
			node->right = p.first;
		}
		if (get_bf(node) > 1)
			node = refactor(node);
		set_height(node);
		return {node, p.second};
	}

	pair<Node*, int> get_inorder_successor(Node* node)
	{
		pair<Node*, int> p;
		if (node->left == NULL && node->right == NULL)
			return {NULL, node->data};
		else if (node->left == NULL)
		{
			p = get_inorder_successor(node->right);
			node->right = p.first;
		}
		else
		{
			p = get_inorder_successor(node->left);
			node->left = p.first;
		}
		if (get_bf(node) > 1)
			node = refactor(node);
		set_height(node);
		return {node, p.second};
	}

	pair<Node*, bool> delete_node(Node* node, int data)
	{
		if (node == NULL)
			return {NULL, false};
		pair<Node*, bool> p = {NULL, true};
		if (data < node->data)
		{
			p = delete_node(node->left, data);
			node->left = p.first;
		}
		else if (data > node->data)
		{
			p = delete_node(node->right, data);
			node->right = p.first;
		}
		else
		{
			pair<Node*, int> p_;
			if (node->left == NULL && node->right == NULL)
				node = NULL;
			else
			{
				if (node->left == NULL)
				{
					p_ = get_inorder_successor(node->right);
					node->right = p_.first;
				}
				else
				{
					p_ = get_inorder_predecessor(node->left);
					node->left = p_.first;
				}
				node->data = p_.second;
			}
		}
		if (p.second && get_bf(node) > 1)
			node = refactor(node);
		return {node, p.second};
	}

	bool del(int data)
	{
		pair<Node*, bool> p = delete_node(root, data);
		root = p.first;
		return p.second;
	}

	void print_tree(Node* node)
	{
		if (node == NULL)
			return;
		cout << node->data << " ";
		print_tree(node->left);
		print_tree(node->right);
	}
};

int32_t main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	AVLTree* tree = new AVLTree();

	int n = 6;
	vector<int> v = {20, 10, 30, 5, 15, 13};

	for (int i = 0; i < n; i++)
		tree->insert(v[i]);

	cout << "Preorder traversel : ";
	tree->print_tree(tree->root);
	cout << endl;

	int data = 20;
	if (tree->search(data))
		cout << data << " " << "Key found" << endl;
	else
		cout << data << " " << "Key not found" << endl;

	data = 20;
	if (tree->del(data))
		cout << data << " " << "Key deleted" << endl;
	else
		cout << data << " " << "Key not found" << endl;

	cout << "Preorder traversel after key deletion: ";
	tree->print_tree(tree->root);
	cout << endl;

	return 0;
}

// Red Black Tree
#include <bits/stdc++.h>
using namespace std;

enum Color { Red, Black };

class Node
{
public:
	int key;
	Color color;
	Node *left, *right, *parent;

	Node(int key)
	{
		this->key = key;
		parent = left = right = NULL;
		color = Red;
	}

	Node *get_uncle() {
		if (parent == NULL || parent->parent == NULL)
			return NULL;

		if (parent->is_on_left())
			return parent->parent->right;
		else
			return parent->parent->left;
	}

	bool is_on_left()
	{
		return this == parent->left;
	}

	Node *get_sibling()
	{
		if (parent == NULL)
			return NULL;

		if (is_on_left())
			return parent->right;

		return parent->left;
	}

	void move_node_down(Node *n_parent)
	{
		if (parent != NULL)
		{
			if (is_on_left())
				parent->left = n_parent;
			else
				parent->right = n_parent;
		}
		n_parent->parent = parent;
		parent = n_parent;
	}

	bool has_red_child()
	{
		return (left != NULL and left->color == Red) ||
		       (right != NULL and right->color == Red);
	}
};

class RBTree {
	Node *root;

	void left_rotate(Node *x)
	{
		Node *n_parent = x->right;

		if (x == root)
			root = n_parent;

		x->move_node_down(n_parent);

		x->right = n_parent->left;

		if (n_parent->left != NULL)
			n_parent->left->parent = x;

		n_parent->left = x;
	}

	void right_rotate(Node *x)
	{
		Node *n_parent = x->left;

		if (x == root)
			root = n_parent;

		x->move_node_down(n_parent);

		x->left = n_parent->right;

		if (n_parent->right != NULL)
			n_parent->right->parent = x;

		n_parent->right = x;
	}

	void swap_colors(Node *x1, Node *x2)
	{
		Color temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void swap_values(Node *u, Node *v)
	{
		int temp;
		temp = u->key;
		u->key = v->key;
		v->key = temp;
	}

	void fix_rr_violation(Node *x)
	{
		if (x == root)
		{
			x->color = Black;
			return;
		}

		Node *parent = x->parent, *grandparent = parent->parent,
		      *get_uncle = x->get_uncle();

		if (parent->color != Black)
		{
			if (get_uncle != NULL && get_uncle->color == Red)
			{
				parent->color = Black;
				get_uncle->color = Black;
				grandparent->color = Red;
				fix_rr_violation(grandparent);
			}
			else
			{
				if (parent->is_on_left())
				{
					if (x->is_on_left())
						swap_colors(parent, grandparent);
					else
					{
						left_rotate(parent);
						swap_colors(x, grandparent);
					}
					right_rotate(grandparent);
				}
				else
				{
					if (x->is_on_left())
					{
						right_rotate(parent);
						swap_colors(x, grandparent);
					}
					else
						swap_colors(parent, grandparent);

					left_rotate(grandparent);
				}
			}
		}
	}

	Node *get_successor(Node *x)
	{
		Node *temp = x;

		while (temp->left != NULL)
			temp = temp->left;

		return temp;
	}

	Node *BST_replace(Node *x) {
		if (x->left != NULL and x->right != NULL)
			return get_successor(x->right);

		if (x->left == NULL and x->right == NULL)
			return NULL;

		if (x->left != NULL)
			return x->left;
		else
			return x->right;
	}

	void delete_node(Node *v) {
		Node *u = BST_replace(v);

		bool uv_black = ((u == NULL || u->color == Black) and (v->color == Black));
		Node *parent = v->parent;

		if (u == NULL)
		{
			if (v == root)
				root = NULL;
			else
			{
				if (uv_black)
					fix_double_black(v);
				else if (v->get_sibling() != NULL)
					v->get_sibling()->color = Red;

				if (v->is_on_left())
					parent->left = NULL;
				else
					parent->right = NULL;
			}
			delete v;
			return;
		}

		if (v->left == NULL || v->right == NULL)
		{
			if (v == root)
			{
				v->key = u->key;
				v->left = v->right = NULL;
				delete u;
			}
			else
			{
				if (v->is_on_left())
					parent->left = u;
				else
					parent->right = u;
				delete v;
				u->parent = parent;
				if (uv_black)
					fix_double_black(u);
				else
					u->color = Black;
			}
			return;
		}

		swap_values(u, v);
		delete_node(u);
	}

	void fix_double_black(Node *x)
	{
		if (x == root)
			return;

		Node *get_sibling = x->get_sibling(), *parent = x->parent;
		if (get_sibling == NULL)
			fix_double_black(parent);
		else
		{
			if (get_sibling->color == Red)
			{
				parent->color = Red;
				get_sibling->color = Black;
				if (get_sibling->is_on_left())
					right_rotate(parent);
				else
					left_rotate(parent);
				fix_double_black(x);
			}
			else
			{
				if (get_sibling->has_red_child())
				{
					if (get_sibling->left != NULL and get_sibling->left->color == Red)
					{
						if (get_sibling->is_on_left())
						{
							get_sibling->left->color = get_sibling->color;
							get_sibling->color = parent->color;
							right_rotate(parent);
						}
						else
						{
							get_sibling->left->color = parent->color;
							right_rotate(get_sibling);
							left_rotate(parent);
						}
					}
					else
					{
						if (get_sibling->is_on_left())
						{
							get_sibling->right->color = parent->color;
							left_rotate(get_sibling);
							right_rotate(parent);
						}
						else
						{
							get_sibling->right->color = get_sibling->color;
							get_sibling->color = parent->color;
							left_rotate(parent);
						}
					}
					parent->color = Black;
				}
				else
				{
					get_sibling->color = Red;
					if (parent->color == Black)
						fix_double_black(parent);
					else
						parent->color = Black;
				}
			}
		}
	}

	void levelorder(Node *x) {
		if (x == NULL)
			return;

		queue<Node *> q;
		Node *curr;

		q.push(x);

		while (!q.empty())
		{
			curr = q.front();
			q.pop();

			cout << curr->key << " ";

			if (curr->left != NULL)
				q.push(curr->left);
			if (curr->right != NULL)
				q.push(curr->right);
		}
	}

	void inorder(Node *x)
	{
		if (x == NULL)
			return;
		inorder(x->left);
		cout << x->key << " ";
		inorder(x->right);
	}

public:
	RBTree()
	{
		root = NULL;
	}

	Node *getRoot()
	{
		return root;
	}

	Node *BST_search(int n)
	{
		Node *temp = root;
		while (temp != NULL)
		{
			if (n < temp->key)
			{
				if (temp->left == NULL)
					break;
				else
					temp = temp->left;
			}
			else if (n == temp->key)
				break;
			else
			{
				if (temp->right == NULL)
					break;
				else
					temp = temp->right;
			}
		}

		return temp;
	}

	void insert(int n)
	{
		Node *new_node = new Node(n);
		if (root == NULL)
		{
			new_node->color = Black;
			root = new_node;
		}
		else
		{
			Node *temp = BST_search(n);

			if (temp->key == n)
				return;

			new_node->parent = temp;

			if (n < temp->key)
				temp->left = new_node;
			else
				temp->right = new_node;

			fix_rr_violation(new_node);
		}
	}

	void del(int n)
	{
		if (root == NULL)
			return;

		Node *v = BST_search(n), *u;

		if (v->key != n) {
			cout << "No node found to delete with key: " << n << endl;
			return;
		}

		delete_node(v);
	}

	void search(int n)
	{
		Node *temp = BST_search(n);

		if (temp->key == n)
			cout << "Key: " << n << " found" << endl;
		else
			cout << "Key: " << n << " not found" << endl;
	}

	void print_in_order()
	{
		cout << "Inorder: " << endl;
		if (root == NULL)
			cout << "Tree is empty" << endl;
		else
			inorder(root);
		cout << endl;
	}

	void print_level_order()
	{
		cout << "Level order: " << endl;
		if (root == NULL)
			cout << "Tree is empty" << endl;
		else
			levelorder(root);
		cout << endl;
	}
};

int main()
{
	RBTree tree;

	tree.insert(25);
	tree.insert(10);
	tree.insert(19);
	tree.insert(32);
	tree.insert(55);
	tree.insert(21);
	tree.insert(29);
	tree.insert(15);

	tree.print_in_order();
	tree.print_level_order();

	cout << endl << "Deleting 55, 15" << endl;

	tree.del(55);
	tree.del(15);

	tree.print_in_order();
	tree.print_level_order();

	cout << endl;
	tree.search(19);
	return 0;
}

// B Tree
#include <bits/stdc++.h>
using namespace std;
#define int long long

class Node
{
	int *keys;
	int t;
	Node **children;
	int n;
	bool is_leaf;

public:
	Node(int _t, bool _is_leaf)
	{
		t = _t;
		is_leaf = _is_leaf;
		keys = new int[2 * t - 1];
		children = new Node *[2 * t];
		n = 0;
	}

	void traverse()
	{
		int i;
		for (i = 0; i < n; i++)
		{
			if (is_leaf == false)
				children[i]->traverse();
			cout << " " << keys[i];
		}
		if (is_leaf == false)
			children[i]->traverse();
	}

	Node *search(int k)
	{
		int i = 0;
		while (i < n && k > keys[i])
			i++;
		if (keys[i] == k)
			return this;
		if (is_leaf == true)
			return NULL;
		return children[i]->search(k);
	}

	int find_key(int k)
	{
		int idx = 0;
		while (idx < n && keys[idx] < k)
			++idx;
		return idx;
	}

	void insertNonFull(int k)
	{
		int i = n - 1;
		if (is_leaf == true)
		{
			while (i >= 0 && keys[i] > k)
			{
				keys[i + 1] = keys[i];
				i--;
			}
			keys[i + 1] = k;
			n = n + 1;
		}
		else
		{
			while (i >= 0 && keys[i] > k)
				i--;
			if (children[i + 1]->n == 2 * t - 1)
			{
				split_child(i + 1, children[i + 1]);
				if (keys[i + 1] < k)
					i++;
			}
			children[i + 1]->insertNonFull(k);
		}
	}

	void split_child(int i, Node *y)
	{
		Node *z = new Node(y->t, y->is_leaf);
		z->n = t - 1;
		for (int j = 0; j < t - 1; j++)
			z->keys[j] = y->keys[j + t];
		if (y->is_leaf == false)
			for (int j = 0; j < t; j++)
				z->children[j] = y->children[j + t];
		y->n = t - 1;
		for (int j = n; j >= i + 1; j--)
			children[j + 1] = children[j];
		children[i + 1] = z;
		for (int j = n - 1; j >= i; j--)
			keys[j + 1] = keys[j];
		keys[i] = y->keys[t - 1];
		n = n + 1;
	}

	void remove(int k)
	{
		int idx = find_key(k);
		if (idx < n && keys[idx] == k)
		{
			if (is_leaf)
				remove_from_leaf(idx);
			else
				remove_from_non_leaf(idx);
		}
		else
		{
			if (is_leaf)
			{
				cout << "The key " << k << " does not exist in the tree\n";
				return;
			}
			bool flag = ( (idx == n) ? true : false );
			if (children[idx]->n < t)
				fill(idx);
			if (flag && idx > n)
				children[idx - 1]->remove(k);
			else
				children[idx]->remove(k);
		}
		return;
	}

	void remove_from_leaf(int idx)
	{
		for (int i = idx + 1; i < n; ++i)
			keys[i - 1] = keys[i];
		n--;
		return;
	}

	void remove_from_non_leaf(int idx)
	{
		int k = keys[idx];
		if (children[idx]->n >= t)
		{
			int pred = get_pred(idx);
			keys[idx] = pred;
			children[idx]->remove(pred);
		}
		else if (children[idx + 1]->n >= t)
		{
			int succ = get_succ(idx);
			keys[idx] = succ;
			children[idx + 1]->remove(succ);
		}
		else
		{
			merge(idx);
			children[idx]->remove(k);
		}
		return;
	}

	int get_pred(int idx)
	{
		Node *cur = children[idx];
		while (!cur->is_leaf)
			cur = cur->children[cur->n];
		return cur->keys[cur->n - 1];
	}

	int get_succ(int idx)
	{
		Node *cur = children[idx + 1];
		while (!cur->is_leaf)
			cur = cur->children[0];
		return cur->keys[0];
	}

	void fill(int idx)
	{
		if (idx != 0 && children[idx - 1]->n >= t)
			borrow_from_prev(idx);
		else if (idx != n && children[idx + 1]->n >= t)
			borrow_from_next(idx);
		else
		{
			if (idx != n)
				merge(idx);
			else
				merge(idx - 1);
		}
		return;
	}

	void borrow_from_prev(int idx)
	{
		Node *child = children[idx];
		Node *sibling = children[idx - 1];
		for (int i = child->n - 1; i >= 0; --i)
			child->keys[i + 1] = child->keys[i];
		if (!child->is_leaf)
		{
			for (int i = child->n; i >= 0; --i)
				child->children[i + 1] = child->children[i];
		}
		child->keys[0] = keys[idx - 1];
		if (!child->is_leaf)
			child->children[0] = sibling->children[sibling->n];
		keys[idx - 1] = sibling->keys[sibling->n - 1];
		child->n += 1;
		sibling->n -= 1;
		return;
	}

	void borrow_from_next(int idx)
	{
		Node *child = children[idx];
		Node *sibling = children[idx + 1];
		child->keys[(child->n)] = keys[idx];
		if (!(child->is_leaf))
			child->children[(child->n) + 1] = sibling->children[0];
		keys[idx] = sibling->keys[0];
		for (int i = 1; i < sibling->n; ++i)
			sibling->keys[i - 1] = sibling->keys[i];
		if (!sibling->is_leaf)
			for (int i = 1; i <= sibling->n; ++i)
				sibling->children[i - 1] = sibling->children[i];
		child->n += 1;
		sibling->n -= 1;
		return;
	}

	void merge(int idx)
	{
		Node *child = children[idx];
		Node *sibling = children[idx + 1];
		child->keys[t - 1] = keys[idx];
		for (int i = 0; i < sibling->n; ++i)
			child->keys[i + t] = sibling->keys[i];
		if (!child->is_leaf)
			for (int i = 0; i <= sibling->n; ++i)
				child->children[i + t] = sibling->children[i];
		for (int i = idx + 1; i < n; ++i)
			keys[i - 1] = keys[i];
		for (int i = idx + 2; i <= n; ++i)
			children[i - 1] = children[i];
		child->n += sibling->n + 1;
		n--;
		delete(sibling);
		return;
	}

	friend class BTree;
};

class BTree
{
	Node *root;
	int t;

public:
	BTree(int _t)
	{
		root = NULL;
		t = _t;
	}

	void traverse()
	{
		if (root != NULL)
			root->traverse();
	}

	void search(int k)
	{
		if (root == NULL || root->search(k) == NULL)
			cout << "The key " << k << " does not exist in the tree\n";
		else
			cout << "The key " << k << " exist in the tree\n";
	}

	void insert(int k)
	{
		if (root == NULL)
		{
			root = new Node(t, true);
			root->keys[0] = k;
			root->n = 1;
		}
		else
		{
			if (root->n == 2 * t - 1)
			{
				Node *s = new Node(t, false);
				s->children[0] = root;
				s->split_child(0, root);
				int i = 0;
				if (s->keys[0] < k)
					i++;
				s->children[i]->insertNonFull(k);
				root = s;
			}
			else
				root->insertNonFull(k);
		}
	}

	void remove(int k)
	{
		if (!root)
		{
			cout << "The tree is empty\n";
			return;
		}
		root->remove(k);
		if (root->n == 0)
		{
			Node *tmp = root;
			if (root->is_leaf)
				root = NULL;
			else
				root = root->children[0];
			delete tmp;
		}
		return;
	}
};

int32_t main()
{
	vector<int> v = {10, 15, 18, 3, 9, 11, 19, 21, 35, 45, 43, 55, 2, 1, 14};

	BTree t(v[0]);
	for (int i = 1; i < v.size(); i++)
		t.insert(v[i]);
	cout << "Traversal of tree constructed is\n";
	t.traverse();
	cout << endl;

	t.search(2);
	t.search(6);

	t.remove(2);
	cout << "Traversal of tree after removing 2\n";
	t.traverse();

	return 0;
}

// Binomial Heap
#include<bits/stdc++.h>
using namespace std;
#define int long long

struct Node
{
	int data, degree;
	Node *child, *sibling, *parent;
};

Node* new_node(int key)
{
	Node *temp = new Node;
	temp->data = key;
	temp->degree = 0;
	temp->child = temp->parent = temp->sibling = NULL;
	return temp;
}

Node* merge_binomial_trees(Node *b1, Node *b2)
{
	if (b1->data > b2->data)
		swap(b1, b2);
	b2->parent = b1;
	b2->sibling = b1->child;
	b1->child = b2;
	b1->degree++;
	return b1;
}

list<Node*> union_bionomial_heap(list<Node*> l1, list<Node*> l2)
{
	list<Node*> _new;
	list<Node*>::iterator it = l1.begin();
	list<Node*>::iterator ot = l2.begin();
	while (it != l1.end() && ot != l2.end())
	{
		if ((*it)->degree <= (*ot)->degree)
		{
			_new.push_back(*it);
			it++;
		}
		else
		{
			_new.push_back(*ot);
			ot++;
		}
	}
	while (it != l1.end())
	{
		_new.push_back(*it);
		it++;
	}

	while (ot != l2.end())
	{
		_new.push_back(*ot);
		ot++;
	}
	return _new;
}

list<Node*> adjust(list<Node*> _heap)
{
	if (_heap.size() <= 1)
		return _heap;
	list<Node*> new_heap;
	list<Node*>::iterator it1, it2, it3;
	it1 = it2 = it3 = _heap.begin();
	if (_heap.size() == 2)
	{
		it2 = it1;
		it2++;
		it3 = _heap.end();
	}
	else
	{
		it2++;
		it3 = it2;
		it3++;
	}
	while (it1 != _heap.end())
	{
		if (it2 == _heap.end())
			it1++;
		else if ((*it1)->degree < (*it2)->degree)
		{
			it1++;
			it2++;
			if (it3 != _heap.end())
				it3++;
		}
		else if (it3 != _heap.end() && (*it1)->degree == (*it2)->degree && (*it1)->degree == (*it3)->degree)
		{
			it1++;
			it2++;
			it3++;
		}
		else if ((*it1)->degree == (*it2)->degree)
		{
			Node *temp;
			*it1 = merge_binomial_trees(*it1, *it2);
			it2 = _heap.erase(it2);
			if (it3 != _heap.end())
				it3++;
		}
	}
	return _heap;
}

list<Node*> insert_a_tree_in_heap(list<Node*> _heap, Node *tree)
{
	list<Node*> temp;
	temp.push_back(tree);
	temp = union_bionomial_heap(_heap, temp);
	return adjust(temp);
}

list<Node*> remove_min_from_tree_return_b_heap(Node *tree)
{
	list<Node*> heap;
	Node *temp = tree->child;
	Node *lo;
	while (temp)
	{
		lo = temp;
		temp = temp->sibling;
		lo->sibling = NULL;
		heap.push_front(lo);
	}
	return heap;
}

list<Node*> insert(list<Node*> _head, int key)
{
	Node *temp = new_node(key);
	return insert_a_tree_in_heap(_head, temp);
}

Node* get_min(list<Node*> _heap)
{
	list<Node*>::iterator it = _heap.begin();
	Node *temp = *it;
	while (it != _heap.end())
	{
		if ((*it)->data < temp->data)
			temp = *it;
		it++;
	}
	return temp;
}

list<Node*> extract_min(list<Node*> _heap)
{
	list<Node*> new_heap, lo;
	Node *temp;
	temp = get_min(_heap);
	list<Node*>::iterator it;
	it = _heap.begin();
	while (it != _heap.end())
	{
		if (*it != temp)
			new_heap.push_back(*it);
		it++;
	}
	lo = remove_min_from_tree_return_b_heap(temp);
	new_heap = union_bionomial_heap(new_heap, lo);
	new_heap = adjust(new_heap);
	return new_heap;
}

void print_tree(Node *h)
{
	while (h)
	{
		cout << h->data << " ";
		print_tree(h->child);
		h = h->sibling;
	}
}

void print_heap(list<Node*> _heap)
{
	list<Node*> ::iterator it;
	it = _heap.begin();
	while (it != _heap.end())
	{
		print_tree(*it);
		it++;
	}
}


int32_t main()
{
	list<Node*> _heap;

	vector<int> v = {21, 10, 1, 12, 25, 13, 6, 8, 14, 29, 11, 17, 38, 27};
	for (int data : v)
		_heap = insert(_heap, data);
	cout << "Heap elements after insertion:\n";
	print_heap(_heap);

	Node *temp = get_min(_heap);
	cout << "\n\nMinimum element of heap is " << temp->data << "\n\n";

	_heap = extract_min(_heap);
	cout << "Heap elements after deletion of minimum element:\n";
	print_heap(_heap);

	return 0;
}

// Fibonacci Heap
#include <bits/stdc++.h>
using namespace std;
#define int long long

struct node
{
	node* parent;
	node* child;
	node* left;
	node* right;
	int key;
	int degree;
	char mark;
	char c;
};

struct node* mini = NULL;

int no_of_nodes = 0;

void insertion(int val)
{
	struct node* new_node = new node();
	new_node->key = val;
	new_node->degree = 0;
	new_node->mark = 'W';
	new_node->c = 'N';
	new_node->parent = NULL;
	new_node->child = NULL;
	new_node->left = new_node;
	new_node->right = new_node;
	if (mini != NULL)
	{
		(mini->left)->right = new_node;
		new_node->right = mini;
		new_node->left = mini->left;
		mini->left = new_node;
		if (new_node->key < mini->key)
			mini = new_node;
	}
	else
		mini = new_node;
	no_of_nodes++;
}

void fibonnaci_link(struct node* ptr2, struct node* ptr1)
{
	(ptr2->left)->right = ptr2->right;
	(ptr2->right)->left = ptr2->left;
	if (ptr1->right == ptr1)
		mini = ptr1;
	ptr2->left = ptr2;
	ptr2->right = ptr2;
	ptr2->parent = ptr1;
	if (ptr1->child == NULL)
		ptr1->child = ptr2;
	ptr2->right = ptr1->child;
	ptr2->left = (ptr1->child)->left;
	((ptr1->child)->left)->right = ptr2;
	(ptr1->child)->left = ptr2;
	if (ptr2->key < (ptr1->child)->key)
		ptr1->child = ptr2;
	ptr1->degree++;
}

void consolidate()
{
	int temp1;
	float temp2 = (log(no_of_nodes)) / (log(2));
	int temp3 = temp2;
	struct node* arr[temp3 + 1];
	for (int i = 0; i <= temp3; i++)
		arr[i] = NULL;
	node* ptr1 = mini;
	node* ptr2;
	node* ptr3;
	node* ptr4 = ptr1;
	do
	{
		ptr4 = ptr4->right;
		temp1 = ptr1->degree;
		while (arr[temp1] != NULL)
		{
			ptr2 = arr[temp1];
			if (ptr1->key > ptr2->key)
			{
				ptr3 = ptr1;
				ptr1 = ptr2;
				ptr2 = ptr3;
			}
			if (ptr2 == mini)
				mini = ptr1;
			fibonnaci_link(ptr2, ptr1);
			if (ptr1->right == ptr1)
				mini = ptr1;
			arr[temp1] = NULL;
			temp1++;
		}
		arr[temp1] = ptr1;
		ptr1 = ptr1->right;
	}
	while (ptr1 != mini);
	mini = NULL;
	for (int j = 0; j <= temp3; j++)
	{
		if (arr[j] != NULL)
		{
			arr[j]->left = arr[j];
			arr[j]->right = arr[j];
			if (mini != NULL)
			{
				(mini->left)->right = arr[j];
				arr[j]->right = mini;
				arr[j]->left = mini->left;
				mini->left = arr[j];
				if (arr[j]->key < mini->key)
					mini = arr[j];
			}
			else
				mini = arr[j];
			if (mini == NULL)
				mini = arr[j];
			else if (arr[j]->key < mini->key)
				mini = arr[j];
		}
	}
}

void extract_min()
{
	if (mini == NULL)
		cout << "The heap is empty" << endl;
	else
	{
		node* temp = mini;
		node* pntr;
		pntr = temp;
		node* x = NULL;
		if (temp->child != NULL)
		{
			x = temp->child;
			do
			{
				pntr = x->right;
				(mini->left)->right = x;
				x->right = mini;
				x->left = mini->left;
				mini->left = x;
				if (x->key < mini->key)
					mini = x;
				x->parent = NULL;
				x = pntr;
			}
			while (pntr != temp->child);
		}
		(temp->left)->right = temp->right;
		(temp->right)->left = temp->left;
		mini = temp->right;
		if (temp == temp->right && temp->child == NULL)
			mini = NULL;
		else
		{
			mini = temp->right;
			consolidate();
		}
		no_of_nodes--;
	}
}

void cut(struct node* found, struct node* temp)
{
	if (found == found->right)
		temp->child = NULL;
	(found->left)->right = found->right;
	(found->right)->left = found->left;
	if (found == temp->child)
		temp->child = found->right;
	temp->degree = temp->degree - 1;
	found->right = found;
	found->left = found;
	(mini->left)->right = found;
	found->right = mini;
	found->left = mini->left;
	mini->left = found;
	found->parent = NULL;
	found->mark = 'B';
}

void cascase_cut(struct node* temp)
{
	node* ptr = temp->parent;
	if (ptr != NULL)
	{
		if (temp->mark == 'W')
			temp->mark = 'B';
		else
		{
			cut(temp, ptr);
			cascase_cut(ptr);
		}
	}
}

void decrease_key(struct node* found, int val)
{
	if (mini == NULL)
		cout << "The Heap is Empty" << endl;
	if (found == NULL)
		cout << "Node not found in the Heap" << endl;
	found->key = val;
	struct node* temp = found->parent;
	if (temp != NULL && found->key < temp->key)
	{
		cut(found, temp);
		cascase_cut(temp);
	}
	if (found->key < mini->key)
		mini = found;
}

void find(struct node* mini, int old_val, int val)
{
	struct node* found = NULL;
	node* temp = mini;
	temp->c = 'Y';
	node* found_ptr = NULL;
	if (temp->key == old_val)
	{
		found_ptr = temp;
		temp->c = 'N';
		found = found_ptr;
		decrease_key(found, val);
	}
	if (found_ptr == NULL)
	{
		if (temp->child != NULL)
			find(temp->child, old_val, val);
		if ((temp->right)->c != 'Y')
			find(temp->right, old_val, val);
	}
	temp->c = 'N';
	found = found_ptr;
}

void deletion(int val)
{
	if (mini == NULL)
		cout << "The heap is empty" << endl;
	else
	{
		find(mini, val, 0);
		extract_min();
		cout << "Key Deleted" << endl;
	}
}

void display()
{
	node* ptr = mini;
	if (ptr == NULL)
		cout << "The Heap is Empty" << endl;
	else
	{
		cout << "The root nodes of Heap are: " << endl;
		do
		{
			cout << ptr->key;
			ptr = ptr->right;
			if (ptr != mini)
				cout << "-->";
		}
		while (ptr != mini && ptr->right != NULL);
		cout << endl << "The heap has " << no_of_nodes << " nodes" << endl << endl;
	}
}

void find_min()
{
	cout << "Min of the heap is: " << mini->key << endl;
}

int32_t main()
{
	vector<int> v = {23, 30, 24, 26, 46, 35, 17, 3, 18, 52, 41, 39, 44, 21, 7};
	cout << "Inserting elements in heap" << endl;
	for (int data : v)
		insertion(data);
	display();

	cout << "Extracting min" << endl;
	extract_min();
	display();

	cout << "Decrease value of 39 to 2" << endl;
	find(mini, 39, 2);
	display();

	cout << "Delete the node 2" << endl;
	deletion(2);
	display();

	return 0;
}

// Simple_Hashing
#include<bits/stdc++.h>
using namespace std;

class HashTable
{
	int table_size;
	list<int> *table;

public:
	HashTable(int size)
	{
		this->table_size = size;
		table = new list<int>[table_size];
	}

	void insert_item(int key)
	{
		int index = hash_function(key);
		table[index].push_back(key);
	}

	void delete_item(int key)
	{
		int index = hash_function(key);
		list <int> :: iterator i;
		for (i = table[index].begin(); i != table[index].end(); i++)
			if (*i == key)
				break;
		if (i != table[index].end())
			table[index].erase(i);
	}

	int hash_function(int key) {
		return (key % table_size);
	}

	void display_hash_table()
	{
		for (int i = 0; i < table_size; i++)
		{
			cout << i;
			for (auto x : table[i])
				cout << " --> " << x;
			cout << endl;
		}
	}
};

int main()
{
	vector<int> v = {15, 11, 27, 8, 12};
	int n = v.size();
	HashTable ht(7);
	for (int i = 0; i < n; i++)
		ht.insert_item(v[i]);
	ht.delete_item(12);
	ht.display_hash_table();
	return 0;
}

// Double_Hashing
#include <bits/stdc++.h>
using namespace std;
#define MAX_SIZE 10000001ll

class DoubleHash
{
	int table_size, keys_present, prime;
	vector<int> hash_table;
	bitset<MAX_SIZE> is_prime;

	void set_sieve()
	{
		is_prime[0] = is_prime[1] = 1;
		for (long long i = 2; i * i <= MAX_SIZE; i++)
			if (is_prime[i] == 0)
				for (long long j = i * i; j <= MAX_SIZE; j += i)
					is_prime[j] = 1;

	}

	int inline hash1(int value)
	{
		return value % table_size;
	}

	int inline hash2(int value)
	{
		return prime - (value % prime);
	}

	bool inline is_full()
	{
		return (table_size == keys_present);
	}

public:
	DoubleHash(int n)
	{
		set_sieve();
		table_size = n;
		prime = table_size - 1;
		while (is_prime[prime] == 1)
			prime--;
		keys_present = 0;
		for (int i = 0; i < table_size; i++)
			hash_table.push_back(-1);
	}

	void print_prime(long long n)
	{
		for (long long i = 0; i <= n; i++)
			if (is_prime[i] == 0)
				cout << i << ", ";
		cout << endl;
	}

	void insert(int value)
	{
		if (value == -1 || value == -2)
		{
			cout << ("ERROR : -1 and -2 can't be inserted in the table\n");
		}
		if (is_full())
		{
			cout << ("ERROR : Hash Table Full\n");
			return;
		}
		int probe = hash1(value), offset = hash2(value);
		while (hash_table[probe] != -1)
		{
			if (-2 == hash_table[probe])
				break;
			probe = (probe + offset) % table_size;
		}
		hash_table[probe] = value;
		keys_present += 1;
	}

	void erase(int value)
	{
		if (!search(value))
			return;
		int probe = hash1(value), offset = hash2(value);
		while (hash_table[probe] != -1)
			if (hash_table[probe] == value)
			{
				hash_table[probe] = -2;
				keys_present--;
				return;
			}
			else
				probe = (probe + offset) % table_size;

	}

	bool search(int value)
	{
		int probe = hash1(value), offset = hash2(value), initialPos = probe;
		bool first_itr = true;
		while (1)
		{
			if (hash_table[probe] == -1)
				break;
			else if (hash_table[probe] == value)
				return true;
			else if (probe == initialPos && !first_itr)
				return false;
			else
				probe = ((probe + offset) % table_size);
			first_itr = false;
		}
		return false;
	}

	void print()
	{
		for (int i = 0; i < table_size; i++)
			cout << hash_table[i] << ", ";
		cout << "\n";
	}

};

int main() {
	DoubleHash dh(13);

	vector<int> insertions = {115, 12, 87, 66, 123};
	for (int i = 0; i < insertions.size(); i++)
		dh.insert(insertions[i]);
	cout << "Status of hash table after initial insertions : "; dh.print();

	vector<int> queries = {1, 12, 2, 3, 69, 88, 115};
	cout << "\n" << "Search operation after insertion : \n";
	for (int i = 0; i < queries.size(); i++)
		if (dh.search(queries[i]))
			cout << queries[i] << " present\n";
	cout << endl;

	vector<int> deletions = {123, 87, 66};
	for (int i = 0; i < deletions.size(); i++)
		dh.erase(deletions[i]);
	cout << "Status of hash table after deleting elements : "; dh.print();

	return 0;
}

// Rabin_Karp.cpp
#include <bits/stdc++.h>
using namespace std;

#define d 256

void search(string pattern, string text, int q)
{
	int M = pattern.length(), N = text.length();
	int i, j;
	int p = 0, t = 0, h = 1;
	for (i = 0; i < M - 1; i++)
		h = (h * d) % q;
	for (i = 0; i < M; i++)
	{
		p = (d * p + pattern[i]) % q;
		t = (d * t + text[i]) % q;
	}
	bool flag = false;
	for (i = 0; i <= N - M; i++)
	{
		if (p == t)
		{
			for (j = 0; j < M; j++)
				if (text[i + j] != pattern[j])
					break;
			if (j == M)
			{
				cout << "Pattern found at index " << i << endl;
				flag = true;
			}
		}
		if (i < N - M)
		{
			t = (d * (t - text[i] * h) + text[i + M]) % q;
			if (t < 0)
				t = (t + q);
		}
	}
	if (!flag)
		cout << "Pattern does not exists in the text";
}

int main()
{
	string text = "My name is Rahul Agarwal";
	string pattern = "Rahul";
	int q = INT_MAX;
	search(pattern, text, q);
	return 0;
}

// KMP
#include <bits/stdc++.h>
using namespace std;

void compute_LPS_array(string pattern, int M, vector<int>& lps)
{
	int len = 0;
	lps[0] = 0;
	int i = 1;
	while (i < M)
	{
		if (pattern[i] == pattern[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if (len != 0)
				len = lps[len - 1];
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

void search(string pattern, string text)
{
	int M = pattern.length(), N = text.length();
	vector<int> lps(M);
	compute_LPS_array(pattern, M, lps);
	int i = 0, j = 0;
	bool flag = false;
	while ((N - i) >= (M - j))
	{
		if (pattern[j] == text[i])
		{
			j++;
			i++;
		}
		if (j == M)
		{
			cout << "Pattern found at index " << i - j << endl;
			flag = true;
			j = lps[j - 1];
		}
		else if (i < N && pattern[j] != text[i])
		{
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
	if (!flag)
		cout << "Pattern does not exists in the text";
}

int main()
{
	string text = "My name is Rahul Agarwal";
	string pattern = "Rahul";
	search(pattern, text);
	return 0;
}

// Push_Relabel
#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
	int flow, capacity;
	int u, v;

	Edge(int flow, int capacity, int u, int v)
	{
		this->flow = flow;
		this->capacity = capacity;
		this->u = u;
		this->v = v;
	}
};

class Vertex
{
public:
	int height, excess_flow;

	Vertex(int height, int excess_flow)
	{
		this->height = height;
		this->excess_flow = excess_flow;
	}
};

class Graph
{
	int vertices;
	vector<Vertex> vertex_list;
	vector<Edge> edge_list;

	bool push(int u)
	{
		for (int i = 0; i < edge_list.size(); i++)
		{
			if (edge_list[i].u == u)
			{
				if (edge_list[i].flow == edge_list[i].capacity)
					continue;
				if (vertex_list[u].height > vertex_list[edge_list[i].v].height)
				{
					int flow = min(edge_list[i].capacity - edge_list[i].flow, vertex_list[u].excess_flow);
					vertex_list[u].excess_flow -= flow;
					vertex_list[edge_list[i].v].excess_flow += flow;
					edge_list[i].flow += flow;
					update_reverse_edge_flow(i, flow);
					return true;
				}
			}
		}
		return false;
	}

	void relabel(int u)
	{
		int min_height = INT_MAX;
		for (int i = 0; i < edge_list.size(); i++)
		{
			if (edge_list[i].u == u)
			{
				if (edge_list[i].flow == edge_list[i].capacity)
					continue;
				if (vertex_list[edge_list[i].v].height < min_height)
				{
					min_height = vertex_list[edge_list[i].v].height;
					vertex_list[u].height = min_height + 1;
				}
			}
		}
	}

	void preflow(int s)
	{
		vertex_list[s].height = vertex_list.size();
		for (int i = 0; i < edge_list.size(); i++)
		{
			if (edge_list[i].u == s)
			{
				edge_list[i].flow = edge_list[i].capacity;
				vertex_list[edge_list[i].v].excess_flow += edge_list[i].flow;
				edge_list.push_back(Edge(-edge_list[i].flow, 0, edge_list[i].v, s));
			}
		}
	}

	void update_reverse_edge_flow(int i, int flow)
	{
		int u = edge_list[i].v, v = edge_list[i].u;
		for (int j = 0; j < edge_list.size(); j++)
		{
			if (edge_list[j].v == v && edge_list[j].u == u)
			{
				edge_list[j].flow -= flow;
				return;
			}
		}
		Edge e = Edge(0, flow, u, v);
		edge_list.push_back(e);
	}

	int over_flow_vertex(vector<Vertex>& vertex_list)
	{
		for (int i = 1; i < vertex_list.size() - 1; i++)
			if (vertex_list[i].excess_flow > 0)
				return i;
		return -1;
	}


public:
	Graph(int vertices)
	{
		this->vertices = vertices;
		for (int i = 0; i < vertices; i++)
			vertex_list.push_back(Vertex(0, 0));
	}

	void add_edge(int u, int v, int capacity)
	{
		edge_list.push_back(Edge(0, capacity, u, v));
	}

	get_max_flow(int s, int t)
	{
		preflow(s);
		while (over_flow_vertex(vertex_list) != -1)
		{
			int u = over_flow_vertex(vertex_list);
			if (!push(u))
				relabel(u);
		}
		return vertex_list.back().excess_flow;
	}

};

int main()
{
	int vertices = 6;
	Graph g(vertices);

	g.add_edge(0, 1, 16);
	g.add_edge(0, 2, 13);
	g.add_edge(1, 2, 10);
	g.add_edge(2, 1, 4);
	g.add_edge(1, 3, 12);
	g.add_edge(2, 4, 14);
	g.add_edge(3, 2, 9);
	g.add_edge(3, 5, 20);
	g.add_edge(4, 3, 7);
	g.add_edge(4, 5, 4);

	int s = 0, t = 5;

	cout << "Maximum flow is " << g.get_max_flow(s, t);
	return 0;
}

// Edmonds_Karp
#include <bits/stdc++.h>
using namespace std;

bool bfs(vector<vector<int>>& residual_graph, int s, int t, vector<int>& parent, int V)
{
	vector<bool> visited(V, false);
	queue<int> q;
	q.push(s);
	visited[s] = true;
	parent[s] = -1;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int v = 0; v < V; v++)
		{
			if (visited[v] == false && residual_graph[u][v] > 0)
			{
				if (v == t)
				{
					parent[v] = u;
					return true;
				}
				q.push(v);
				parent[v] = u;
				visited[v] = true;
			}
		}
	}
	return false;
}

int edmonds_karp(vector<vector<int>>& graph, int s, int t, int V)
{
	int u, v;
	vector<vector<int>> residual_graph(V, vector<int>(V));
	for (u = 0; u < V; u++)
		for (v = 0; v < V; v++)
			residual_graph[u][v] = graph[u][v];
	vector<int> parent(V);
	int max_flow = 0;
	while (bfs(residual_graph, s, t, parent, V))
	{
		int path_flow = INT_MAX;
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			path_flow = min(path_flow, residual_graph[u][v]);
		}
		for (v = t; v != s; v = parent[v])
		{
			u = parent[v];
			residual_graph[u][v] -= path_flow;
			residual_graph[v][u] += path_flow;
		}
		max_flow += path_flow;
	}
	return max_flow;
}

int main()
{
	int V = 6;
	vector<vector<int>> graph =
	{
		{ 0, 16, 13, 0, 0, 0 },
		{ 0, 0, 10, 12, 0, 0 },
		{ 0, 4, 0, 0, 14, 0 },
		{ 0, 0, 9, 0, 0, 20 },
		{ 0, 0, 0, 7, 0, 4 },
		{ 0, 0, 0, 0, 0, 0 }
	};
	cout << "The maximum possible flow is " << edmonds_karp(graph, 0, 5, V);
	return 0;
}
