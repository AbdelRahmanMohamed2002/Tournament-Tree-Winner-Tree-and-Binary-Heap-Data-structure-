#include "Tournmenttree.h"
#include <list>
using namespace std;

#define COUNT 10

// Tournament Tree node
struct Tournamenttree::Node
{
    int idx;
    Node* left, * right;
};

// Utility function to create a tournament tree node
Tournamenttree::Node* Tournamenttree::createNode(int idx)
{
    Node* t = new Node;
    t->left = t->right = NULL;
    t->idx = idx;
    return t;
}

void Tournamenttree::print2DUtil(Node* root, int space, int ar[])
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space, ar);

    // Print current node after space
    // count
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << "  ";
    cout << "Player " << (root->idx) + 1 << "\n";

    for (int i = COUNT; i < space; i++)
        cout << "  ";
    cout << "   (" << ar[root->idx] << ")";

    // Process left child
    print2DUtil(root->left, space, ar);
    cout << "\n";
}

// Wrapper over print2DUtil()
void Tournamenttree::print2D(Node* root, int ar[])
{
    // Pass initial space count as 0
    print2DUtil(root, 0, ar);
}

// Creates and sorts tree automatically using array values
void Tournamenttree::TreeMaker(int arr[], int n, Node*& nptr, char choice)
{
    // Create a list to store nodes of current level
    list<Node*> li;

    //Creates Node Pointer "root" without a value
    Node* root = NULL;

    for (int i = 0; i < n; i += 2)  //Loop
    {
        //Creates Node Pointer "t1" points at a new node with index (i)
        Node* t1 = createNode(i);

        //Creates Node Pointer "t2" and initiallizes it with NULL
        Node* t2 = NULL;

        //if next in array is less than array size
        if (i + 1 < n)
        {
            // Make a node for next element
            t2 = createNode(i + 1);

            // (>The comparison that determines the winner in the external level<)
            // Make root = smaller between (arr[i]) and (arr[i + 1])

            switch (choice)
            {
            case'+':
                root = (arr[i] > arr[i + 1]) ? createNode(i) : createNode(i + 1);
                break;
            case'-':
                root = (arr[i] < arr[i + 1]) ? createNode(i) : createNode(i + 1);
            }

            //root = (arr[i] < arr[i + 1]) ? createNode(i) : createNode(i + 1);

            // Make two nodes as children of smaller node (root)
            root->left = t1;
            root->right = t2;

            // Add root
            li.push_back(root);
        }
        else
            li.push_back(t1);
    }

    int lsize = li.size();

    // Construct the complete tournament tree
    // prepared list of winners in first round.
    while (lsize != 1)
    {
        // Find index of last pair
        int last = (lsize & 1) ? (lsize - 2) : (lsize - 1);

        // Process current list items in pair
        for (int i = 0; i < last; i += 2)
        {
            // Extract two nodes from list
            Node* f1 = li.front();
            li.pop_front();

            Node* f2 = li.front();
            li.pop_front();

            // (>The comparison that determines the winner in the internal level<)
            // create a new node with index of the smaller between (arr[f1->idx]) and (arr[f2->idx])

            switch (choice)
            {
            case'+':
                root = (arr[f1->idx] > arr[f2->idx]) ? createNode(f1->idx) : createNode(f2->idx);
                break;
            case'-':
                root = (arr[f1->idx] < arr[f2->idx]) ? createNode(f1->idx) : createNode(f2->idx);
            }

            //root = (arr[f1->idx] > arr[f2->idx]) ? createNode(f1->idx) : createNode(f2->idx);

            // Make winner as parent of two
            root->left = f1;
            root->right = f2;

            // Add winner to list of next level
            li.push_back(root);
        }
        if (lsize & 1)
        {
            li.push_back(li.front());
            li.pop_front();
        }
        lsize = li.size();
    }

    cout << "\nWinner: Player " << (root->idx) + 1 << ", with score: " << arr[root->idx] << endl;
    nptr = root;
}

// Main Function
int main()
{
    int n; char choice;

    cout << "Enter the number of players: "; cin >> n;
    while (n <= 1)
    {
        cout << "*****************************No. of players cannot be Zero or Negative!***************************** \n\n";
        cout << "                                                  &                                                    \n\n";
        cout << "********************************No. of players cannot be less than 2******************************** \n\n";

        cout << "Please ReEnter the number of players: "; cin >> n; cout << "\n";
    }
    int* arr = new int[n];

    cout << "\nChoose the winning condition \n'+' for Player with Max Score or '-' for Player with Min Score: "; cin >> choice;
    while (choice != '+' && choice != '-')
    {
        cout << "**Invalid Input!** \n\n";
        cout << "Please only enter '+' or '-': "; cin >> choice; cout << "\n";
    }
    cout << "Choice: " << choice << "\n";
    cout << "__\n\n";
    if (choice == '+')
        cout << "**!Winner is the player with the Most score!**\n";
    else if (choice == '-')
        cout << "**!Winner is the player with the Least score!**\n";
    cout << "__\n\n";

    for (int i = 0; i < n; i++)
    {
        cout << "Enter player " << i + 1 << "'s score: (POSITIVE ONLY): "; cin >> arr[i];
        while (arr[i] < 0)
        {
            cout << "enter a postive number" << endl;
            cin >> arr[i];
        }
    }

    Tournamenttree::Node* root;
    Tournamenttree::TreeMaker(arr, n, root, choice);// <- "root" will be taken as reference and will be returned pointing at the actual root node


    Tournamenttree::print2D(root, arr);

}