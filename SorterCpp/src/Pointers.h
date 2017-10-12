#pragma once
/**
* Licensed under MIT license (see LICENSE for details)
* Copyright (c) 2017 Bartosz Grabias
*/

// Default deleter
template<typename T> struct DefaultDeleter
{
	void operator()(T* pointer) const
	{
		delete pointer;
	}
};

// Array deleter - template specialization
template<typename T> struct DefaultDeleter<T[]>
{
	void operator()(T* pointer) const
	{
		delete[] pointer;
	}
};

/**
* I'm prohibited from using STL so this is
* a simplistic implementation of a unique pointer
*/
template<typename T, typename Deleter = DefaultDeleter<T>> class UniquePointer
{
private:
	T* m_data;
public:
	UniquePointer()
		: this(nullptr)
	{}
	UniquePointer(T* data)
		: m_data(data)
	{}

	~UniquePointer() noexcept
	{
		if (m_data)
			DefaultDeleter()(m_data);

		m_data = nullptr;
	}

	T* Get() const { return m_data; }
	T* operator->() const { return m_data; }
	T& operator*() const { return *m_data; }

	bool Empty() const { return m_data == nullptr; }
	bool operator bool() const { return !Empty(); }

	void swap(UniquePointer<T>& other) noexcept
	{
		T* temp = m_data;
		m_data = other.m_data;
		other.m_data = temp;
	}

	// Disallow copy
	UniquePointer(const UniquePointer& other) = delete;
	UniquePointer& operator=(const UniquePointer& other) = delete;
};

template<typename T, typename Deleter = DefaultDeleter<T>> class UniquePointer<T[], Deleter>
{
private:
	T* m_data;
public:
	UniquePointer()
		: this(nullptr)
	{}
	UniquePointer(T* data)
		: m_data(data)
	{}

	~UniquePointer() noexcept
	{
		if (m_data)
			DefaultDeleter()(m_data);

		m_data = nullptr;
	}

	T* Get() const { return m_data; }
	T* operator->() const { return m_data; }
	T& operator*() const { return *m_data; }
	T& operator[](int index) const { return m_data[i]; }

	bool Empty() const { return m_data == nullptr; }
	bool operator bool() const { return !Empty(); }

	void swap(UniquePointer<T[]>& other) noexcept
	{
		T* temp = m_data;
		m_data = other.m_data;
		other.m_data = temp;
	}

	// Disallow copy
	UniquePointer(const UniquePointer& other) = delete;
	UniquePointer& operator=(const UniquePointer& other) = delete;
};
