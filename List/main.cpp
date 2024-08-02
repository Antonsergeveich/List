#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class List
{
	class Element
	{
		int Data;      //значение элемента
		Element* pNext;//указательна следующий элемент
		Element* pPrev;//указатель на предыдущий элемент

	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;  //объекты класса можно объявлять непосредственно после его описания.
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
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//                 Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//1) Создаём новый элемент:
			Element* New = new Element(Data);

			//2) Привязываем новый элемент к началу списка:
			New->pNext = Head;

			//3) Привязываем головной элемент списка к новому элементу:
			Head->pPrev = New;

			//4) Смещаем голову на новый элемент:
			Head = New;
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		else
		{
			Element* New = new Element(Data); // Создаём новый элемент
			New->pPrev = Tail;                // Привязываем новый элемент к концу списка
			Tail->pNext = New;                // Привязываем хвост к новому элементу
			Tail = New;                       // Смещаем хвост на новый элемент
		}
		size++;
	}
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return; // Если указывают на ноль, то ничего не делаем;
		if (Head == Tail) // Если указывают на один и тот же элемент;
		{
			delete Head;            //удаляем голову
			Head = Tail = nullptr;  //обнуляем Head и Tail
			return;
		}
		Head = Head->pNext;     // Убираем нулевой элемент из списка
		delete Head->pPrev;     // Удаляем нулевой элемент из памяти
		Head->pPrev = nullptr;  // Делаем указатель Head->pPrev нулевым чтобы он не указывал на удалённый элемент
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front(); //ЕЕсли один элемент в списке то с начала удаляем
		Tail = Tail->pPrev;     // Привязываем хвост к предыдущему элементу
		delete Tail->pNext;     // Удаляем последний элемент 
		Tail->pNext = nullptr;  // Новый последний элемент указываем на ноль, так как он указывает на удалённый элемент
		size--;
	}

	//                      Methods:
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов в списке: " << size << endl;
	}
	void reverse_print()
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов в списке: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	list.reverse_print();
	list.push_back(256);
	list.print();
	list.pop_front();
	list.print();
	list.pop_back();
	list.print();
}