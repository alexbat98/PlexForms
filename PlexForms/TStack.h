#pragma once

template <typename T>
class TStack
{
private:
	T *arr;
	int size;
	int last;
public:
	TStack(int n = 25)
	{
		size = n;
		arr = new T[size];
		T zero(0);
		last = 0;

		for (int i = 0; i < size; i++)
		{
			arr[i] = zero;
		}
	}

	TStack(const TStack& src)
	{
		size = src.size;
		arr = new T[size];

		for (int i = 0; i < size; i++)
		{
			arr[i] = src.arr[i];
		}
		last = src.last;
	}

	~TStack()
	{
		//delete[] arr;
	}

	TStack<T>& operator= (const TStack<T>& src)
	{
		if (size != src.size)
		{
			if (size != 0)
			{
				delete[] arr;
			}

			arr = new T[size];
			size = src.size;
		}

		last = src.last;

		for (int i = 0; i < size; i++)
		{
			arr[i] = src.arr[i];
		}

		return *this;
	}

	bool isEmpty()
	{
		return (last == 0);
	}

	bool isFull()
	{
		return (last == size - 1);
	}

	T peek()
	{
		if (!isEmpty())
		{
			return arr[last - 1];
		}
		else
		{
			return nullptr;
		}
	}

	void push(T item)
	{
		if (!isFull())
		{
			arr[last++] = item;
		}
	}

	T pop()
	{
		//T res(0);

		if (!isEmpty())
		{
			return arr[--last];
			//arr[last--] = T(0);
		}

		return nullptr;
	}
};

