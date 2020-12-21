# Assignment

Add Inputs:
==========
Add Inputs to "input.txt" file.

To Run the Program:
==================
Command = "g++ solution.cpp; ./a.out"


DataStructure used:
==================
typedef struct Node                                                                                 
{                                                                                                   
    Node *left;                                                                                     
    Node *right;                                                                                    
    int type;                                                                                       
    int data;                                                                                       
    string scale;                                                                                   
}Node;                                                                                              
       
The type of Node - either Scale or a Mass is kept as an element in structure for easy manipulation.

Logic:
==================

Value Population
----------------
First, from the given values, all the Scale mappings are retreived (a Map with Key as Scale-names and values as Vector of left and right elements). 

Then, the tree is formed from the Map values (populate() API). 

Find the Balance for the Tree:
-----------------------------
Then the Balance() API is used to find the values at each Node to make it balanced. 

Printing the solution:
----------------------
Again an Ordered-Map is created (with key as Scale-names and values as Vector of left and right elements).
An Ordered-Map is required since the output is required in Alphabetical order. 



