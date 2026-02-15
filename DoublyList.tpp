template <typename T>
DoublyList<T>::DoublyList()
{
    header  = nullptr;
    trailer = nullptr;
    this->length = 0;
}

template <typename T>
DoublyList<T>::DoublyList(const DoublyList<T>& copyObj)
: header(new Node), trailer(new Node) {
    copy(copyObj);
}

template <typename T>
DoublyList<T>& DoublyList<T>::operator=(const DoublyList<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
DoublyList<T>::~DoublyList() {
    clear();
    delete header;
    delete trailer;
    header = trailer = nullptr;
}

template <typename T>
void DoublyList<T>::append(const T& elem) {
    // TO DO: Implement the code for the append
    Node* newNode = new Node(elem);

    if(header == nullptr)
    {
        header = newNode;
        trailer = newNode;
    }
    else
    {
        trailer->next = newNode;
        newNode->prev = trailer;
        trailer = newNode;
    }

    this->length++;
}

template <typename T>
void DoublyList<T>::clear() {
    for (Node* curr = nullptr; header->next != trailer; ) {
        curr = header->next->next;
        delete header->next;
        header->next = curr;
    }

    trailer->prev = header;
    this->length  = 0;
}

template <typename T>
void DoublyList<T>::copy(const DoublyList<T>& copyObj) {
    this->length   = copyObj.length;
    Node* myCurr   = header;
    Node* copyCurr = copyObj.header->next;

    while (copyCurr != copyObj.trailer) {
        Node* n      = new Node(copyCurr->value);
        myCurr->next = n;
        n->prev      = myCurr;
        myCurr       = n;
        copyCurr     = copyCurr->next;
    }

    myCurr->next  = trailer;
    trailer->prev = myCurr;
}

template <typename T>
T DoublyList<T>::getElement(int position) const {
    // TO DO: Implent code for getElement at position
    typename DoublyList<T>::Node* current;

    if(position <= int(this->length/2))
    {
        current = header; //element zero
        for(int i = 0; i < position; i++)
        {
            current = current->next;
        }
        return current->value;
    }
    else
    {
        current = trailer; //last element
        for(int i = 0; i < this->length - position - 1; i++)
        {
            current = current->prev;
        }
        return current->value;
    }
}

template <typename T>
int DoublyList<T>::getLength() const {
    return this->length;
}


template <typename T>
void DoublyList<T>::insert(int position, const T& elem) {
  // TO DO: Implement code to insert an element to list

    Node* previous = nullptr;
    Node* current = header;

    Node* newNode = new DoublyList<T>::Node(elem);
    
    for(int i = 0; i < position && current != nullptr; i++)
    {
        previous = current;
        current = current->next;
    }

    //We want to set previous->next to the current node, and set newNode->next to current

    if(previous != nullptr) //First verify that previous is valid
    {
        previous->next = newNode;
    }
    else //If it's not, we are inserting at element zero. Set header as newNode.
    {
        header = newNode;
    }

    newNode->next = current;
    this->length++;
}

template <typename T>
bool DoublyList<T>::isEmpty() const {
    return this->length  == 0;
}

template <typename T>
void DoublyList<T>::remove(int position) {
    // TO DO: Implement code to remove element at given position
    typename DoublyList<T>::Node* current;
    typename DoublyList<T>::Node* currentPrev = nullptr;
    typename DoublyList<T>::Node* currentNext = nullptr;

    if(position <= int(this->length/2))
    {
        current = header; //element zero
        for(int i = 0; i < position; i++)
        {
            current = current->next;
        }
    }
    else
    {
        current = trailer; //last element
        for(int i = 0; i < this->length - position - 1; i++)
        {
            current = current->prev;
        }
    }

    currentPrev = current->prev;
    currentNext = current->next;
    delete current;

    this->length--;

    if(currentPrev == nullptr)
    {
        //we deleted the head, set accordingly
        header = currentNext;
        return;
    }
    else if(currentNext == nullptr)
    {
        //we deleted the tail, set accordingly
        trailer = currentPrev;
        return;
    }

    //patch hole in list
    currentPrev->next = currentNext;
    currentNext->prev = currentPrev;
}

template <typename T>
bool DoublyList<T>::search(const T& elem) const {
    // TO DO: Implement code to search for element
    if(this->length == 0)
    {
        return false;
    }

    typename DoublyList<T>::Node* current = header;
    while(current != nullptr)
    {
        if(current->value == elem)
        {
            return true;
        }
        current = current->next;
    }

    return false;
}

template <typename T>
void DoublyList<T>::replace(int position, const T& elem) {
    // TO DO: Add code for replace method
    typename DoublyList<T>::Node* current;

    if(position <= int(this->length/2))
    {
        current = header; //element zero
        for(int i = 0; i < position; i++)
        {
            current = current->next;
        }
    }
    else
    {
        current = trailer; //last element
        for(int i = 0; i < this->length - position - 1; i++)
        {
            current = current->prev;
        }
    }

    current->value = elem;
}

template <typename T>
ostream& operator<<(ostream& outStream, const DoublyList<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "List is empty, no elements to display.\n";
    }
    else {
        typename DoublyList<T>::Node* curr = myObj.header;
        if(myObj.length == 1)
        {
            outStream << curr->value;
        }
        else
        {
            while (curr != myObj.trailer) {
                outStream << curr->value;
                if (curr->next != myObj.trailer) {
                    outStream << " <--> ";
                }
                curr = curr->next;
            }
            if(curr != nullptr)
            {
                outStream << " <--> ";
                outStream << curr->value;
            }
        }
        outStream << endl;
    }

    return outStream;
}
