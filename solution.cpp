#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <cstdlib>
#include <cstdio>
#include <fstream>
using namespace std;

#define SCALE 1
#define MASS  2

//Node structure
typedef struct Node
{
    Node *left;
    Node *right;
    int type;
    int data;
    string scale;
}Node;

//API - Print the Tree
void printTree(Node *root)
{
    if(root != NULL)
    {   
        if(root->type == MASS)  
            cout<<root->data<<endl;
        else
            cout<<root->scale<<endl;

        printTree(root->left);
        printTree(root->right);
    }
}


//API - Allocation for Nodes
Node* alloc(int type, int d, string s)
{
    Node* root = new Node;
    root->type = type;
    if(type == MASS) {
        root->data = d;            
        root->scale = "";
    }        
    else {
        root->scale = s;
        root->data = 0;            
    }        
    root->left = NULL;
    root->right = NULL;
    return root;
}

//API - Balance the Tree with scales
int balance(Node *root, map<string, vector<int> > &ord_map)
{
    if(root == NULL)
        return 0;
    if((root->left == NULL) && (root->right == NULL))        
    {
        return  root->data;
    }
    int S1 = balance(root->left, ord_map);
    int S2 = balance(root->right, ord_map);
    int val = 0;

    if(S1 == S2)
    {
        vector<int> V;
        V.push_back(0);
        V.push_back(0);
        ord_map[root->scale] = V;
    }
    else if(S1 > S2)
    {
        val = S1 - S2;
        vector<int> V;
        V.push_back(0);
        V.push_back(val);
        ord_map[root->scale] = V;
    }
    else
    {
        val = S2 - S1;
        vector<int> V;
        V.push_back(val);
        V.push_back(0);
        ord_map[root->scale] = V;
    }
    return (S1+S2+val+1);
}

//API - Populate the Nodes in Tree
void populate(map<string, vector<string> > map1, Node **root)
{
    Node *p = *root;
    if(p->type != SCALE)
    {
        return;
    }        

    vector<string> v1 = map1[p->scale];
    string s = v1[0];
    if(isdigit(s[0])) {
        int val;
        sscanf(s.c_str(), "%d", &val);
        p->left = alloc(MASS, val, "");
    }
    else {
        p->left = alloc(SCALE, 0, s);
    }
    s = v1[1];
    if(isdigit(s[0])) {
        int val;
        sscanf(s.c_str(), "%d", &val);
        p->right = alloc(MASS, val, "");
    }
    else {
        p->right = alloc(SCALE, 0, s);
    }
    populate(map1, &(p->left));
    populate(map1, &(p->right));
}


int main()
{
    int i = 0;
    map<string, vector<string> > map1;

    ifstream iFile("input.txt");    
    while (true) {
        string line;
        iFile >> line;
        if( iFile.eof() ) break;
        vector<string> v;
        stringstream ss(line);
        while (ss.good()) {
            string substr;
            getline(ss, substr, ',');
            v.push_back(substr);
        }

        vector<string> tt;
        tt.push_back(v[1]);
        tt.push_back(v[2]);

        map1[v[0]] = tt; 
    }

    //Received values from stdin
    cout<<endl<<"RECEIVED VALUES"<<endl;
    cout<<"=========================================="<<endl;
    for(map<string, vector<string> >::const_iterator it = map1.begin(); it != map1.end(); ++it)
    {
        std::cout <<it->first << "-> ";
        vector<string> v1 = it->second;
        std::cout << v1[0] << " " <<v1[1]<<endl;
    }
    cout<<"=========================================="<<endl<<endl;

    Node *root = NULL;
    map<string, vector<string> >::const_iterator it = map1.begin();
    root = alloc(SCALE, 0, it->first);

    vector<string> v1 = it->second;
    string s = v1[0];
    if(isdigit(s[0])) {
        int val;    
        sscanf(s.c_str(), "%d", &val);
        root->left = alloc(MASS, val, "");
    }
    else {
        root->left = alloc(SCALE, 0, s);
    }
    s = v1[1];
    if(isdigit(s[0])) {
        int val;    
        sscanf(s.c_str(), "%d", &val);
        root->right = alloc(MASS, val, "");
    }            
    else {
        root->right = alloc(SCALE, 0, s);
    }

    populate(map1, &(root->left));
    populate(map1, &(root->right));

    map<string, vector<int> >ord_map;
    balance(root, ord_map);
    cout<<endl<<"SOLUTION"<<endl;
    cout<<"=========================================="<<endl;
    for(map<string, vector<int> >::const_iterator it = ord_map.begin(); it != ord_map.end(); ++it)
    {
        std::cout <<it->first << "-> ";
        vector<int> v1 = it->second;
        std::cout << v1[0] << " " <<v1[1]<<endl;
    }
    cout<<"=========================================="<<endl<<endl;

    iFile.close();
}
