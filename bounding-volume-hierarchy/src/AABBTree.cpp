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
    this->right = NULL;
    insert_box_into_box(objects[0]->box, this->box);
  } else if (num_leaves == 2){
    this->left = objects[0];
    this->right = objects[1];
    insert_box_into_box(objects[0]->box, this->box);
    insert_box_into_box(objects[1]->box, this->box);
  } else{

    // build the box
    for (int i = 0; i < num_leaves; i++){
      insert_box_into_box(objects[i]->box, this->box);
    }

    // Find the midpoint m of the bounding box of objects along axis
    int axis = -1;
    double max_distance = -1;
    double x_dis, y_dis, z_dis;

    double m = -1;

    x_dis = this->box.max_corner[0] - this->box.min_corner[0];
    y_dis = this->box.max_corner[1] - this->box.min_corner[1];
    z_dis = this->box.max_corner[2] - this->box.min_corner[2];

    max_distance = fmax(fmax(x_dis, y_dis),z_dis);
    if (max_distance == x_dis){axis = 0;}
    else if (max_distance == y_dis){axis = 1;}
    else if (max_distance == z_dis){axis = 2;}

    if(axis != -1 && max_distance != -1){
      // define the midpoint
      m = (box.max_corner[axis] + box.min_corner[axis]) / 2;
    }

    //partition objects into list with length k and (numleaves - k) surrounding m
    std::vector<std::shared_ptr<Object>> left_objects;
    std::vector<std::shared_ptr<Object>> right_objects;
    for (int i = 0; i < num_leaves; i++){
      // use m as a divider
        if (objects[i]->box.center()[axis] < m){
          left_objects.push_back(objects[i]);
        }
        else{
          right_objects.push_back(objects[i]);
        }
    }

    // if the tree is not balance
    if(left_objects.size()==0){
      for (int i = 0; i < right_objects.size() / 2; i++) {
        left_objects.push_back(right_objects.back());
        right_objects.pop_back();
      }
    }else if (right_objects.size()==0){
      for (int i = 0; i < left_objects.size() / 2; i++) {
        right_objects.push_back(right_objects.back());
        left_objects.pop_back();
      }
    }

    // left = new bvh-node(object[0-k], (axis+1)%3, not used ere)
    this->left = std::make_shared<AABBTree>(left_objects, a_depth+1);

    // right = new bvh-node(object[k+1 to numleaves], (axis+1)%3)
    this->right = std::make_shared<AABBTree>(right_objects, a_depth+1);

  }
  ////////////////////////////////////////////////////////////////////////////
}
