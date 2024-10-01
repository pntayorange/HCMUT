template <class T>
void SLinkedList<T>::add(const T& e) {
    if (head == NULL)   {head = tail = new Node(e,NULL); count++; return;}
    Node* tmp = new Node(e,NULL);
    tail -> next = tmp;
    tail = tail -> next;
    count++;
}

template<class T>
void SLinkedList<T>::add(int index, const T& e) {
    if (head == NULL)   {head = tail = new Node(e,NULL); count++; return;}
    if (index == 0){
        Node* tmp = new Node(e,head);
        head = tmp;
        count++;
        return;
    }
    Node *cur = head;
    for (int i=1;i<index;i++)   {cur = cur -> next;}
    Node *tmp = new Node(e,cur->next);
    cur->next = tmp;
    if (cur == tail)    tail = tmp;
    count++;
}

template<class T>
int SLinkedList<T>::size() {
    return count;
}
