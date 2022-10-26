#ifndef _List_H

#define ElementType int;

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty( List L );
int IsEmpty( List L);
int IsLast( Position P, List L );
Position Find( ElementType X, List L );

#endif
