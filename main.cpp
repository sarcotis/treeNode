/* 
 * BINARY SEARCH TREE PROJECT  
 Sarah Cotis
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class TreeNode {
public:
    TreeNode* parent;
    TreeNode* childL;
    TreeNode* childR;
    string PurseBrand;
    int price;

    TreeNode(string purse, int prc, TreeNode* p)
        //Shorthand to input values to members
        :PurseBrand(purse), price(prc), parent(p)
    {
        //set children to nullptrs by default
        childL = nullptr;
        childR = nullptr;
    }
};
//Globals for use in main() later
TreeNode* evTree;
TreeNode* testNode = new TreeNode("Coach", 1200, nullptr);


void recursiveWalk(TreeNode* fendi)
{
    if (fendi != nullptr)
    {
        recursiveWalk(fendi->childL);
        cout << fendi->PurseBrand << "\n";
        recursiveWalk(fendi->childR);
    }
}

TreeNode* insertNode(TreeNode* tree, TreeNode* bauble = nullptr)
{
    //Create the node to be added
    //The node is referred to as "bauble" because you hang baubles on trees or something
    if (bauble == nullptr)
    {
        string purseBrand;
        int price;
        cout << "\nEnter the Purse Brand:-->\n";
        cin >> purseBrand;
        cout << "\nEnter the purse's price:-->\n";
        cin >> price;
        bauble = new TreeNode(purseBrand, price, nullptr);
    }
    //The Algorithm™

    //If the tree is empty, insert the node as the root
    if (tree == nullptr)
    {
        tree = bauble;
    }

    else
    {
    compare:
        //st1.compare(st2) outputs -1 if st2 is earlier alphabetically than st1, 
        //                          1 if later, 
        //                          0 if they are the same.
        int comparison = bauble->PurseBrand.compare(tree->PurseBrand);
        switch (comparison)
        {
            //If bauble is earlier in the alphabet than tree, 
            //Check Tree's left node for a nullptr
        case -1:
            //If the node's left child is a nullptr,
            //set the node to the child of the node
            if (tree->childL == nullptr)
            {
                tree->childL = bauble;
                bauble->parent = tree;
                cout << "Node successfully inserted as the left child of " << tree->PurseBrand << "\n";
                break;
            }
            //Otherwise, set the check node nown a level and try again
            else
            {
                tree = tree->childL;
                goto compare;
            }
            //If bauble is later in the alphabet than tree, 
            //Check Tree's right node for a nullptr
        case 1:
            //If the node's left child is a nullptr,
            //set the node to the child of the node
            if (tree->childR == nullptr)
            {
                tree->childR = bauble;
                bauble->parent = tree;
                cout << "Node successfully inserted as the right child of " << tree->PurseBrand << "\n";
                break;
            }
            //Otherwise, set the check node nown a level and try again
            else
            {
                tree = tree->childR;
                goto compare;
            }
            //If the nodes are the same, do not insert the node.
        case 0:
            cout << "Node already in tree. \n";
            break;

        }
    }
    //iterate back to the root of the modified tree before returning the tree
    while (tree->parent != nullptr)
    {
        tree = tree->parent;
    }
    //Return the modified tree
    return tree;
}

//deleting nodes here

TreeNode* deleteNode(TreeNode* tree)
{
    TreeNode* slated = nullptr;

    //Ask for a node to be deleted
    //look for said node
    //set slated to that node
    string check;
    int comparitor;
    cout << "What node do you want to delete? (cAsE sEnSiTiVe, no_spaces)\n";
    cin >> check;

    //Look for the node in the tree with the same name as the string
navigate1:
    comparitor = check.compare(tree->PurseBrand);
    switch (comparitor)
    {
        //If the search term is less than the currently observed node
    case -1:
        //If the search ends with no node of the same name
        if (tree->childL == nullptr)
        {
            cout << "Could not find the node you are looking for.\nNo node will be deleted.\n";
            //Iterate back to the top of the tree and exit
            while (tree->parent != nullptr)
            {
                tree = tree->parent;
            }
            return tree;
        }
        //Otherwise descend a level
        else
        {
            tree = tree->childL;
            goto navigate1;
        }
        //If the search term is more than the currently observed node
    case 1:
        //If the search ends with no node of the same name
        if (tree->childR == nullptr)
        {
            cout << "Could not find the node you are looking for.\nNo node will be deleted.\n";
            //Iterate back to the top of the tree and exit
            while (tree->parent != nullptr)
            {
                tree = tree->parent;
            }
            return tree;
        }
        //Otherwise descend a level
        else
        {
            tree = tree->childR;
            goto navigate1;
        }
        //When it finds a node of the same name
    case 0:
        slated = tree;
        break;
    }
    //navigate back to the top of the tree
    while (tree->parent != nullptr)
    {
        tree = tree->parent;
    }

    TreeNode* orphanL;
    orphanL = slated->childL;
    TreeNode* orphanR;
    orphanR = slated->childR;
    bool orphanLIsNull = false;
    bool orphanRIsNull = false;
    if (orphanL == nullptr) { orphanLIsNull = true; }
    if (orphanR == nullptr) { orphanRIsNull = true; }

    //Decide which node to remove
    tree = slated->parent;
    bool directionIsL;
    if (slated->PurseBrand.compare(tree->PurseBrand) == -1)
    {
        directionIsL = true;
    }
    else if (slated->PurseBrand.compare(tree->PurseBrand) == 1)
    {
        directionIsL = false;
    }
    //if slated has no children:
    if (orphanLIsNull && orphanRIsNull)
    {
        //Depending on which side slated is on, set nullptrs accordingly
        if (directionIsL)
        {
            tree->childL = nullptr;
        }
        else if (!directionIsL)
        {
            tree->childR = nullptr;
        }
    }
    //If slated has a left child
    else if (!orphanLIsNull && orphanRIsNull)
    {
        //depending on which side slated is on, link left orphan to parent
        if (directionIsL)
        {
            tree->childL = orphanL;
        }
        else if (!directionIsL)
        {
            tree->childR = orphanL;
        }
    }
    //if slated has a right child
    else if (orphanLIsNull && !orphanRIsNull)
    {
        //depending on which side slated is on, link right orphan to parent
        if (directionIsL)
        {
            tree->childL = orphanR;
        }
        else if (!directionIsL)
        {
            tree->childR = orphanR;
        }
    }
    //if slated has two children
    else if (!orphanLIsNull && !orphanRIsNull)
    {
        //nullify the slated node as above
        if (directionIsL)
        {
            tree->childL = nullptr;
        }
        else if (!directionIsL)
        {
            tree->childR = nullptr;
        }
        //Insert the two orphan nodes back into the tree
        while (tree->parent != nullptr)
        {
            tree = tree->parent;
        }
        insertNode(tree, orphanL);
        insertNode(tree, orphanR);
    }
    //navigate back to the top of the tree
    while (tree->parent != nullptr)
    {
        tree = tree->parent;
    }
    return tree;
}

void buildTree()
{

    TreeNode* node = new TreeNode("Gucci", 1350, nullptr);
    evTree = node;
   

    TreeNode* tempParent = evTree; 
    node = new TreeNode("Louis Vuitton", 3375, tempParent);
    tempParent->childL = node;
   
    node = new TreeNode("Burberry", 1095, tempParent);
    tempParent->childR = node;
  
    tempParent = tempParent->childL; 
    node = new TreeNode("Chanel", 6050, tempParent);
    tempParent->childL = node;
   
    node = new TreeNode("Chloe", 2250, tempParent);
    tempParent->childR = node;
   
    tempParent = tempParent->childL;
    node = new TreeNode("BVLGari", 2600, tempParent);
    tempParent->childR = node;
    
    tempParent = tempParent->parent;
    tempParent = tempParent->parent;
    tempParent = tempParent->childR;

    node = new TreeNode("Coach", 1550, tempParent);
    tempParent->childL = node;
   

    node = new TreeNode("Dkny", 850, tempParent);
    tempParent->childR = node;
    

    tempParent = tempParent->childL;
    node = new TreeNode("Kate Spade", 1795, tempParent);
    tempParent->childL = node;

    tempParent = tempParent->parent;
    tempParent = tempParent->childR;
    node = new TreeNode("Armani", 1450, tempParent);
    tempParent->childL = node;
   

    cout << "Base tree initialized with 10 nodes.\n";

}

//main

int main()
{
    buildTree();
    cout << "\n";
    recursiveWalk(evTree);
    evTree = insertNode(evTree);
    evTree = insertNode(evTree, testNode);
    cout << "\n";
    recursiveWalk(evTree);
    evTree = deleteNode(evTree);
    cout << "\n";
    recursiveWalk(evTree);
}