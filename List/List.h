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
///           Class declaration (ОБЪЯВЛЕНИЕ класса)         ///

template<typename T>class List
{
	class Element
	{
		T Data;      //значение элемента
		Element* pNext;//указательна следующий элемент
		Element* pPrev;//указатель на предыдущий элемент
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;  //объекты класса можно объявлять непосредственно после его описания.
	//Element* Head;
	//Element* Tail;
	size_t size; //typedef unsigned __int64 size_t;
	//size_t - это typedef на 'unsigned int'.
	//Директива 'typedef' создаёт псевдоним для существующего типа данных.
	//typedef имеет следующий синтаксис: typedef существующий_тип_данных псевдоним
	/*size_t — это специальный беззнаковый целочисленный тип, определённый в стандартных библиотеках языков С и С++.
		Он является типом результата, возвращаемого оператором sizeof и alignof.Максимально допустимым значением типа size_t является константа SIZE_MAX.
		Размер size_t выбирается таким образом, чтобы в него можно было записать максимальный размер теоретически возможного массива или объекта.
		Этот тип используется : для хранения размеров объектов; для индексации массивов; для адресной арифметики.*/
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
		//              Dereference operators (операторы разыименования):
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
	// Если возникает необходимость изменить значение в списке, 
	// то кроме константных итераторов нужны ещё и обычные итераторы.
	// Обычные итераторы будут дополнять 
	// константные итераторы обычным не константным разъименованием.

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

///      Class declaration end ( Конец ОБЪЯВЛЕНИЯ класса)       ///
/// /////////////////////////////////////////////////////////// ///