#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue
#include <utility>

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  // build the comparator to use in priority queue
  struct comparator {
    bool operator() (std::pair<double, std::shared_ptr<Object>>& pair_1, std::pair<double, std::shared_ptr<Object>>& pair_2) const
    {
      return pair_1.first > pair_2.first;
    }
  };
    std::priority_queue<std::pair<double, std::shared_ptr<Object>>, std::vector<std::pair<double, std::shared_ptr<Object>>>, comparator> queue;
  // insert root into queue
  queue.push(std::make_pair(point_box_squared_distance(query, root->box), root));
  
  // define variable to use
  double distance, min_distance;
  min_distance = std::numeric_limits<double>::infinity();

  while (!queue.empty()) {
    std::pair<double, std::shared_ptr<Object>> top = queue.top();
    queue.pop();

    // get the content in the pair
    double distance= top.first;
    std::shared_ptr<AABBTree> tree = std::dynamic_pointer_cast<AABBTree>(top.second);
      
      if (tree) {
        // add subtree to the queue if not null
        //if the left sub tree is not empty
        if (tree->left) {
          distance = point_box_squared_distance(query, tree->left->box);
          if (distance <= max_sqrd){
            // new node for left sub tree
            queue.push(std::make_pair(distance, tree->left));
          }
        }
        // if the right sub tree is not empty
        if (tree->right) {
          distance = point_box_squared_distance(query, tree->right->box);
          if (distance <= max_sqrd){
            // new node for right sub tree
            queue.push(std::make_pair(distance, tree->right));
          }
        }
      }
      else{ // it the tree has no subtrees, leaf node
        if (distance >= min_sqrd) {
          sqrd = distance;
          descendant = top.second;
          //end of search
          return true;
        }
      }
    }
  }
  // queue empty before finding any object
  return false;
}
