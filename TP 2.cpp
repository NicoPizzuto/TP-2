#include <iostream>

using namespace std;

template <typename T>
struct Nodo
{
	T dato;
	Nodo<T> * next;
	Nodo<T> * ant = nullptr;
};

struct Pizza
{
	string gusto;
	int cant;
};

ostream& operator << (ostream &os, Pizza& p)
{
	os << p.gusto << " : " << p.cant;
	return os;
}

template <typename T> void push_dosvalores(Nodo<T> *&pila, T valor1, T valor2)
{
	Nodo<T> * nuevo = new Nodo<T>;
	Nodo<T> * puntero1 = pila;
	Nodo<T> * puntero2 = pila;
	Nodo<T> * nuevo_ult = new Nodo<T>;
	nuevo_ult->dato = valor2;
	nuevo_ult->next = nullptr;
	nuevo->dato = valor1;
	nuevo->next = pila;
	pila = nuevo;
	if (puntero1 == nullptr)
	{
		pila->next = nuevo_ult;
	}
	else
	{
		while (puntero1->next != nullptr)
		{
			puntero2 = puntero1;
			puntero1 = puntero1->next;
		}
		if (puntero1 != puntero2)
		{
			puntero1->next = nuevo_ult;
		}
	}
}

template <typename T> void agregar_dosvalores(Nodo<T> * &cola, T valor, T valor2)
{
	Nodo<T> * nuevo = new Nodo<T>;
	nuevo->dato = valor;
	nuevo->next = nullptr;
	Nodo<T> * nuevo2 = new Nodo<T>;

	if (cola == nullptr)
	{
		nuevo2->dato = valor2;
		nuevo2->next = nuevo;
		cola = nuevo2;
	}
	else
	{
		Nodo<T> * aux = cola;
		while (aux->next != nullptr) 
		aux = aux->next;		 
		aux->next = nuevo;
		nuevo2->dato = valor2;
		nuevo2->next = cola;
		cola = nuevo2;
	}
}

template <typename T> void pop_dosvalores(Nodo<T> * &pila)
{
	T valor = pila->dato;
	T valor2;
	Nodo<T> * aux_elim = pila;
	pila = pila->next;
	Nodo<T> * puntero1 = pila;
	Nodo<T> * puntero2 = pila;
	delete aux_elim;
	if (pila != nullptr)
	{
		while (puntero1->next != nullptr)
		{
			puntero2 = puntero1;
			puntero1 = puntero1->next;
		}
		if (puntero1 != puntero2)
		{
			valor2 = puntero1->dato;
			puntero2->next = nullptr;
			delete puntero1;
		}
	}
	cout << "El primer valor igual a: " << valor << endl << "El valor final igual a: " << valor2 << endl;
}

template <typename T> void mostrar(Nodo<T> * lista)
{
	while (lista != nullptr)
	{
		cout << lista->dato << endl;
		lista = lista->next;
	}
}

template <typename T> void mostrar_primer_segundo_valor(Nodo<T> * lista)
{
	if (lista != nullptr)
	{
		cout << lista->dato << endl; 
		Nodo<T> * puntero1 = lista;
		Nodo<T> * puntero2 = lista;
		while (puntero1->next != nullptr)
		{
			puntero2 = puntero1;
			puntero1 = puntero1->next;
		}
		if (puntero1 != puntero2)
		{
			cout << puntero1->dato;
		}
	}
}

int criterio_int(int a, int b)
{
	return a - b;
}

int criterio_str(string a, string b)
{
	return (a < b) ? -1 : (a > b);
}

int criterio_pizza(Pizza a, Pizza b)
{
	if (a.gusto == b.gusto)
	return 0;
	else
	return a.gusto > b.gusto ? 1 : -1;
}

template <typename T> void buscar_linearDosValores(T clave, T clave2, Nodo<T> * lista, int (*criterio)(T, T))
{
	bool a = false;
	bool b = false;
	Nodo<T> * puntero2 = lista;
	while (lista->next != nullptr && a != true)
	{
		if (criterio(lista->dato, clave) == 0)
		{
			a = true;
		}
		lista = lista->next;
		lista->ant = puntero2;
		puntero2 = lista;
		if (lista->next == nullptr)
        {
            if (criterio(lista->dato, clave) == 0)
            {
				a = true;
            }
        }
	}
	while (lista->ant != nullptr && b != true)
	{
		if (criterio(lista->dato, clave2) == 0)
		{
			b = true;
		}
		lista = lista->ant;
		if (lista->ant == nullptr)
        {
            if (criterio(lista->dato, clave2) == 0)
            {
                b = true;
            }
        }
	}

	if (a == true && b == true)
	{
		cout << "Se han encontrado los dos valores: " << clave << " y " << clave2 << endl;
	}
	else if (b == true)
	{
		cout << "Se ha encontrado solo el valor: " << clave2 << endl;
		;
	}
	else if (a == true)
	{
		cout << "Se ha encontrado solo el valor: " << clave << endl;
	}
	else
	{
		cout << "Ninguno de los valores se ha encontrado en la lista" << endl;
	}
}

int main()
{
	Nodo<int> * pila = nullptr;
	push_dosvalores(pila, 1,2);
	push_dosvalores(pila, 3,4);
	push_dosvalores(pila, 5,6);
	cout << "Pila (1 2 3)" << endl;
	mostrar_primer_segundo_valor(pila);
	cout << endl<< "Eliminamos" << endl;
	while (pila != nullptr )
	{
		pop_dosvalores(pila);
	}
	cout << endl
	<< "Confirmamos pila vacia:" << endl;
	mostrar_primer_segundo_valor(pila);
	cout << "fin mostrar pila" << endl;
	cout << "-----------------" << endl;
	Nodo<string> * cola = nullptr;
	agregar_dosvalores(cola, "uno"s, "dos"s);
	agregar_dosvalores(cola, "tres"s, "cuatro"s);
	agregar_dosvalores(cola, "cinco"s, "seis"s);
	cout << endl << "Cola (uno dos tres)" << endl;
	mostrar_primer_segundo_valor(cola);
	cout << endl<< "Eliminamos" << endl;
	while (cola != nullptr)
	{
		pop_dosvalores(cola);
	}
	cout << endl<< "Confirmamos cola vacia:" << endl;
	mostrar_primer_segundo_valor(cola);
	cout << "Fin mostrar cola" << endl;
	cout << "-----------------" << endl;
	agregar_dosvalores(cola, "Juan"s, "Pedro"s);
	agregar_dosvalores(cola, "Pedro"s, "Maria"s);
	agregar_dosvalores(cola, "Jann"s, "Jasmin"s);
	mostrar(cola);
	cout << endl<< "Datos para la busqueda" << endl;
	mostrar_primer_segundo_valor(cola);
	string nombre, nombre2;
	cout << endl<< "Ingrese el nombre a buscar: ";
	while (cin >> nombre) 
	{
        cout << endl << "Ingrese el segundo nombre a buscar: ";
        cin >> nombre2;
        buscar_linearDosValores(nombre,nombre2, cola, criterio_str) ;
        cout << "Ingrese el nombre a buscar: ";
    }
	cin.clear(); 
	cout << endl << "-----------------" << endl;
	Nodo<Pizza> *lista = nullptr;
	agregar_dosvalores(lista, {"Muza", 4},{"Muza", 6});
	agregar_dosvalores(lista, {"Fugazzeta", 1},{"Fugazzeta", 3});
	agregar_dosvalores(lista, {"Pizzaiola", 2},{"Pizzaiola", 9});
	cout << endl << "Pedidos en la lista:" << endl;
	mostrar_primer_segundo_valor(lista);
	Pizza pizza_clave;
	Pizza pizza_clave2;
	cout << endl << "Ingrese el gusto a buscar: ";
	while (cin >> pizza_clave.gusto) 
	{
        cin >> pizza_clave2.gusto;
        buscar_linearDosValores(pizza_clave, pizza_clave2, lista, criterio_pizza);
        cout << "Ingrese el nombre a buscar: ";
		return EXIT_SUCCESS;
	}
}