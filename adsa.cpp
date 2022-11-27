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
