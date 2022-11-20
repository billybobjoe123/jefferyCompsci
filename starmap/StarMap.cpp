#include "StarMap.h"
#include <cmath>
#include<bits/stdc++.h> 
Entry::Entry(Star star, Entry* parent, Entry* left, Entry* right) {
  this->star = star;
  this->parent = parent;
  this->left = left;
  this->right = right;
}
Entry::Entry(Star star) {
  this->star = star;
  this->parent = nullptr;
  this->left = nullptr;
  this->right = nullptr;
}
Entry::~Entry() {
  delete left;
  delete right;
}


KDtree::KDtree() {
  mRoot = nullptr;
}
KDtree::~KDtree() {
  delete mRoot;
}
size_t KDtree::push(Entry* entry) { //if code doesn't work later, CHECK THIS
  Entry* ptr = mRoot;
  if(!ptr) {
    mRoot = entry;
    mRoot->parent = nullptr;
    mRoot->left = nullptr;
    mRoot->right = nullptr;
    mRoot->level = 0;
    return 1;
  }
  while(ptr) {
    if(ptr->star.x == entry->star.x && ptr->star.y == entry->star.y && ptr->star.z == entry->star.z) {
      break;
    }
    if(ptr->level % 3==0) { //x
      if (entry->star.x<=ptr->star.x) {
        if(ptr->left) {
          ptr = ptr->left;
        }
        else {
          ptr->left = entry;
          ptr->left->level = ptr->level + 1;
          ptr->left->parent = ptr;
          ptr->left->left = nullptr;
          ptr->left->right = nullptr;
          return 1;
        }
      }
      else if (entry->star.x>ptr->star.x) {
        if(ptr->right) {
          ptr = ptr->right;
        }
        else {
          ptr->right = entry;
          ptr->right->level = ptr->level + 1;
          ptr->right->parent = ptr;
          ptr->right->left = nullptr;
          ptr->right->right = nullptr;
          return 1;
        }
      }
    }
    else if(ptr->level % 3==1) { //y
      if (entry->star.y<=ptr->star.y) {
        if(ptr->left) {
          ptr = ptr->left;
        }
        else {
          ptr->left = entry;
          ptr->left->level = ptr->level + 1;
          ptr->left->parent = ptr;
          ptr->left->left = nullptr;
          ptr->left->right = nullptr;
          return 1;
        }
      }
      else if (entry->star.y>ptr->star.y) {
        if(ptr->right) {
          ptr = ptr->right;
        }
        else {
          ptr->right = entry;
          ptr->right->level = ptr->level + 1;
          ptr->right->parent = ptr;
          ptr->right->left = nullptr;
          ptr->right->right = nullptr;
          return 1;
        }
      }
    }
    else if(ptr->level % 3 ==2) { //z
      if (entry->star.z<=ptr->star.z) {
        if(ptr->left) {
          ptr = ptr->left;
        }
        else {
          ptr->left = entry;
          ptr->left->level = ptr->level + 1;
          ptr->left->parent = ptr;
          ptr->left->left = nullptr;
          ptr->left->right = nullptr;
          return 1;
        }
      }
      else if (entry->star.z>ptr->star.z) {
        if(ptr->right) {
          ptr = ptr->right;
        }
        else {
          ptr->right = entry;
          ptr->right->level = ptr->level + 1;
          ptr->right->parent = ptr;
          ptr->right->left = nullptr;
          ptr->right->right = nullptr;
          return 1;
        }
      }
    }
  }
  return 0;
}
Entry* KDtree::closest(Entry* e1, Entry* e2, float x, float y, float z) {
  bool comparison = pow(e1->star.x - x,2)+pow(e1->star.y-y,2)+pow(e1->star.z - z,2) < pow(e2->star.x - x,2)+pow(e2->star.y - y,2)+pow(e2->star.z - z,2);
  if (comparison) {
    return e1;
  }
  return e2;
}
Entry* KDtree::nearestNeighbor(Entry* root, std::priority_queue<wrap> *neighbor, size_t n,float x, float y, float z) { //if there are errors, this one is probably wrong as well
  if(!root) {
    return nullptr;
  }
  float rootcompareval;
  float targetcompareval;
  Entry* nextBranch = nullptr;
  Entry* otherBranch = nullptr;
  if(root->level%3 == 0) {
    rootcompareval = root->star.x;
    targetcompareval = x;
  }
  else if(root->level%3 == 1) {
    rootcompareval = root->star.y;
    targetcompareval = y;
  }
  else if(root->level%3 == 2) {
    rootcompareval = root->star.z;
    targetcompareval = z;
  }
  if(targetcompareval<=rootcompareval) {
    nextBranch = root->left;
    otherBranch = root->right;
  }
  else {
    nextBranch = root->right;
    otherBranch = root->left;
  }
  Star star = root->star;
  wrap w;
  w.star = star;
  w.score = pow(root->star.x - x,2) + pow(root->star.y - y,2) + pow(root->star.z - z,2);
  if(neighbor->size() < n) {
    neighbor->push(w);
  }
  else if(neighbor->top().score>w.score) {
    neighbor->pop();
    neighbor->push(w);
  }
  Entry* temp = nearestNeighbor(nextBranch, neighbor, n, x, y, z);
  Entry* best = closest(temp,root ,x,y,z);

  if(neighbor->size()<n||neighbor->top().score>abs(targetcompareval - rootcompareval)) {
    temp = nearestNeighbor(otherBranch, neighbor, n, x, y, z);
  }
  return best;
}

std::vector<Star> KDtree::find(size_t n, float x, float y, float z) {
  std::vector<Star> nearestNeighbors = std::vector<Star>();
  std::priority_queue<wrap> *pqueue = new std::priority_queue<wrap>();
  if(!mRoot || n == 0) {
    return nearestNeighbors;
  }
  nearestNeighbor(mRoot,pqueue, n , x, y, z);
  while(!pqueue->empty()) {
    wrap w = pqueue->top();
    pqueue->pop();
    Star star = w.star;
    nearestNeighbors.push_back(star);
  }
  std::reverse(nearestNeighbors.begin(),nearestNeighbors.end());
  return nearestNeighbors;

}

StarMap::StarMap(std::istream& stream) {
  kdtree = new KDtree();
  std::string line;
  size_t id = 1;
  while(std::getline(stream,line)) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(line);
    while (std::getline(ss, token, '\t')){
      tokens.push_back(token);
    }
    float x = std::stof(tokens[0]);
    float y = std::stof(tokens[1]);
    float z = std::stof(tokens[2]);
    Star star;
    star.id = id;
    star.x = x;
    star.y = y;
    star.z = z;
    Entry *entry = new Entry(star);
    kdtree->push(entry);
    id++;
  }
}
StarMap::~StarMap(){
  delete kdtree;
}

StarMap* StarMap::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new StarMap(stream);
}









