#pragma once
#include<iostream>
#include<string>
#include <new.h>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n-------------------------------\n"

/// /////////////////////////////////////////////////////// ///
///           Class declaration (���������� ������)         ///

template<typename T>class List
{
	class Element
	{
		T Data;      //�������� ��������
		Element* pNext;//����������� ��������� �������
		Element* pPrev;//��������� �� ���������� �������
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;  //������� ������ ����� ��������� ��������������� ����� ��� ��������.
	//Element* Head;
	//Element* Tail;
	size_t size; //typedef unsigned __int64 size_t;
	//size_t - ��� typedef �� 'unsigned int'.
	//��������� 'typedef' ������ ��������� ��� ������������� ���� ������.
	//typedef ����� ��������� ���������: typedef ������������_���_������ ���������
	/*size_t � ��� ����������� ����������� ������������� ���, ����������� � ����������� ����������� ������ � � �++.
		�� �������� ����� ����������, ������������� ���������� sizeof � alignof.����������� ���������� ��������� ���� size_t �������� ��������� SIZE_MAX.
		������ size_t ���������� ����� �������, ����� � ���� ����� ���� �������� ������������ ������ ������������ ���������� ������� ��� �������.
		���� ��� ������������ : ��� �������� �������� ��������; ��� ���������� ��������; ��� �������� ����������.*/
		//https://cplusplus.com/reference/cstddef/size_t/
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) :Temp(Temp) {}
		~ConstBaseIterator() {}
		//             Comparison operators:
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		//              Dereference operators (��������� ��������������):
		const T& operator*()const;
	};
public:
	class ConstIterator : public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}
		//                 Incremento/Decremento:
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	// ���� ��������� ������������� �������� �������� � ������, 
	// �� ����� ����������� ���������� ����� ��� � ������� ���������.
	// ������� ��������� ����� ��������� 
	// ����������� ��������� ������� �� ����������� ���������������.

	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};

	Iterator begin();
	Iterator end();
	ConstIterator begin()const;
	ConstIterator end()const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();
	//                 Operators:
	List<T>& operator=(const List<T>& other);
	//                 Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void pop_front();
	void pop_back();
	void insert(T Data, int index);
	//                      Methods:
	void print()const;
	void reverse_print()const;
};

///      Class declaration end ( ����� ���������� ������)       ///
/// /////////////////////////////////////////////////////////// ///