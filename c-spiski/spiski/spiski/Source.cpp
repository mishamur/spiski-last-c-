/*
Даны два списка целых чисел:
a0, a1, ..., an - 1(|ai| <= 100)
и b0, b1, ..., bm−1(| bi| <= 100).
Проверить, все ли элементы одного из списков принадлежат другому ?

 Автор: Котов М.В.
 Дата: 11.09.2020
 Предмет: Практикум по программированию
*/

#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

//список
struct List {
	int info;
	List *next;
	List *pred;
};

//создание списка
void createRandomList(List *&head, List *&tail, int n) {
	head = new List;
	tail = new List;

	head->next = tail;
	tail->pred = head;
	List *last = head;



	for (int i = 0; i < n; i++) {
		List *p;
		p = new List;
		int numb;
		cin >> numb;
		p->info = numb;
		//p->info = rand() % 200 - 100;
		p->pred = last;
		p->next = last->next;
		last->next = p;
		p->next->pred = p;
	}
	return;
}

//вывод списка
void printList(List *head, List *tail) {
	List *p = head->next;
	
	while (p != tail) {
		cout << p->info << "\t";
		p = p->next;
	}
	cout << endl;
	return;
}

void test(List *aHead, List *aTail, List *bHead, List *bTail) {
	//все ли числа первого списка содержит второй список
	List *p1, *p2;
	p1 = aHead->next;
	p2 = bHead->next;


	while (p1 != aTail) {
		while (p1->next != aTail && p1->info == p1->next->info ) {
			p1 = p1->next;
		}
		if (p1->info < p2->info) {
			cout << "Нет!!!! Не все элементы первого списка входят во второй ";
			return;
		}
		else if (p1->info > p2->info) {
			while (p2 != bTail) {
				if (p1->info == p2->info) {
					p1 = p1->next;
					break;
				}
				p2 = p2->next;
			}
			if (p2 == bTail) {
				cout << "Нет, не все элементы первого списка входят во второй ";
				return;
			}
		}
		else if (p1->info == p2->info) {
			p1 = p1->next;
			continue;
		}
	}
	cout << endl << "Все числа из первого списка входят во второй" <<endl;
	return;
}


//сортировка списка
void sortList(List *&aHead, List *&aTail) {
	List *p, *L, *R;

	//p = aHead->next;
	L = aHead->next;
	R = aTail->pred;
	p = R->pred;
	while (p != aHead) {

		while (p->next != aTail) {
			if (p->info > p->next->info) {

				List *pP = p->pred;
				List *tempB = p->next;
				//связали next
				p->pred->next = p->next;
				p->next = tempB->next;
				tempB->next = p;

				//связали pred
				p->pred = tempB;
				tempB->pred = pP;
				p->next->pred = p;

				p = p->pred;
			}

			p = p->next;
		}
		R = R->pred;
		p = R;
	}
}

// Функция исключает элемент р из списка, возвращает указатель на
// элемент, следовавший после него
List * removeElement(List *p)
{
	if (p)
	{
		List * p1 = p->pred;
		List * p2 = p->next;
		p1->next = p2;
		p2->pred = p1;
		p->pred = p->next = NULL;
		return p2;
	}
	else
		return NULL;
}

//Функция вставляет элемент p в список после элемента last
// возвращает указатель на вставленный в список элемент
List * insertElementIntoList(List * last, List * p)
{
	if (last && p)
	{
		p->pred = last;
		p->next = last->next;
		last->next = p;
		p->next->pred = p;
		return p;
	}
	else
		return NULL;
}



int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "RUS");
	List *aHead = NULL, *aTail = NULL;//список А
	List *bHead = NULL, *bTail = NULL;//список В


	cout << "Введите размер первого списка: ";
	int n;
	cin >> n;

	cout << "Введите размер второго списка: ";
	int m;
	cin >> m;
	cout << "Введите значения списка: ";
	createRandomList(aHead, aTail, n);
	cout << "Исходный список А: "<<endl;
	
	printList(aHead, aTail);

	cout << "Отсортированный список А:" << endl;
	sortList(aHead, aTail);
	printList(aHead, aTail);
	cout << endl;

	cout<< endl << "Введите значения списка: ";
	createRandomList(bHead, bTail, m);
	cout << endl << endl << "Исходный список В: " << endl;
	printList(bHead, bTail);

	cout << "Отсортированный список B:" << endl;
	sortList(bHead, bTail);
	printList(bHead, bTail);

	test(aHead, aTail, bHead, bTail);
	cout << endl;
	system("pause");
	return 0;
}