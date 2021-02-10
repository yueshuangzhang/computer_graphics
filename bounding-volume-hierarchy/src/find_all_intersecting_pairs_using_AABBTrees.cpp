#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  ////////////////////////////////////////////////////////////////////////////
  // make sure
  if (leaf_pairs.size() > 0){
    leaf_pairs.clear();
  }

  std::list<std::pair<std::shared_ptr<Object>, std::shared_ptr<Object> >> queue;
  std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> node_pair;
  std::shared_ptr<Object> node_A, node_B;
  std::shared_ptr<AABBTree> tree_A, tree_B;
  if (box_box_intersect(rootA->box, rootB->box)){
    queue.push_back(std::make_pair(rootA, rootB));
  }else{
    return;
  }

  while (!queue.empty()) {
    // triverse from the end of the tree
    // get the 2 tree node
    node_pair = queue.front();
    queue.pop_front();
    node_A = node_pair.first;
    node_B = node_pair.second;
    
    tree_A = std::dynamic_pointer_cast<AABBTree>(node_A);
    tree_B = std::dynamic_pointer_cast<AABBTree>(node_B);

    // both tree_A and tree_B are leaves
    if ((tree_A == NULL) && (tree_B == NULL)){
      leaf_pairs.push_back(std::make_pair(node_A, node_B));
    }
    //only A is leave
    else if (tree_A == NULL){
      if (box_box_intersect(node_A->box, tree_B->left->box)){
        queue.push_back(std::make_pair(node_A, tree_B->left));
      }
      if (box_box_intersect(node_A->box, tree_B->right->box)){
        queue.push_back(std::make_pair(node_A, tree_B->right));
      }
    }
    //only B is leave
    else if (tree_B == NULL){
      if (box_box_intersect(tree_A->left->box, node_B->box)){
        queue.push_back(std::make_pair(tree_A->left, node_B));
      }
      if (box_box_intersect(tree_A->right->box, node_B->box)){
        queue.push_back(std::make_pair(tree_A->right, node_B));
      }
    }
    //either is leaves
    else{
      //if tree a left intersect with tree b left
      if(box_box_intersect(tree_A->left->box, tree_B->left->box)){
          queue.push_back(std::make_pair(tree_A->left, tree_B->left));
      }
      //if tree a left intersect with tree b left
      if(box_box_intersect(tree_A->left->box, tree_B->right->box)){
          queue.push_back(std::make_pair(tree_A->left, tree_B->right));
      }
      //if tree a left intersect with tree b left
      if(box_box_intersect(tree_A->right->box, tree_B->right->box)){
          queue.push_back(std::make_pair(tree_A->right, tree_B->right));
      }
      //if tree a left intersect with tree b left
      if(box_box_intersect(tree_A->right->box, tree_B->left->box)){
          queue.push_back(std::make_pair(tree_A->right, tree_B->left));
      }
    }
  }

  ////////////////////////////////////////////////////////////////////////////
}
