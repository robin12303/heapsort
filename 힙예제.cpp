#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>
using namespace std;

typedef struct _NODE
{ 
	int data;
	_NODE* left; _NODE* right;
	_NODE(int _data) : data(_data), left(nullptr), right(nullptr) { /*printf("Node->data = %d has been created.\n", data);*/ }
}NODE;

typedef struct _HEAP
{
	NODE* root_node;
	int size;
	_HEAP() : root_node(nullptr), size(0) {}
	

	void display(int n)
	{
		int counter = 0;  
		for (int loop = 0; loop < n; loop++)
		{
			NODE* trace = div(root_node, loop);
			cout << trace->data << " ";
		}
		cout << endl;
	}
	void delete_node(NODE* ptr)
	{
		delete ptr;
	}

	vector<int> get_list()
	{
		vector<int> list;
		for (;size > 0;)
		{  
			NODE* trace = div(root_node, size - 1); 
			int temp = trace->data;
			trace->data = root_node->data; 
			root_node->data = temp;
			list.push_back(trace->data);
			int end = (size - 1);
			NODE* dp = div(root_node, (end - 1) / 2);
			if ((size - 1) % 2 == 1)
			{
				delete dp->left;
				dp->left = nullptr;
			}
				
			else if ((size - 1) % 2 == 0)
			{
				delete dp->right;
				dp->right = nullptr;
			}
				 
			else
			{
				delete root_node;
				root_node = nullptr;
			}
				 
			make_heap(root_node, size);

			size--;  

		}  
		return list;
	}
	 
	void make_heap(NODE* cur, int n)
	{
		NODE* lp = nullptr, * rp = nullptr, *p = nullptr;

		while (true)
		{  
			lp = cur->left;
			rp = cur->right;

			if (lp == nullptr && rp == nullptr)
				break;
			p = cur;

			if (lp != nullptr && p->data < lp->data)
				p = lp;
			if (rp != nullptr && p->data < rp->data)
				p = rp;

			if (p == cur)
				break;

			int temp = cur->data;
			cur->data = p->data;
			p->data = temp;

			cur = p;
		}

	}
	void insert(int _data)
	{
		NODE* p = root_node;

		p = div(p, (size - 1) / 2);
		int parity = (size % 2);
		if (size > 0 && parity == 1)
			p->left = new NODE(_data);
		else if (size > 0 && parity == 0)
			p->right = new NODE(_data);
		else
			root_node = new NODE(_data);

		size++;

		int loop = (size-1)/2;

		for (; loop >= 0; loop--)
		{
			NODE* trace = div(root_node, loop); 
			make_heap(trace, loop);
		}

		//display(size);
		 
	}
	NODE* div(NODE* _p, int _n)
	{ 
		if (_n < 1)
			return _p; 

		_p = div(_p, (_n - 1) / 2);

		if (_n > 0 && _n % 2 == 1)
			_p = _p->left;

		else if (_n > 0 && _n % 2 == 0)
			_p = _p->right;

		return _p;
	  
	}
}HEAP;

int main()
{
	srand((unsigned int)time(NULL));
	HEAP heap; 
	int n = 15;
	vector<int> rands; 
	while (rands.size() < n)
	{
		int data = rand() % n + 1;
		rands.push_back(data);
	} 

	for (auto e : rands)
	{
		cout << e << " ";
		heap.insert(e);
	}

		
	cout << endl;
	vector<int> list = heap.get_list();

	for (auto& iter : list)
		cout << iter << " ";
	cout << endl;

	

	return 0;
}