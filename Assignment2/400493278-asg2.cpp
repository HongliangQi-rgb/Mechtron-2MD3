#include <cstdlib>
#include <iostream>

class Element{ //Element class, store name and score
    std::string name;
    int score;
    public:
        Element() : name(" "), score(0) {}
        Element(std::string name , int score) : name(name) , score(score){}
    friend class DNode; // let DNode class and DLinkedList class can visit Element class
    friend class DLinkedList;
};

class DNode {   //define elem consist by name and score
 private:
  Element elem;                
  DNode* prev;               // I am in current, prev is before me, next is after me.
  DNode* next;              
  friend class DLinkedList;  
};

class DLinkedList {  //show all function I write
 public:
  DLinkedList();
  DLinkedList(const DLinkedList & other);                
  ~DLinkedList(); 
  DLinkedList& operator=(const DLinkedList& other);               
  bool empty() const;            
  const Element& front() const;     
  const Element& back() const;      
  void addFront(const Element& e);  
  void addBack(const Element& e);   
  void removeFront();            
  void removeBack();
  void ListSort(const Element& e);
  void ListnameSort(const Element& e);
  int Size()const;
  void AddScoreInOrder(std::string name, int score);
  void RemoveScore(int index);
  bool UpdateScore(std::string name, int score); 
  void Print();
  void OrderByName();
  void OrderByScore();
  void Append(DLinkedList& L);
  void Reverse();    
 private:                        
  DNode* header;        // define guard Node        
  DNode* trailer;

 protected:                           
  void add(DNode* v, const Element& e);  
  void remove(DNode* v);
  int SizeRecursion(DNode* Node) const;
  void PrintRecursion(DNode* node)const;           
};

DLinkedList::DLinkedList() {  
  header = new DNode;         
  trailer = new DNode;
  header->next = trailer;  
  trailer->prev = header;
  header->prev = NULL;
  trailer->next = NULL;
}

DLinkedList :: DLinkedList(const DLinkedList & other)// copy the linklist and store in a new memory.
{
  header = new DNode;        
  trailer = new DNode;
  header->next = trailer;  
  trailer->prev = header;
  DNode* current = other.header->next;
    while (current != other.trailer) {
        ListSort(current->elem);
        current = current->next;
    }
}

DLinkedList& DLinkedList::operator=(const DLinkedList& other)// write the operator "=" let two DLinkedList class to share content. 
{
  if (this != &other)
  {
    while (!empty())
    {
      removeFront();
    }
    DNode* current = other.header->next;
    while(current != other.trailer)
    {
      ListSort(Element(current->elem.name, current -> elem.score));
      current = current -> next;
    }
  }
  return *this;
}

DLinkedList::~DLinkedList() { 
  while (!empty()) {
    removeFront();  
  }
  delete header;  
  delete trailer;
}

bool DLinkedList::empty() const {  
  return (header->next == trailer);
}

const Element& DLinkedList::front() const {  
  return header->next->elem;
}

const Element& DLinkedList::back() const {  
  return trailer->prev->elem;
}

void DLinkedList::add(DNode* v, const Element& value) {
  DNode* newNode = new DNode;
  newNode->elem = value;
  newNode->next = v->next;
  newNode->prev = v;
  v->next->prev = newNode;
  v->next = newNode;
}

void DLinkedList::addFront(const Element& e) {  
  add(header, e);
}

void DLinkedList::addBack(const Element& e) {  
  add(trailer->prev, e);
}

void DLinkedList::remove(DNode* v) {  
  DNode* u = v->prev;                
  DNode* w = v->next;                 
  u->next = w;                       
  w->prev = u;
  delete v;
}

void DLinkedList::removeFront() {  
  remove(header->next);
}

void DLinkedList::removeBack() {  
  remove(trailer->prev);
}

int DLinkedList::SizeRecursion(DNode* Node) const
{
    if (Node  == trailer)return 0;
    return 1 + SizeRecursion(Node -> next); // use recursion way to calculate size
}

int DLinkedList::Size() const
{
    return SizeRecursion(header -> next);
}

void DLinkedList::ListSort(const Element& e)  //add a new element and insert it in a sort by score
{
    DNode* current = header -> next;
    while(current != trailer && current->elem.score >= e.score)
    {
        current = current -> next;
    }
    add(current->prev , e);
}

void DLinkedList::ListnameSort(const Element& e) //add a new element and insert it in a sort by Name
{
  DNode* current = header -> next;
  while(current != trailer && current -> elem.name < e.name)
  {
    current = current->next;
  }
  add(current->prev,e);
}

void DLinkedList::AddScoreInOrder(std::string name, int score)
{
    ListSort(Element(name,score));
}

void DLinkedList:: RemoveScore(int index)
{
    DNode* current = header -> next;
    for (int i = 0; i < index; i++)
    {
        current = current -> next;
    }
    remove(current);
}

bool DLinkedList::UpdateScore(std::string name, int score) 
{
    DNode* current = header -> next;
    DNode* Update;

    while (current != trailer && current->elem.name != name) // find the elem first
    {
        current = current -> next;
    }
    if (current -> elem.name ==name )
    {
        current -> elem.score = score;

        Update->elem.name = current->elem.name; // change the score
        Update->elem.score = current->elem.score;
        remove(current);
        ListSort(Element(Update->elem.name, Update->elem.score));
        return true;
    }
    else
    {
        std::cout<<"The name does not exist" << std::endl;
        return false;
    }    
}

void DLinkedList::PrintRecursion(DNode* node)const // print the list with recursion
{
    if (node == trailer)
    {
        return;
    }
    std::cout<<"{"<<node->elem.name<<","<<node->elem.score<<"}"<<"->";
    PrintRecursion(node->next);
}

void DLinkedList:: Print()
{
    PrintRecursion(header->next);
    std::cout<<"NULL"<<std::endl;
}

void DLinkedList::OrderByName() 
{
  DLinkedList newList;
  DNode* current = header -> next;
  while (current != trailer)
  {
    newList.ListnameSort(current->elem);
    current = current -> next;
  }
  while(!empty())
  {
    removeFront();
  }
  current = newList.header -> next;
  while(current != newList.trailer)
  {
    ListnameSort(current->elem);
    current = current -> next;
  }
}

void DLinkedList::OrderByScore()
{
  DLinkedList newList;
  DNode* current = header -> next;
  while (current != trailer)
  {
    newList.ListSort(current->elem);
    current = current -> next;
  }
  while(!empty())
  {
    removeFront();
  }
  current = newList.header -> next;
  while(current != newList.trailer)
  {
    ListSort(current->elem);
    current = current -> next;
  }
}

void DLinkedList::Append(DLinkedList& L)
{
  if (empty())
  {
    return;
  }
  DNode* lastnode = trailer -> prev;
  DNode* Lfirstnode = L.header -> next;
  DNode* Llastnode = L.trailer -> prev;

  lastnode-> next = Lfirstnode;
  Lfirstnode->prev = lastnode;

  Llastnode -> next = trailer; // Llastnode be the tail
  trailer -> prev = Llastnode;

  L.header -> next = L.trailer; // Let L be a empty list
  L.trailer -> prev = L.header;
}

void DLinkedList::Reverse()
{
  if (empty())return;
  DNode * current = header;
  DNode * medium = nullptr;

  while (current != nullptr)
  {
    medium = current -> prev; 
    current -> prev = current -> next; // nodes between current exchange position 
    current -> next = medium;
    current = current -> prev;
  }

  medium = header;
  header = trailer; // exchange the header and trailer to make nodes connect again. 
  trailer = medium;
}
