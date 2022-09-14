using namespace std;

#include<vector>
#include <iostream>
#include <queue>
#include<deque>

class TreeNode {
 public:
  int val { };
  TreeNode* left;
  TreeNode* right; 
  TreeNode* next;
  TreeNode(int x) {
    val = x;
    left = right = next =nullptr;
  }

};

class LevelOrderTraversal {
public:
// Time O(W * N) == O(N)    Space O(2W) == O(N)
  static  vector<vector<int>> level_traversal(TreeNode* root) { // static ::

    vector<vector<int>> result; // main vector of vectors , return type
    if(!root)
        return result;

    queue<TreeNode*> nodes_queue;
    nodes_queue.push(root);

    while(!nodes_queue.empty()) {

        int sz = nodes_queue.size();
        vector<int> level_nodes; // nodes values at this level 

            while(sz--) {

                TreeNode* current = nodes_queue.front();
                nodes_queue.pop();

                level_nodes.push_back(current->val);

                if(current->left)
                    nodes_queue.push(current->left); 
                if(current->right)
                    nodes_queue.push(current->right);
            }

        result.push_back(level_nodes); // level 'k' is done
    }
    return result;
 }

};

// Last level to be the first vector, from lowest(last level) to level 0 
/*
    append the current level nodes(vector) at the fron - push front
    == last level now at the beginning of the result/deque

*/
class ReverseLevelOrderTraversal {
public:

static  deque<vector<int>> level_traversal(TreeNode* root) { 

    deque<vector<int>> result;  // Deque

    if(!root)
        return result;

    queue<TreeNode*> nodes_queue;   
    nodes_queue.push(root);

    while(!nodes_queue.empty()) {

        int sz = nodes_queue.size();
        vector<int> level_nodes; 

            while(sz--) {

                TreeNode* current = nodes_queue.front();
                nodes_queue.pop();

                level_nodes.push_back(current->val);

                if(current->left)
                    nodes_queue.push(current->left); 
                if(current->right)
                    nodes_queue.push(current->right);

            }
        result.push_front(level_nodes); // here's the reversed traverse.. push front 
    }

    return result;
 }

};


class ZigzagTraversal {
 public:
  static vector<deque<int>> traverse(TreeNode *root) {
       vector<deque<int>> result;
    if(!root)
        return result;

    queue<TreeNode*> nodes_queue;       // NO change ,, the zigzag-ing done with the level_nodes deque
    nodes_queue.push(root);             // cuz this deque , is pushed back to the main result vector

    bool zigZag = false; // Flag

    while(!nodes_queue.empty()) {

        int sz = nodes_queue.size();
        deque<int> level_nodes;         // deque much easier than a vector

            while(sz--) {

                TreeNode* current = nodes_queue.front();
                nodes_queue.pop();

                if(zigZag)
                   level_nodes.push_front(current->val);
                else
                   level_nodes.push_back(current->val);


                if(current->left)
                    nodes_queue.push(current->left); 
                if(current->right)
                    nodes_queue.push(current->right);

            }

        result.push_back(level_nodes);
        zigZag = !zigZag; // zig ZAG -- L to R ,, R to L

    }
    return result;
 }                                         

}; 

class LevelAverage {
 public:
  static vector<double> findLevelAverages(TreeNode *root) {
    vector<double> result;
    if (!root) 
      return result;

    queue<TreeNode*> nodes_queue;
    nodes_queue.push(root);

    while(!nodes_queue.empty()) {

        int level_size = nodes_queue.size();
        int num_of_nodes = level_size;
        double level_sum { };   // keep track the sum of this level

            while(level_size--) {   

                TreeNode* current = nodes_queue.front();
                nodes_queue.pop();
                level_sum += current->val;

                if(current->left)
                    nodes_queue.push(current->left);
                if(current->right)
                  nodes_queue.push(current->right);

            }

        double avg = level_sum / num_of_nodes;
        result.push_back(avg);
    }

    return result;
  }
};

class LevelMaximum {
 public:
  static vector<double> findLevelMax(TreeNode *root) {
    vector<double> result;
    if (!root) 
      return result;

    queue<TreeNode*> nodes_queue;
    nodes_queue.push(root);

    while(!nodes_queue.empty()) {

        int level_size = nodes_queue.size();
        int level_max = nodes_queue.front()->val;   // better intialization

            while(level_size--) {   

                TreeNode* current = nodes_queue.front();
                nodes_queue.pop();

                level_max = max(level_max , current->val);

                if(current->left)
                    nodes_queue.push(current->left);
                if(current->right)
                  nodes_queue.push(current->right);

            }

        result.push_back(level_max);
    }

    return result;
  }
};

class MinimumDepth {    // == height ( 0 or 1 based)
 public:
  static int findMinDepth(TreeNode *root) {
    if(!root)   
        return 0;

    queue<TreeNode*> queue_nodes;
    queue_nodes.push(root);
    int min_depth { };     // or -1

    while(!queue_nodes.empty()) {

         min_depth++;                   //++  (1)    (2) .... STOP at level (2) we got 1st leaf 
        int sz = queue_nodes.size();

            while(sz--) {
                TreeNode* current = queue_nodes.front();
                

                if(!current->left && !current->right)
                    return min_depth;
                      
                      
                      //  min_depth++;  

                  queue_nodes.pop(); // here or before . doesn't matter

                  if(current->left)
                     queue_nodes.push(current->left);
                  if(current->right)
                     queue_nodes.push(current->right);
            }

    }
    return min_depth;
  }

}; 

class MaximumDepth {   
 public:
  static int findMaxDepth(TreeNode *root) {
    if(!root)   
        return 0;

    queue<TreeNode*> queue_nodes;
    queue_nodes.push(root);
    int max_depth { };     

    while(!queue_nodes.empty()) {

         max_depth++;                   // just keep counting till Q is empty == max height/depth
        int sz = queue_nodes.size();

            while(sz--) {
                TreeNode* current = queue_nodes.front();
      
                      
                  queue_nodes.pop(); 

                  if(current->left)
                     queue_nodes.push(current->left);
                  if(current->right)
                     queue_nodes.push(current->right);
            }

    }
    return max_depth;
  }

}; 

class LevelOrderSuccessor {   
 public:
  static TreeNode* findLevelSuccessor(TreeNode *root , int key) {
    if(!root)   
        return NULL;

    if(!root->left && !root->right)
            return NULL;

    queue<TreeNode*> queue_nodes;
    queue_nodes.push(root);

    while(!queue_nodes.empty()) {

        int levelSize = (int)queue_nodes.size();

        while(levelSize--) {
            TreeNode* temp = queue_nodes.front();

                  if(temp->left)
                     queue_nodes.push(temp->left);
                  if(temp->right)
                     queue_nodes.push(temp->right);

                   if(temp->val == key) {
                       queue_nodes.pop();
                             if(!queue_nodes.empty())
                                return queue_nodes.front();
                             else
                                return NULL;
                   }
             queue_nodes.pop();  
        }
    }
    return NULL;
  }

};
// simple

class LevelOrderSuccessor2 {   
 public:
  static TreeNode* findLevelSuccessor(TreeNode *root , int key) {
    if(!root)   
        return NULL;

    if(!root->left && !root->right)
            return NULL;

    queue<TreeNode*> queue_nodes;
    queue_nodes.push(root);

    while(!queue_nodes.empty()) {

        TreeNode* temp = queue_nodes.front();
        queue_nodes.pop();            


             if(temp->left)
                    queue_nodes.push(temp->left);
             if(temp->right)
                    queue_nodes.push(temp->right);

        if(temp->val == key)
            break;
        
    }
    if(queue_nodes.empty())
         return NULL;

    return queue_nodes.front();
  }

};
    //Level order traversal using 'next' pointer 

    // > NULL pointer < like a FLAG 

class ConnectLevelOrderSiblings {
 public:



  static void connect(TreeNode *root) {
    if (!root) 
      return;

    queue<TreeNode*> nodes_queue;
    nodes_queue.push(root);

    while(!nodes_queue.empty()) {
      int levelSize = nodes_queue.size();
            
        while(levelSize--) {
               TreeNode* current = nodes_queue.front();

                if(current->left)
                    nodes_queue.push(current->left);
                if(current->right)
                    nodes_queue.push(current->right);
    

                if(!levelSize) {    // 0
                    current->next = NULL;
                    nodes_queue.pop();
                    break;
                }
        
            nodes_queue.pop();
            current->next = nodes_queue.front();
        }
    }
  }
  
// depending on Next pointer & ------- NULL flag no QUEUE 

 static void printLevelOrder(TreeNode* root) {
    if(!root) 
        return;
    TreeNode* nextLevelRoot = root;  

    while(nextLevelRoot) {                                                           // no L or R == end of traversing !

         TreeNode* current = nextLevelRoot;           
         nextLevelRoot = NULL;                                                 //  a level  

            while(current) {
                cout << current->val << " ";                                                             // root

                     if (nextLevelRoot == nullptr) {                             // next level children   
                            if(current->left)   
                                    nextLevelRoot = current->left;              // from Left to Right to be the next root
                             else if (current->right) 
                                   nextLevelRoot = current->right;
                        }

                current = current->next;                                                                // next sibling
             }
    cout << endl;                                                                                        // !cuurent == null 
 }


}

};   

    // All , last successor -> next = null
class ConnectAllSiblings {
 public:
  static void connectAll(TreeNode *root) {
    if (!root) 
      return;

    
    queue<TreeNode*> nodes_queue;
    nodes_queue.push(root);

    while(!nodes_queue.empty()) {
        int levelSize = nodes_queue.size();

                while(levelSize--) {
                        TreeNode* current = nodes_queue.front();

                        if(current->left)
                            nodes_queue.push(current->left);
                        if(current->right)
                            nodes_queue.push(current->right);

                        if(!levelSize) {        
                            nodes_queue.pop();

                                if(nodes_queue.empty()) {
                                    current->next = NULL;
                                     break; 
                                } 
                                else {
                                    current->next = nodes_queue.front();
                                     break; 
                                }     
                        }

                        nodes_queue.pop();
                        current->next = nodes_queue.front();
                }
    }

  }
  static void connectAll_simple(TreeNode *root) {
    if (!root) 
      return;

    queue<TreeNode*> nodes_queue;
    nodes_queue.push(root);

    TreeNode* prev { },* curr { };

    while(!nodes_queue.empty()) {
        curr = nodes_queue.front();
        nodes_queue.pop();

        if(prev)                        // 1 ->2  ->3   ->4 ->5 ->6 ->7 
            prev->next = curr;
        
        prev = curr;

        if(curr->left)
            nodes_queue.push(curr->left);
         if(curr->right)
             nodes_queue.push(curr->right);
    }

}   

  static  void printAll(TreeNode* root) {
        TreeNode* traversal = root;

        while(traversal) {
            cout << traversal->val << " ";
            traversal = traversal->next;
        }
        cout << endl;
    }

}; 

class RightViewTree {
 public:
  static vector<TreeNode *> traverse(TreeNode *root) {
    vector<TreeNode *> result;
    if (!root) 
      return result;

    queue<TreeNode*> nodes_queue;
    nodes_queue.push(root);

    while(!nodes_queue.empty()) {
        int levelSize = nodes_queue.size();

            while(levelSize--) {
                TreeNode* current = nodes_queue.front();
                nodes_queue.pop();

              if(current->left)
                     nodes_queue.push(current->left);
              if(current->right)
                     nodes_queue.push(current->right);   

               if(!levelSize) { // 0 last node at this level
                result.push_back(current);
               }      

            }
    }
    return result;
}

};

class LeftViewTree {
 public:
  static vector<TreeNode *> traverse(TreeNode *root) {
    vector<TreeNode *> result;
    if (!root) 
      return result;

    queue<TreeNode*> nodes_queue;
    nodes_queue.push(root);

    while(!nodes_queue.empty()) {
        int levelSize = nodes_queue.size();
        int temp = levelSize;
        
            while(levelSize--) {
                TreeNode* current = nodes_queue.front();
                nodes_queue.pop();

              if(current->left)
                     nodes_queue.push(current->left);
              if(current->right)
                     nodes_queue.push(current->right);   

               if((levelSize + 1) == temp) { // 1 first node at this level
                result.push_back(current);
               }      

            }
    }
    return result;
  }
  
};

int main() {

/*
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);

    vector<vector<int>> test;
    test = LevelOrderTraversal::level_traversal(root);   // return 

  cout << "Level order traversal: \n";
  for (auto vec : test) {
    for (auto num : vec) {
      cout << num << " ";
    }
    cout << endl;
  } 
/*
12
7 1
9 10 5

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  TreeNode *root = new TreeNode(12);
  root->left = new TreeNode(7);
  root->right = new TreeNode(1);
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);

    deque<vector<int>> test;
    test = ReverseLevelOrderTraversal::level_traversal(root);    

  cout << "Reversed Level order traversal: \n";
  for (auto deq : test) {
    for (auto num : deq) {
      cout << num << " ";
    }
    cout << endl;
  }
/*
9 10 5 
7 1 
12 
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  TreeNode *root = new TreeNode(12);                            //   12  
  root->left = new TreeNode(7);                         //     7         1 
  root->right = new TreeNode(1);    //                      9         10     5 
  root->left->left = new TreeNode(9);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);

    vector<deque<int>> test;
    test = ZigzagTraversal::traverse(root);    

  cout << "ZigZag traversal: \n";
  for (auto vec : test) {
    for (auto num : vec) {
      cout << num << " ";
    }
    cout << endl;
  }

*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  TreeNode *root = new TreeNode(12);                            //   12  
  root->left = new TreeNode(7);                         //     7          1 
  root->right = new TreeNode(1);    //                      9    1     10     5 
  root->left->left = new TreeNode(9);
  root->left->right = new TreeNode(1);
  root->right->left = new TreeNode(10);
  root->right->right = new TreeNode(5);
  //root->right->right->right = new TreeNode(-500);
  //root->right->right->left = new TreeNode(-502);


    vector<double> test;
    test = LevelAverage::findLevelAverages(root);    

    cout << "Averages: \n";
    for (auto num : test) 
      cout << num << " ";
    cout << endl;
  
  test = LevelMaximum::findLevelMax(root);
  cout << "Maximums: \n";
    for (auto num : test) 
      cout << num << " ";

    cout << endl;
*/    
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  TreeNode *root = new TreeNode(12);                            //   12  
  root->left = new TreeNode(7);                         //     7          1 
  root->right = new TreeNode(1);    //                    9      1           0       
  root->left->left = new TreeNode(9); //                                       10
  root->left->right = new TreeNode(1);
  root->right->right = new TreeNode(0);
  root->right->right->right = new TreeNode(10);

  int minDepth = MinimumDepth::findMinDepth(root);
  cout << "Min: " << minDepth << endl;
  int maxDepth = MaximumDepth::findMaxDepth(root);
  cout << "Max: " << maxDepth << endl;
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
  TreeNode *root = new TreeNode(12);                            //   12  
  root->left = new TreeNode(7);                         //     7          1 
  root->right = new TreeNode(1);    //                    9       2          0       
  root->left->left = new TreeNode(9); //                                       10
  root->left->right = new TreeNode(2);
  root->right->right = new TreeNode(0);
  root->right->right->right = new TreeNode(10);

  TreeNode* successor = LevelOrderSuccessor::findLevelSuccessor(root , 10);

    if(!successor) 
        cout << "NULL \n";
    else 
        cout << "LevelOrderSuccessor: " << successor->val << endl; 


    TreeNode* successor2 = LevelOrderSuccessor2::findLevelSuccessor(root , 10);

    if(!successor2) 
        cout << "NULL \n";
    else 
        cout << "LevelOrderSuccessor: " << successor2->val << endl; 
*/

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*

  TreeNode *root = new TreeNode(1);          //
                                                     //         1   -> N           
                                                  //       2        3   -> N        
                                                  //   4      5   6    7   -> N      
                                                                        
                                                           
  root->left = new TreeNode(2);                         
  root->right = new TreeNode(3);       
  root->left->left = new TreeNode(4); 
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);
  root->right->right->right = new TreeNode(70);
  root->right->right->right->right = new TreeNode(700);
  root->right->right->right->left = new TreeNode(-1);

    ConnectLevelOrderSiblings::connect(root);
    cout << "Level order traversal using 'next' pointer: " << endl;
    ConnectLevelOrderSiblings::printLevelOrder(root);

*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
          /*
                                                              1             
                                                         2        3           
                                                     4      5   6    7       
                                                                        
 */
/*
  TreeNode *root = new TreeNode(1);              
  root->left = new TreeNode(2);                         
  root->right = new TreeNode(3);       
  root->left->left = new TreeNode(4); 
  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);
   
    ConnectAllSiblings::connectAll(root);
    cout << "Level order traversal using 'next' pointer: " << endl;
    ConnectAllSiblings::printAll(root);
   if(!root->right->right->next) 
        cout << "NULL\n";
*/
        /*          12
                7       1
            9        10   5  
        
        */
/*
  TreeNode *test = new TreeNode(12);
  test->left = new TreeNode(7);
  test->right = new TreeNode(1);
  test->left->left = new TreeNode(9);
  test->right->left = new TreeNode(10);
  test->right->right = new TreeNode(5);

    //ConnectAllSiblings::connectAll(test);
    ConnectAllSiblings::connectAll_simple(test);

  cout << "Level order traversal using 'next' pointer: " << endl;
    ConnectAllSiblings::printAll(test);
   if(!test->right->right->next) 
        cout << "NULL\n";
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

          /*
                                                              1             
                                                         2        3           
                                                     4      5   6    7       
                                                                        
 */
/*
  TreeNode *root = new TreeNode(1);              
  root->left = new TreeNode(2);                         
  root->right = new TreeNode(3);       
  root->left->left = new TreeNode(4); 
  root->left->left->left = new TreeNode(-555); 

  root->left->right = new TreeNode(5);
  root->right->left = new TreeNode(6);
  root->right->right = new TreeNode(7);
  root->right->right->right = new TreeNode(-777);

    vector<TreeNode*> vec = RightViewTree::traverse(root);
    cout << "Right View of a Binary Tree: " << endl;

    for(auto x : vec) {
        cout << x->val << " "; 
    }
    cout << endl;

    vector<TreeNode*> vect = LeftViewTree::traverse(root);
    cout << "Left View of a Binary Tree: " << endl;

    for(auto x : vect) {
        cout << x->val << " "; 
    }
    cout << endl;


*/

// DONE

    return 0;
}