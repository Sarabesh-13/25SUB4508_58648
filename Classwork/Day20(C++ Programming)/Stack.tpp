using namespace std;

template <typename T>
Stack<T>::Stack(int s)
{
    this->size = s;
    arr = new T[size];
    top = -1;
}

//push
template <typename T>
void Stack<T>::push(T value)
{
    if (isFull())
    {
        cout << "Stack overflow" << endl;
        return;
    }
    arr[++top] = value;
}

// Pop
template <typename T>
void Stack<T>::pop()
{
    if (isEmpty())
    {
        cout << "Stack empty" << endl;
        return;
    }
    top--;
}

// Peek
template <typename T>
T Stack<T>::peek()
{
    if (isEmpty())
    {
        cout << "Stack empty" << endl;
        return T();  // default value of T
    }
    return arr[top];
}

// isEmpty
template <typename T>
bool Stack<T>::isEmpty()
{
    return top == -1;
}

// isFull
template <typename T>
bool Stack<T>::isFull()
{
    return top == size - 1;
}

// Display
template <typename T>
void Stack<T>::display()
{
    cout<<"Stack elements"<<endl;
    for(int i=top;i>=0;i--)
    {
        cout<<arr[i]<<endl;
    }
}

// Destructor
template <typename T>
Stack<T>::~Stack()
{
    delete[] arr;
}

