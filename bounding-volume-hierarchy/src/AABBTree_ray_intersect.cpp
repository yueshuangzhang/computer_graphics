#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////

  if (ray_intersect_box(ray, this->box, min_t, max_t)){

    // store return value
    double left_t, right_t;
    std::shared_ptr<Object> left_tree, right_tree;

    bool left_hit, right_hit;

    // determine whether the ray hit the left tree or right tree
    left_hit = (this->left != NULL) && this->left->ray_intersect(ray, min_t, max_t, left_t, left_tree);
    right_hit = (this->right != NULL) && this->right->ray_intersect(ray, min_t, max_t, right_t, right_tree);

    // hit both, take min t
    if (left_hit && right_hit){
      if(left_t < right_t){
        t = left_t;
        descendant = left_tree; 
      }else{
        t = right_t;
        descendant = right_tree; 
      }
    }else if (!left_hit && !right_hit){
      return true;
    }else if (left_hit && !right_hit){
      t = left_t;
      descendant = left_tree; 
    }else if (right_hit && !left_hit){ 
      t = right_t;
      descendant = right_tree; 
    }
    return true;
  }

  // not hit
  return false;
  ////////////////////////////////////////////////////////////////////////////
}

