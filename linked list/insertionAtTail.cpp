#include<iostream>
using namespace std;
class Node{
    public:
    int val;
    Node* next;
    Node(int data)
    {
        val=data;
        next=NULL;
    }
};
void insertAtTail(Node* &head ,int val)
{
    Node* newNode=new Node(val);
    Node* temp=head;
    while(temp==NULL)
    {
        temp=temp->next;
    }
}
void display(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
int main()
{
    Node* head=NULL;
    insertAtTail(head,1);
    insertAtTail(head,2);
    insertAtTail(head,3);
    display(head);
    return 0;
}

