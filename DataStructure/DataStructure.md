
# Chap.3 Lists, Stacks and Queues
## 1 Abstract Data Type

- Definition: **Data Type = {Objects}∪{Operations}**

## 2 The List ADT

- **Objects**:(item_0, item_1, ... , item_n-1)
- **Operations**:
    - Finding the length
    - Printing
    - Making an empty list
    - Find the k-th
    - Inserting after the k-th
    - Deleting an item
    - Finding next of the current item
    - Finding previous of the current

### Simple Array implementations

- Find_Kth takes O(1) time
- MaxSize has to be estimated
- Insertion and Deletion not only take O(N) time, but also involve a lot of data movements which takes time

### Linked Lists

```c
//Initialization
typedef struct list_node *list_ptr;
typedef struct list_node {
  char data [4];
  list_ptr next;
};
list_ptr ptr;
```

> Add a dummy head node to a list

### Doubly Linked Circular Lists

###  ![image-20221019154103593](./attachments/image-20221019154103593.png)

### Cursor Implementation of Linked Lists

Features that a linked list must have:

- The data are store in a collection of structures. Each structure contains data and a pointer to the next structure.
- A new structure can be obtained from the system's global memory by a call to malloc and released by a call to free.

![image-20221019160402637](./attachments/image-20221019160402637.png)
![[Pasted image 20221020023526.png]]
## 3 The Stack ADT
### ADT
- LIFO: Last-In-First-Out
- Insertions and deletions at the **top** only
- Objects: A finite orderd list with zero or more elements
- Operations:
	- Int IsEmpty(Stack S)
	- Stack CreateStack()
	- DisposeStack(Stack S)
	- MakeEmpty(Stack S)
	- Push(ElementType X, Stack S)
	- ELementType Top(Stack S)
	- Pop(Stack S)

### Implementations
#### Linked List Implementation(with a header node)
```c
Push(int x, Stack S)
{
	TmpCell->Next = S->Next;
	S->Next=TmpCell;
}

int Top(Stack S)
{
	return S->Next->Element;
}

int Pop(Stack S)
{
	FirstCell=S->Next
}
```

> calls to malloc() and free() are expensive->keep another stack as a recycle bin

#### Array Implementation
```c
struct StackRecord{
    int Capacity;//size
    int TopofStack;//top pointer
    ElementType *Array;//array for stack elements
}
```
> The stack model must be well **encapsulated**
> Error check must be done before Push and Pop(Top)
### Applications
- Balancing Symbols(check if brackets are balanced)
- Postfix Evaluation
  ![[Pasted image 20221020033536.png]]
  >Infix to Postfix Conversion
  >    The order of operands is the same in infix and post fix
  >    Operators with higher precedence appear before those with lower precedence
# Binary Tree

## Implementation
- Find
```c
//tail recursion
Position Find(ElementType X, SearchTree T)
{
	if(T == NULL)
		return NULL;
	if(X < T->Element)
		return Find(X,T->Left)
	else if(X > T->Element)
		return Find(X,T->Right)
	else
		return T;
}
//loop
Position Iter_Find(ElementType X, SearchTree T)
{
	while(T){
		if (X==T->Element)
			return T;
		else if ()
	}
}
```
$$ T(N)=X(N)=O(d), d=depth(X$$
- FindMin
```c
Position FindMin(SearchTree T)
{
	if (T==NULL)
		return NULL;
	else if (T->Left)
}
```
- FindMax