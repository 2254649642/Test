#if 0
#include <iostream>
#include <atomic>

using namespace std;

template<typename T>
class RefCnt {
public:
	RefCnt(T* ptr = nullptr) 
		:mptr(ptr)
	{
		if (mptr != nullptr) {
			mcount = 1;
		}
	}

	void addRef() { mcount++; };
	int subRef() { return --mcount; };
private:
	T* mptr;
	atomic_int mcount; //cas原子操作，让多线程变得安全
};

template<typename T>
class CSmartPtr {
public:
	CSmartPtr(T* ptr = nullptr)
		:mptr(ptr)
	{
		refPtrCount = new RefCnt<T>(mptr);
	}

	~CSmartPtr() {
		if (refPtrCount->subRef() == 0) {
			delete mptr;
			mptr = nullptr;
		}
	}

	T& operator*() { return *mptr; }
	T* operator->() { return mptr; }

	CSmartPtr<T>& operator=(const CSmartPtr<T>& src) {
		if (this == &src) {
			return *this;
		}

		if (refPtrCount.subRef() == 0) {
			delete mptr;
		}
		mptr = src->mptr;
		refPtrCount = src->refPtrCount;
		refPtrCount.addRef();
		return *this;

	}

	CSmartPtr(const CSmartPtr<T>& src)
		:mptr(src->mptr), refPtrCount(src->refPtrCount)
	{
		if (mptr != nullptr) {
			refPtrCount.addRef();
		}
	}

private:
	T* mptr; //指向资源的指针
	RefCnt<T>* refPtrCount; //引用计数
};


int main(int argc, char **argv) {
	CSmartPtr<int> refPtr(new int(20));
	cout << *refPtr << endl;

	return 0;
}
#endif