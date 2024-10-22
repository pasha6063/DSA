#include<iostream>
using namespace std;
struct Node{
    int data;
    Node* left;
    Node* right;
};
//function to create a new node
Node* createNode(int value)
{
    Node* newNode=new Node();
    newNode->data=value;
    newNode->left=newNode->right=nullptr;
    return newNode;
}
Node* insert(Node* root, int value)
{
    if(root==nullptr)
    {
        return createNode(value);
    }
    if(value<root->data){

        root->left=insert(root->left,value);
    }
    else if(value>root->data){
        root->right = insert(root->right, value);
    }
    return root;
}
void inOrderTraversal(Node* root)
{
    if(root==nullptr)
    return;
    inOrderTraversal(root->left);
    cout<<root->data<<" ";
    inOrderTraversal(root->right);
}
void preOrderTraversal(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    cout << root->data << " "; // Print the data before visiting the left and right subtrees
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}
void postOrderTraversal(Node *root)
{
    if (root == nullptr)
    {
        return;
    }

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    cout << root->data<< " "; // Print the data after visiting the left and right subtrees
}
int main()
{
    Node* root =nullptr;
    root = insert(root,50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
    cout<<"In-oder traversal of the BST:"<<endl;
    inOrderTraversal(root);
    cout<<endl;

    cout << "Pre-oder traversal of the BST:"<<endl;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
    preOrderTraversal(root);
    cout << endl;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);
    cout << "Post-oder traversal of the BST:"<<endl;
    postOrderTraversal(root); 
    return 0;
}