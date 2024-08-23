#include"List.h"

///////////////////////////////////////////////////////////////////
/// //////     Class definition (ОПРЕДЕЛЕНИЕ класса):    ////// ///

/////////////////////////////////////////////////////////
//////////         Element methods:           ///////////
template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}
//////////         Element methods:           ///////////
/////////////////////////////////////////////////////////

/// ----------------------------------------------- ///

///////////////////////////////////////////////////////////
//////////         Iterators methods:           ///////////

//                Const base iterator:
template <typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template <typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
//template<typename T>type name(parameters)modifiers
template <typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

//                 Const Iterator:
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

//                Const reverse iterator:
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator  List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator  List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
// Свернуть = CTRL + M + M;
// Писать в нескольких строках = SHIFT + ALT + (стрелочка вверх или стрелочка вниз)

//                    Iterator:
template<typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
//                  ReverseIterator:
template <typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

//////////         Iterators methods:           ///////////
///////////////////////////////////////////////////////////

/// --------------------------------------------------- ///

///////////////////////////////////////////////////////////
//////////              List methods:           ///////////
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		//push_front(*it);
		push_back(*it);
	}
}
template<typename T>List<T>::List(const List<T>& other) : List()
{
	*this = other;
	cout << "CopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//                Operators:
//type         name (   parameters   )
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}

//                 Adding elements:
template<typename T>void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
	}
	else
	{
		////1) Создаём новый элемент:
		//Element* New = new Element(Data);

		////2) Привязываем новый элемент к началу списка:
		//New->pNext = Head;

		////3) Привязываем головной элемент списка к новому элементу:
		//Head->pPrev = New;

		////4) Смещаем голову на новый элемент:
		//Head = New;

		Head = Head->pPrev = new Element(Data, Head);
	}
	size++;
}
template<typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)return push_front(Data);
	else
	{
		//Element* New = new Element(Data); // Создаём новый элемент
		//New->pPrev = Tail;                // Привязываем новый элемент к концу списка
		//Tail->pNext = New;                // Привязываем хвост к новому элементу
		//Tail = New;                       // Смещаем хвост на новый элемент
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}
	size++;
}
template<typename T>void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return; // Если указывают на ноль, то ничего не делаем;
	if (Head == Tail) // Если Head и Tail указывают на один и тот же элемент;
	{
		delete Head;            //удаляем голову
		Head = Tail = nullptr;  //обнуляем Head и Tail
		size--;
		return;
	}
	Head = Head->pNext;     // Убираем нулевой элемент из списка
	delete Head->pPrev;     // Удаляем нулевой элемент из памяти
	Head->pPrev = nullptr;  // Делаем указатель Head->pPrev нулевым чтобы он не указывал на удалённый элемент
	size--;
}
template<typename T>void List<T>::pop_back()
{
	if (Head == Tail)return pop_front(); //Если один элемент в списке то удаляем с начала 
	Tail = Tail->pPrev;     // Привязываем хвост к предыдущему элементу
	delete Tail->pNext;     // Удаляем последний элемент 
	Tail->pNext = nullptr;  // Новый последний элемент указываем на ноль, так как он указывает на удалённый элемент
	size--;
}
template<typename T>void List<T>::insert(T Data, int index)
{
	if (index > size)return;
	if (index == 0)return push_front(Data);
	if (index == size)return push_back(Data);
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - index - 1; i++)
		{
			Temp = Temp->pPrev;
		}
	}
	/*Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;*/

	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);

	size++;
}

//                      Methods:
template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов в списке: " << size << endl;
}
template<typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов в списке: " << size << endl;
}

template<typename T>
List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> buffer = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10; 
		//Для того чтобы невозможно было изменить операнды оператора +
		//создаём базовый класс с константными методами 
		//которые не дают изменять объекты для которых вызываются
	}
	return buffer;
}

/// //////     Class definition end (Конец ОПРЕДЕЛЕНИЯ класса):    ////// ///
/////////////////////////////////////////////////////////////////////////////