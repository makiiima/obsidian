int is_empty(queue q)
{
    return (q.top==q.rear);
}

int front(queue q)
{
    return q.data[q.top];
}

int pop(queue q)
{
    if (is_empty(q)){
        return -1;
    }
    else
    {
        q.top++;
        return q.data[q.top-1];
    }
}

int push(queue q, int n)
{
    if(q.rear>=MAXSIZE-1){
        return -1;
    }
    else
    {
        q.rear++;
        q.data[q.rear]=n;
        return 1;
    }
}