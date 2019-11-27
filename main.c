#include<stdio.h>
#define SIZE 40

struct stack
{
    int top;
    int items[SIZE];
};

struct stack* createStack()
{
    struct stack*s = malloc(sizeof(struct stack));
    s->top = -1;
    return s;
};

void push(struct stack *s , int value)
{
    if(s->top == SIZE-1)
    {
        printf("Stack is Full");
    }
    else
    {
        s->top++;
        s->items[s->top] = value;

    }
}

int pop(struct stack*s)
{
    int item;
    if(s->top==-1)
    {
        printf("Stack is Empty");
        return 0;
    }
    else
    {
        item = s->items[s->top];
        s->top--;
        return item;
    }



}


struct node
{
    int vertex;
    struct node* next;
};

struct node* createNode(int v)
{
    struct node* newnode = malloc(sizeof(struct node));
    newnode->vertex = v;
    newnode->next = NULL;
    return newnode;
};

struct Graph
{
    int vertex;
    struct node** adjlist;
    int* visited;
};

struct Graph* createGraph(int vertex)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->vertex = vertex;
    graph->adjlist = malloc(vertex* sizeof(struct node *));
    graph->visited = malloc(vertex *sizeof(int));

    int i;
    for(i=0;i<vertex;i++)
    {
        graph->adjlist[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;


};

void addEdge(struct Graph* graph , int src ,int dest)
{
    struct node*newnode = createNode(dest);
    newnode->next = graph->adjlist[src];
    graph->adjlist[src] = newnode;

    newnode = createGraph(src);
    newnode->next = graph->adjlist[dest];
    graph->adjlist[dest] = newnode;


}


void printGraph(struct Graph* graph)
{
    int v;
    for(v=0;v<graph->vertex;v++)
    {
        struct node*temp = graph->adjlist[v];

        printf("\n Adjacency list of vertex %d\n " , v);
        while(temp)
        {
            printf("%d ->" , temp->vertex);
            temp = temp->next;
        }
        printf("\n");


    }
}

void dfs(struct Graph* graph , int startnode)
{
     struct stack *s = createStack();
     graph->visited[startnode] = 1;

     push(s , startnode);

     while(s->top!=-1)
     {
         int current = pop(s);
         printf("Visited %d\n" , current);

         struct node*temp = graph->adjlist[current];

         while(temp)
         {
             int adjnode = temp->vertex;

             if(graph->visited[adjnode]==0)
             {
                 graph->visited[adjnode] = 1;
                 push(s , adjnode);
             }
             temp= temp->next;




         }

     }


}


int main()
{
    struct Graph *graph = createGraph(4);
    addEdge(graph , 0,1);
    addEdge(graph , 0,2);
    addEdge(graph,1,2);
    addEdge(graph , 2,3);

    dfs(graph , 2);
    return 0;
}


