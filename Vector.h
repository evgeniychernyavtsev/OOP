#pragma once

template<class T> class Vector
{
public:
	Vector<T>() 
	{
		_size = 0;
		_capacity = 0;
		_data = nullptr;
	}
	Vector<T>(unsigned int size)
	{
		_size = size;
		_capacity = size;
		_data = new uint8_t[size * sizeof(T)];
	}
	Vector<T>(Vector<T> const& vec)
	{
		_size = vec._size;
		_capacity = vec._capacity;
		_data = new uint8_t[_capacity * sizeof(T)];
		for (unsigned int i = 0; i < _size; i++)
		{
			vec[i] = new uint8_t[_data + i * sizeof(T)];
		}
	}
	~Vector<T>()
	{
		for (unsigned int i = 0; i < _size; i++)
		{
			this->operator[](i).~T();
		}
		delete[] _data;
	}
	T& operator[] (unsigned int const & id) const
	{
		if (id < 0 || id >= _size)
			throw std::runtime_error("vector out of bounds");
		return reinterpret_cast<T&>(_data[id * sizeof(T)]);
	}
	unsigned int size() const
	{
		return _size;
	}
	void reserve(unsigned int capacity)
	{
		if (capacity <= _size)
			return;
		uint8_t* tmp = new uint8_t[capacity * sizeof(T)];
		for (unsigned int i = 0; i < _size * sizeof(T); i++)
			tmp[i] = _data[i];
		_capacity = capacity;
		delete[] _data;
		_data = tmp;
	}
	void push(T const & element)
	{
		if (_capacity == 0)
			reserve(2);
		else if (_size >= _capacity)
			reserve(_capacity * 2);
		new(_data + _size * sizeof(T)) (T)(element);
		_size++;
	}
	void pop()
	{
		if (_size > 0)
		{
			this->operator[](_size - 1).~T();
			_size--;
		}
	}
	void clear()
	{
		while (_size > 0)
			pop();
		delete[] _data;
		_size = 0;
		_capacity = 0;
	}
	unsigned int capacity() const
	{
		return _capacity;
	}
	bool empty() const
	{
		return _size == 0;
	}
	void print(std::ostream& out) const
	{
		for (unsigned int i = 0; i < _size; i++)
			out << reinterpret_cast<T&>(_data[i * sizeof(T)]) << std::endl;
	}
private:
	size_t _size, _capacity;
	uint8_t* _data;
};