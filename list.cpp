#include <iostream>
#include <string>
#include <initializer_list>

template <class T>
class LinkedList
{
private:
	struct node
	{
		T data;
		node *next;
	} *head = nullptr;
public:
	// Constructors and destructors
	LinkedList() = default;
	~LinkedList();
	LinkedList(const std::initializer_list<T> &il);
	LinkedList(std::istream &is);

	// Member functions
	void push (T data);
	LinkedList<T>& reverse();
	std::ostream &print(std::ostream &os);
};

template <class T>
LinkedList<T>::~LinkedList()
{
	node *cur = head, *next = nullptr;
	while (cur)
	{
		next = cur->next;
		delete cur;
		cur = next;
	}
}

template <class T>
LinkedList<T>::LinkedList(const std::initializer_list<T> &il)
{
	for (const auto &data : il)
		push (data);
}

template <class T>
LinkedList<T>::LinkedList(std::istream &is)
{
	T temp;
	while (is >> temp)
		push (temp);
}

// Push to head
template <class T>
void LinkedList<T>::push (T data)
{
	node *elem = new node;
	elem->data = data;
	elem->next = head;
	head = elem;
}

template <class T>
LinkedList<T>& LinkedList<T>::reverse()
{
	node *prev = nullptr;
	node *next = nullptr;
	if (!head) return *this;
	while (head->next)
	{
		next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}
	head->next = prev;
	return *this;
}

template <class T>
std::ostream& LinkedList<T>::print(std::ostream &os)
{
	node *iter = head;
	while (iter)
	{
		os << iter->data << " ";
		iter = iter->next;
	}
	return os;
}


int main()
{
	// Integers
	LinkedList<int> list({1, 2, 3, 4, 5});
	list.print(std::cout) << std::endl;
	list.reverse();
	list.print(std::cout) << std::endl;

	// Strings
	LinkedList<std::string> s(std::cin);
	s.print(std::cout) << std::endl;
	s.reverse().print(std::cout) << std::endl;
}
