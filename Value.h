#pragma once
#include "BaseInterface.h"
template <typename T>
class Value :
	public BaseInterface
{
	lept_type m_lt; //类型标识符---确定当前对象的实际类型
	T m_data; 
public:
	Value(const T& data);
	Value() :m_lt(LEPT_NULL){};

	lept_type get_type();
	void set_data(const T&data);
	void set_type(lept_type lt);
	operator T();
};

template<typename T>
inline Value<T>::Value(const T& data):m_data(data),m_lt(LEPT_NULL)
{}

template<typename T>
inline lept_type Value<T>::get_type()
{
	return m_lt;
}

template<typename T>
inline void Value<T>::set_data(const T& data)
{
	m_data = data;
}

template<typename T>
inline void Value<T>::set_type(lept_type lt)
{
	if (lt == m_lt)
		return;
	m_lt = lt;
}

template<typename T>
inline Value<T>::operator T()
{
	return m_data;
}
