#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

template <typename T>
class TreeNode {
    public:
    T data;
    vector<TreeNode<T>*> children;
    // creating a constructor
    TreeNode (T data){
        this->data=data;
    }

    ~TreeNode(){
        for (int i = 0; i < this->children.size(); i++)
        {
            delete children[i];
        }
        
    }
};

template <typename T>
class PairClass{
    public:
    TreeNode<int>* largest;
    TreeNode<int>* secondLargest;

    PairClass(TreeNode<int>* first, TreeNode<int>* second){
        this->largest=first;
        this->secondLargest=second;
    }
};


//1 Function for taking Levelwise input of the tree
TreeNode<int>* takeInputLevelwise(){
    int rootData;
    cout<<"Enter root data"<<endl;
    cin>>rootData;
    TreeNode<int>* root = new TreeNode<int>(rootData);

    // mere queue mein tree node pointers jaaenge of type integers
    queue<TreeNode<int>*> pendingNodes;
    pendingNodes.push(root);
    while (pendingNodes.size()!=0)
    {
        TreeNode<int>* front=pendingNodes.front();
        pendingNodes.pop();
        cout<<"Enter no. of children for "<<front->data<<endl;
        int numChild;
        cin>>numChild;
        for (int i = 0; i < numChild; i++)
        {
            int childData;
            cout<<"Enter "<<i<<"th child of "<<front->data<<endl;
            cin>>childData;
            // yaha p jo node bana rahe h hum usko dynamically allocate karu ya statically?
            /*
            TreeNode<int> child(childData);---------------->STATIC ALLOCATION
            front->children.push_back(&child);
            we cannot do this, after this scope ye memory udd jaaega and koi memory rahega 
            bhi nhi so.. we need to do DYNAMIC ALLOCATION of the node pointer.
            */
           TreeNode<int>* child=new TreeNode<int>(childData);
           front->children.push_back(child);
           pendingNodes.push(child);

        }
    }
    return root;
    

}

//2 Function for taking input of the tree
TreeNode<int>* takeInput(){
    int rootData;
    cout<<"Enter data:"<<endl;
    cin>> rootData;
    TreeNode<int>* root= new TreeNode<int>(rootData);
    int n;
    cout<<"Enter number of children for "<<rootData<<endl;
    cin>>n;
    for (int i = 0; i <n; i++)
    {
        TreeNode<int>* child= takeInput();
        root->children.push_back(child);
    }
    return root;
}


//3 Function for printing the tree
void printTree(TreeNode<int>* root){
    if (root == NULL)
    {
        return;
    }
    
    cout<<root->data<<':';
    for (int i = 0; i < root->children.size(); i++)
    {
        cout<<root->children[i]->data<<',';
    }
    cout<<endl;
    for (int i = 0; i < root->children.size(); i++)
    {
        printTree(root->children[i]);
    }
    
}


//4 Function for printing the tree levelwise
void printTreeLevelwise(TreeNode<int>* root){
    if (root == NULL)
    {
        return;
    }
    
    queue<TreeNode<int>*> queueHelper;
    queueHelper.push(root);
    while (!queueHelper.empty())
    {   
        
        TreeNode<int>* rootData=queueHelper.front();
        cout<<rootData->data<<':';
        queueHelper.pop();
        for (int i = 0; i <rootData->children.size() ; i++)
        {
            if (i<(rootData->children.size()-1))
            {
                cout<<rootData->children[i]->data<<',';
                queueHelper.push(rootData->children[i]);
            }
            else
            {
                cout<<rootData->children[i]->data;
                queueHelper.push(rootData->children[i]);
            }

        }
        cout<<endl; 
    }
    
}

//5 node counter using queue
int countNodes(TreeNode<int>* root){
    int counter=1;
    queue<TreeNode<int>*> q;
    q.push(root);
    while (!q.empty())
    {
        TreeNode<int>* rootData=q.front();
        q.pop();
        counter+=rootData->children.size();
        for (int i = 0; i < rootData->children.size(); i++)
        {
            q.push(rootData->children[i]);
        }
    }
    return counter;
    
}

//6 node counter using recursion
int countNodesRec(TreeNode<int>* root){
    int ans=1;
    for (int i = 0; i < root->children.size(); i++)
    {
        ans+=countNodesRec(root->children[i]);
    }
    return ans;
}

//7 finding the sum of all the nodes
int sumOfNodes(TreeNode<int>* root){
    if (root ==NULL)
    {
        return 0;
    }
    
    int sumNodes=root->data;
    for (int i = 0; i < root->children.size(); i++)
    {
        sumNodes+=sumOfNodes(root->children[i]);
    }
    return sumNodes;
}

//8 find node with max value
TreeNode<int>* maxNode(TreeNode<int>* root){
    if (root == NULL)
    {
        return 0;
    }
    TreeNode<int>* maxi=root;
    for (int i = 0; i < root->children.size(); i++)
    {
        TreeNode<int>*temp=maxNode(root->children[i]);
        if (maxi->data<temp->data)
        {
            maxi=temp;
        }
    }
    return maxi;
}

//9 find height of the tree
/*
root k child p ja aur child ka height dekhle bas, jaha p max height aa raha hoga waha p 
return karrwale height and add +1 to it as we are considering height of root is 1.
*/
int heightOfTree(TreeNode<int>* root){
    if (root==NULL)
    {
        return 0;
    }
    int height=0;
    for (int i = 0; i < root->children.size(); i++)
    {
        int childHeight=heightOfTree(root->children[i]);
        if (childHeight>height)
        {
            height=childHeight;
        }
        
    }
    return 1+height;
}

//10 print nodes till kth Depth from the root
void printdDepthKthNode(TreeNode<int>* root, int k){
    if (k==0)
    {
        cout<<root->data<<' ';
        return;
    }
    for (int i = 0; i <root->children.size(); i++)
    {
        printdDepthKthNode(root->children[i], k-1);
    }
}

//11 number of leaf nodes in the tree
int noOfLeafNodes(TreeNode<int>* root){
    if (root==NULL)
    {
        return 0;
    }
    int leaf=0;
    if (root->children.size()==0)
    {
        leaf++;
    }
    for (int i = 0; i < root->children.size(); i++)
    {
        leaf+=noOfLeafNodes(root->children[i]);
    }
    return leaf;
}

//12 print tree in preorder, means pehle root phirr uska baccha
void printPreOrder(TreeNode<int>* root){
    if (root==NULL)
    {
        return;
    }
    cout<< root->data<<' ';
    for (int i = 0; i < root->children.size(); i++)
    {
        printPreOrder(root->children[i]);
    }
}

//13 printing like pehle baccha phirr root
void printPostOrder(TreeNode<int>* root){
    if (root==NULL)
    {
        return;
    }
    for (int i = 0; i < root->children.size(); i++)
    {
        printPostOrder(root->children[i]);
    }
    cout<<root->data<<' '; 
}

//14 Find and return the node with next larger element in the Tree
TreeNode<int>* nextLargestEle(TreeNode<int>* root, int n){
    TreeNode<int>* ans=NULL;
    if (root==NULL)
    {
        return 0;
    }
    if (root->data>n)
    {
        ans=root;
    }
    for (int i = 0; i < root->children.size(); i++)
    {
        TreeNode<int>* temp=nextLargestEle(root->children[i], n);
        if (ans==NULL)
        {
            ans=temp;
        }
        else if (temp!=NULL && temp->data<ans->data)
        {
            ans=temp;
        }
        
    }
    return ans;
}

void helperForreplaceWithDepthValue(TreeNode<int>* root, int depth){
    root->data=depth;
    for (int i = 0; i < root->children.size(); i++)
    {
        helperForreplaceWithDepthValue(root->children[i], depth+1);
    }

}
//15 In a given Generic Tree, replace each node with its depth value.
void replaceWithDepthValue(TreeNode<int> *root){
    if (root==NULL)
    {
        return;
    }
    helperForreplaceWithDepthValue(root, 0);   
}

/*16
Given a tree, find and return the node for which sum of data of all children and 
the node itself is maximum. In the sum, data of node itself and data of immediate 
children is to be taken.
*/
void maxSumNodeHelper(TreeNode<int>* root, TreeNode<int>** resNode, int* maxsum){
    if (root == NULL)
    {
        return;
    }
    int currsum=root->data;
    for (int i = 0; i < root->children.size(); i++)
    {
        currsum+=root->children[i]->data;
        maxSumNodeHelper(root->children[i], resNode, maxsum);
    }
    if (currsum>*maxsum)
    {
        *resNode=root;
        *maxsum=currsum;
    }
    return;
}

TreeNode<int>* maxSumNode(TreeNode<int>* root){
    TreeNode<int>* resNode;
    int maxsum=0;
    maxSumNodeHelper(root, &resNode, &maxsum);
    return resNode;
}

/* 17
find and return the node with second largest value in given tree. 
Return NULL if no node with required value is present.
*/

PairClass<int>* secondLargestNodeHelper(TreeNode<int>* root){
    if (root==NULL)
    {
        PairClass<int>* ans= new PairClass<int>(NULL, NULL);
        return ans;
    }
    PairClass<int>* ans=new PairClass<int>(root, NULL);
    for (int i = 0; i < root->children.size(); i++)
    {
        PairClass<int>* childAns=secondLargestNodeHelper(root->children[i]);
        if (childAns->largest->data>ans->largest->data)
        {   
            if (childAns->secondLargest==NULL)
            {
                ans->secondLargest=ans->largest;
                ans->largest=childAns->largest;
            }
            else
            {
                if (childAns->secondLargest->data>ans->largest->data)
                {
                    ans->secondLargest=childAns->secondLargest;
                    ans->largest=childAns->largest;
                }
                else
                {
                    ans->secondLargest=ans->largest;
                    ans->largest=childAns->largest;
                }
            }
        }
        else if (ans->largest->data==childAns->largest->data && childAns->secondLargest!=NULL)
        {
            ans->secondLargest=childAns->secondLargest;
        }
        else if (ans->largest->data!=childAns->largest->data && ans->secondLargest==NULL 
        || childAns->largest->data>ans->secondLargest->data)
        {
            ans->secondLargest=childAns->largest;
        }
    }
    return ans;
}

TreeNode<int>* secondLargestNode(TreeNode<int>* root){
    return secondLargestNodeHelper(root)->secondLargest;

}


int main(){
    /*
    TreeNode<int>* root=new TreeNode<int>(1);
    TreeNode<int>* node1=new TreeNode<int>(2);
    TreeNode<int>* node2=new TreeNode<int>(3);
    root->children.push_back(node1);
    root->children.push_back(node2);
    */
    TreeNode<int>* root = takeInputLevelwise();
    printTreeLevelwise(root);
    cout<< "the total number of nodes of the given tree are: "<<countNodes(root)<<endl;
    // TreeNode<int>* ansOfMaxTreeNode=maxNode(root);
    cout<<"Sum of all Nodes: "<<sumOfNodes(root)<<endl;
    cout<<"Maximum node value of the tree is: "<<maxNode(root)->data<<endl;
    cout<<"Height of the tree is: "<<heightOfTree(root)<<endl;
    // cout<< "Nodes at Depth "<<k<< ' :'<<printdDepthKthNode(root, k)<<endl;
    cout<< "Printing nodes till 2nd Depth: "<<endl;
    printdDepthKthNode(root, 2);
    cout<<endl;
     /* 1 3 2 3 4 2 5 6 2 7 8 0 0 0 0 1 9 0 */
    cout<<"No. of leaf nodes in the tree: "<<noOfLeafNodes(root)<<endl;
    cout<<"Pre-order traversal of tree : "<<endl;
    printPreOrder(root);
    cout<<endl;
    cout<<"Post-order traversal of tree : "<<endl;
    printPostOrder(root);
    cout<<endl;
    if (nextLargestEle(root, 7)!=NULL)
    {
        cout<<"Next largest ele for 7 in tree is :"<<nextLargestEle(root, 7)->data<<endl;
    }
    else
    {
        cout<<"Next largest ele for 8 in tree is -"<<INT_MIN<<endl;
    }
    // cout<<"Replacing tree with its depth"<<endl;
    // replaceWithDepthValue(root);
    // printTreeLevelwise(root);
    cout<<"the node for which sum of data of all children is:"<<maxSumNode(root)->data<<endl;
    cout<<"2nd largest ele of the tree is- "<<secondLargestNode(root)->data<<endl;
    delete root;
    // cout<<endl;
    cout<<"Tree deleted"<<endl;
    // return 0;
}
