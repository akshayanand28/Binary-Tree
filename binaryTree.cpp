#include<iostream>
#include<queue>
using namespace std;
struct btNode
{
	int info;							//integer information of the node
	btNode* left;							//left child node
	btNode* right;							//right child node
};
btNode* getNode(int info)						//creating a new node
{	btNode* newNode = new btNode();					//create pointer to new node of type btNodd
	newNode->info = info;						//assign info to new node
	newNode->left = NULL;						//initialise left child to null
	newNode->right = NULL;						//initialise right child to null
	return newNode;							//pointer to new node
}
btNode* insertNode(btNode* root,int info)				//inserting new node using BFS algorithm		
{

	if(root == NULL)						//boundary condition of an empty tree
		root = getNode(info);
	else
	{
		queue<btNode*> Q;					//using BFS algorithm
		Q.push(root);						//root is the first node to be pushed
		while(!Q.empty())					//run loop till all the nodes are visited
		{	
			btNode* current = Q.front();
			if(current->left != NULL)			//if left subtree is not empty then push the left child to the queue
				Q.push(current->left);
			else
			{
				current->left = getNode(info);		//if left subtree is empty then add the new node there
				break;
			}
			if(current->right != NULL)			//if right subtree is not empty then push the right child to the queue
				Q.push(current->right);
			else
			{
				current->right = getNode(info);		//if right subtree is empty then add the new node there
				break;
			}
			Q.pop();					//pop the current first node in queue
		}
	}
	return root;							//pointer to root
}
void searchNode(btNode* root,int info)					//search node with a specific info value using BFS algorithm
{
	if(root == NULL)						//boundary condition of an empty tree
	{
		cout<<info<<" Not Found"<<endl;
		return;
	}
	btNode* current;
	queue<btNode*> Q;						//using BFS algorithm
	Q.push(root);							//root is the first node to be pushed
	while(!Q.empty())						//run loop till all the nodes are visited
	{
		current = Q.front();
		if(current->left != NULL)				//if left subtree is not empty
		{
			if(current->left->info == info)			//check if value is equal to the one being searched
			{

				cout<<info<<" Found"<<endl;
				break;					//break out of loop if element is found
			}
			Q.push(current->left);				//if value not equal then push the left child to the queue
		}
		if(current->right != NULL)				//if right subtree is not empty
		{
			if(current->right->info == info)		//check if value is equal to the one being searched
			{
				cout<<info<<" Found";
				break;					//break out of loop if element is found
			}
			Q.push(current->right);				//if value not equal then push the right child to the queue
		}
		Q.pop();						//pop the current first node in queue
	}
	cout<<info<<" Not Found"<<endl;					//all nodes are visited but required node not found
}
void levelOrder(btNode* root)						//level wise traversal ( breadth first )
{
	if(root == NULL)						//boundary condition of an empty tree
		return;
	queue<btNode*> Q;
	Q.push(root);							//root is the first node to be pushed
	while(!Q.empty())						//run loop till all the nodes are visited
	{
		btNode* current = Q.front();
		cout<<current->info<<"\t";
		if(current->left != NULL)				//if left subtree is not empty then push the left child to the queue
			Q.push(current->left);
		if(current->right != NULL)				//if right subtree is not empty then push the right child to the queue
			Q.push(current->right);
		Q.pop();						//pop the current first node in queue
	}
	cout<<endl;
}
void preOrder(btNode* root)						//traversal order root --> left --> right
{
	if(root == NULL)						//boundary condition of an empty tree
		return;
	cout<<root->info<<"\t";
	preOrder(root->left);						//recursive call with left child node as root
	preOrder(root->right);						//recursive call with right child node as root
}
void inOrder(btNode* root)						//traversal order left --> root --> right
{
	if(root == NULL)						//boundary condition of an empty tree
		return;
	inOrder(root->left);						//recursive call with left child node as root
	cout<<root->info<<"\t";
	inOrder(root->right);						//recursive call with right child node as root
}
void postOrder(btNode* root)						//traversal order left --> right --> root
{
	if(root == NULL)						//boundary condition of an empty tree
		return;
	postOrder(root->left);						//recursive call with left child node as root
	postOrder(root->right);						//recursive call with right child node as root
	cout<<root->info<<"\t";
}
btNode* deleteNode(btNode* root, int info)				//deleting node using BFS algorithm
{
	if(root == NULL)						//boundary condition of an empty tree
		return root;
	int repInfo, found=0;						//integer info of the node to be replaced ( bottom most, right most )
	btNode* delNode = NULL;						//initialising the node to be deleted
	btNode* current;						//pointer to keep track of the current temporary node

	//finding the bottom most, right most node and the node to delete
	queue<btNode*> Q;
	Q.push(root);							//root is the first node to be pushed
	while(!Q.empty())						//run loop till all the nodes are visited
	{
		current = Q.front();
		if(current->info == info)				//if info of current node is same as the one to be deleted
		{
			delNode = current;				//assign the pointer of current node to delNode
			found = 1;
		}
		if(current->left != NULL)				//if left subtree is not empty then push the left child to the queue
			Q.push(current->left);
		if(current->right != NULL)				//if right subtree is not empty then push the right child to the queue
			Q.push(current->right);
		Q.pop();						//pop the current first node in queue
	}
	if(found == 0)
	{
		cout<<"Element does not exist\n";
		return root;
	}
	repInfo = current->info;					//assign the value of bottom most, right most node to repInfo for using for replacement

	//deleting the bottom most, right most node
	Q.push(root);							//root is the first node to be pushed
	while(!Q.empty())						//run loop till all the nodes are visited
	{
		current = Q.front();						
		if(current->right != NULL)				//if right subtree is not empty
		{
			if(current->right->info == repInfo)		//check if value of right child is equal to repInfo
			{
				delete current->right;			//if equaL then delete the right child
				current->right = NULL;			//set the pointer to right child as null
				break;					//break out of the loop
			}
			Q.push(current->right);				//if value not equal then push the right child to the queue	
		}
		if(current->left != NULL)				//if left subtree is not empty
		{
			if(current->left->info == repInfo)		//check if value of left child is equal to repInfo
			{

				delete current->right;			//if equaL then delete the left child
				current->left = NULL;			//set the pointer to left child as null
				break;					//break out of the loop
			}
			Q.push(current->left);				//if value not equal then push the left child to the queue
		}
		Q.pop();						//pop the current first node in queue
	}
	delNode->info = repInfo;
	cout<<info<<" Deleted\n";					//replace the info of node to be deleted with the info of the previously bottom most, right most node
	return root;							//pointer to root
}
int main()
{
	btNode* root = NULL;
	int ch,n;
	while(1)
	{
		cout<<"1. Insert Node\n2. Search Node\n3. Level Order Traversal\n4. Pre Order Traversal\n5. In Order Traversal\n6. Post Order Traversal\n7. Delete Node\n8. Exit\n";
		cin>>ch;
		switch(ch)
		{
			case 1: cout<<"Enter Number to be Inserted : ";
					cin>>n;
					root = insertNode(root,n);
					cout<<n<<" Inserted\n";
					break;
			case 2: cout<<"Enter Number to be Searched : ";
					cin>>n;
					searchNode(root,n);
					break;
			case 3: cout<<"Level Order Traversal :\n";
					levelOrder(root);
					cout<<endl;
					break;
			case 4: cout<<"Pre Order Traversal :\n";
					preOrder(root);
					cout<<endl<<endl;
					break;
			case 5: cout<<"In Order Traversal :\n";
					inOrder(root);
					cout<<endl<<endl;
					break;
			case 6: cout<<"Post Order Traversal :\n";
					postOrder(root);
					cout<<endl<<endl;
					break;
			case 7: cout<<"Enter Number to be Deleted : ";
					cin>>n;
					root = deleteNode(root,n);
					break;
			case 8: return 0;
		}	
	}
}
