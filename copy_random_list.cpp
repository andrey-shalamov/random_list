#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cassert>

struct node
{
	int data = 0;
	node* next = nullptr;
	node* random = nullptr;
};

node* create_random_list(int n)
{
	std::vector<node*> vec(n);

	node* list = new node;
	node* cur = list;
	for (int i=0; i<n; ++i)
	{
		vec[i] = cur;
		cur->data = i;
		cur->next = i == n-1 ? nullptr : new node;
		cur = cur->next;
	}

	cur = list;
	std::srand(std::time(0));
	while(cur != nullptr)
	{
		int r = std::rand() % n;
		cur->random = vec[r];
		cur = cur->next;
	}
	return list; 
}

void print_list(node* list)
{
	node* cur = list;
	while(cur != nullptr)
	{
		printf("(%i, %i, %i)", cur->data, cur->random->data, cur->next == nullptr);
		cur = cur->next;
	}
	printf("\n");
}

node* copy_random_list(node* list)
{
	node* cur = list;
	while(cur != nullptr)
	{
		node* new_cur = new node;
		new_cur->data = cur->data;
		new_cur->next = cur->next;
		new_cur->random = cur->random;
 
		cur->next = new_cur;
		cur = new_cur->next;
	}

	node* new_list = list == nullptr ? nullptr : list->next;
	node* cur_new = new_list;
	while (cur_new != nullptr)
	{
		cur_new->random = cur_new->random->next;
		cur_new = cur_new->next == nullptr ? nullptr : cur_new->next->next;
	}

	cur = list;
	while (cur != nullptr)
	{
		auto next = cur->next;
		cur->next = next == nullptr ? nullptr : next->next;
		cur = next;
	}

	return new_list;
}

int main()
{
	const int n = 10;
	
	node* list = create_random_list(n);

	print_list(list);

	node* new_list = copy_random_list(list);

	print_list(list);
	print_list(new_list);

	node* cur = list;
	node* new_cur = new_list;
	while (cur != nullptr && new_cur != nullptr)
	{
		assert(cur != new_cur);
		printf("[%p, %p]\n", cur, new_cur);
		cur = cur->next;
		new_cur = new_cur->next;
	}

	cur = list;
	while (cur != nullptr)
	{
		auto next = cur->next;
		delete cur;
		cur = next;
	}

	print_list(new_list);

	new_cur = new_list;
	while (new_cur != nullptr)
	{
		auto next = new_cur->next;
		delete new_cur;
		new_cur = next;
	}

	return 0;
}
