#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <vector>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // the level 0 is the root of the tree, and inserted to the lef of the node
  // Book p 304-305
  // the number of child is the num_leaves
  if (num_leaves == 0){
    this->left = NULL;
    this->right = NULL;

  } else if (num_leaves == 1){
    this->left = objects[0];
    insert_box_into_box(objects[0]->box, this->box);
  } else if (num_leaves == 2){
    this->left = objects[0];
    this->right = objects[1];
    insert_box_into_box(objects[0]->box, this->box);
    insert_box_into_box(objects[1]->box, this->box);
  } else{

    // Find the midpoint m of the bounding box of objects along axis
    int axis = -1;
    double max_distance = -1;
    double m = -1;

    for (int i = 0; i < 3; i++){
      double distance = abs(this->box.max_corner[i] - this->box.min_corner[i]);
      if (distance > max_distance){
        max_distance = distance;
        axis = i;
      }
    }

    if(axis != -1 && max_distance != -1){
      // define the midpoint
      m = (box.max_corner[axis] - box.min_corner[axis]) / 2;
    }

    //partition objects into list with length k and (numleaves - k) surrounding m
    std::vector<std::shared_ptr<Object>> left_objects;
    std::vector<std::shared_ptr<Object>> right_objects;
    for (int i = 0; i < num_leaves; i++){
      //objects[i]->box.center()[axis]
      if (i < m){
        left_objects.push_back(objects[i]);
      }
      else{
        right_objects.push_back(objects[i]);
      }
    }
    // left = new bvh-node(object[0-k], (axis+1)%3)
    this->left = std::make_shared<AABBTree>(left_objects, a_depth+1);

    // right = new bvh-node(object[k+1 to numleaves], (axis+1)%3)
    this->right = std::make_shared<AABBTree>(right_objects, a_depth+1);
    
    //bbox = combine left->bbox, right->bbox
    // insert_box_into_box(objects[0]->box, this->box);
    // insert_box_into_box(objects[1]->box, this->box);

  }
  ////////////////////////////////////////////////////////////////////////////
}
