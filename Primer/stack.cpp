#if 0
#include <iostream>

using namespace std;

template<typename T>
class Stack {
public:
	Stack<T>(int size = 10) {
		m_nSize = size;
		m_nTop = 0;
		m_Stack = new T[size];
	}
	~Stack<T>() {
		delete[] m_Stack;
		m_Stack = nullptr;
	}

	void push(const T& val) {
		if (full()) {
			expand();
		}

		m_Stack[m_nTop++] = val;
	}

	int pop() {
		if (empty()) {
			return -1;
		}
		m_nTop--;
	}

	bool full() {
		if (m_nTop == m_nSize) {
			return true;
		}
		return false;
	}

	void expand() {
		T* tmpStack = new T[m_nSize * 2];

		for (int i = 0; i < m_nSize; i++) {
			tmpStack[i] = m_Stack[i];
		}

		delete[] m_Stack;
		m_Stack = tmpStack;
		m_nSize *= 2;
	}

	bool empty() {
		if (m_nTop == 0) {
			return true;
		}
		return false;
	}

	T top() {
		if (empty()) {
			throw "Stack is empty!";
		}
		return m_Stack[m_nTop - 1];
	}

private:
	int m_nTop;
	int m_nSize;
	T* m_Stack;


};

int main()
{
	Stack<double> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);

	stack.pop();
	stack.pop();
	stack.pop();

	int tmp = stack.top();
	cout << tmp << endl;

	return 0;
}
#endif