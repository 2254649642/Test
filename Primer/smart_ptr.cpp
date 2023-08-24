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
	atomic_int mcount; //casԭ�Ӳ������ö��̱߳�ð�ȫ
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
	T* mptr; //ָ����Դ��ָ��
	RefCnt<T>* refPtrCount; //���ü���
};


int main(int argc, char **argv) {
	CSmartPtr<int> refPtr(new int(20));
	cout << *refPtr << endl;

	return 0;
}
#endif