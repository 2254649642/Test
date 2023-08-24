#if 0
#include <iostream>
#include <cstdlib>

using namespace std;


template<typename T>
class Allocator {
public:
	//申请指定大小内存
	T* allocate(int size = 10) {
		void* p = malloc(sizeof(T) * size);
		memset(p, 0, sizeof(T) * size);
		return (T*)p;
	}

	//释放申请内存
	void deallocate(void *p) {
		free(p);
	}

	//调用对象析构
	void destroy(T* p) {
		p->~T();
	}

	//构造指定对象
	void construct(T *p, const T& val) {
		new (p) T(val);
	}
};

template<typename T, typename Alloca = Allocator<T>>
class vector {
public:
	vector(int size = 2) {
		//_first = new T[size];
		_first = _allocate.allocate(size);
		_end = _first + size;
		_last = _first;
		this->size = 0;
		len = size;

	}

	vector(const vector<T> &rhs) {
		//_first = new T[len];
		_first = _allocate.allocate(len);

		for (int i = 0; i < size; i++) {
			//_first[i] = rhs._first[i];
			_allocate.construct(_first + i, rhs._first[i]);
		}
		_last = _first + rhs.size;
		_end = _first + rhs.len;
		len = rhs.len;
		size = rhs.size;
	}

	vector<T>& operator=(const vector<T>& rhs) {
		if (&rhs == this) {
			return *this;
		}

		//delete[] _first;
		_allocate.deallocate(_first);

		//_first = new T[len];
		_first = _allocate.allocate(rhs.len);


		for (int i = 0; i < rhs.size; i++) {
			//_first[i] = rhs._first[i];
			_allocate.construct(_first + i, rhs._first[i]);
		}
		_last = _first + rhs.size;
		_end = _first + rhs.len;
		len = rhs.len;
		size = rhs.size;
	}

	T& operator[](int index) {
		return *(_first + index);
	}

	~vector() {
		//delete[] _first;
		for (T* p = _first; p != _last; p++) {
			_allocate.destroy(p);
		}
		_allocate.deallocate(_first);
		_end = _last = _first = nullptr; 
	}

	void push_back(const T& val) {
		if (full()) {
			cout << "vector is full\n" << endl;
			expand();
		}
		//*_last++ = val;
		_allocate.construct(_first + size, val);
		_last++;
		size++;
	}
	void pop_back() {
		if (empty()) {
			//throw "vector is empty!";
			cout << "vector is empty\n" << endl;
			return;
		}
		_last--;
		_allocate.destroy(_last);
		size--;
		return;
	}


	T& back() {
		if (empty()) {
			cout << "vector is empty\n";
			//throw "vector is empty";
			return *(_last - 1);
		}
		return *(_last - 1);
	}

	bool full() {
		if (_last == _end) {
			return true;
		}
		return false;
	}
	bool empty() {
		if (_first == _last) {
			return true;
		}
		return false;
	}
	void expand() {
		//T* tmp = new T[len * 2];
		T* tmp = _allocate.allocate(len * 2);
		
		for (int i = 0; i < len; i++) {
			tmp[i] = _first[i];
		}

		//delete[] _first;
		_allocate.deallocate(_first);

		len *= 2;
		_first = tmp;
		_last = _first + size;
		_end = _first + len;
	}


	class iterator {
	public:
		iterator(T *ptr = nullptr) : _ptr(ptr) {}

		bool operator!=(const iterator& rhs) {
			return _ptr != rhs._ptr;
		}

		bool operator==(const iterator& rhs) {
			return _ptr == rhs._ptr;
		}

		void operator++() {
			_ptr++;
		}

		T& operator*() {
			return *_ptr;
		}

		const T& operator*() const {
			return *_ptr;
		}

	private:
		T* _ptr;
	};

	iterator begin() {
		return iterator(_first);
	}
	iterator end() {
		return iterator(_end);
	}

private:
	T* _first; //指向数组第一个元素
	T* _end; //数组空间的后继位置
	T* _last; //有效元素的后继位置
	int size; //当前有效元素个数
	int len; //当前空间总个数
	Alloca _allocate; //内存空间配置器


};



int main(int argc, char **argv) {
	vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(4);
	vec.push_back(4);
	vector<int> vec1;
	vec1 = vec;

	//for (int i = 0; i < 7; i++) {
	//	cout << vec.back() << endl;
	//	vec.pop_back();
	//}

	//for (int i = 0; i < 7; i++) {
	//	cout << vec1.back() << endl;
	//	vec1.pop_back();
	//}

	cout << vec1[1] << endl;
	for (vector<int>::iterator it = vec1.begin(); it != vec1.end(); ++it) {
		cout << *it << endl;
	}

	return 0;
}
#endif