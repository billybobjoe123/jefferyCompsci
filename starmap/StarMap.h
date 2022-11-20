#ifndef STARMAP_H
#define STARMAP_H

#include "Star.h"
#include "Helpers.h"
#include <istream>

#include <vector>

class Entry {
public:
  float score;
  Star star;
  size_t level;
  Entry* parent;
  Entry* left;
  Entry* right;

  Entry(Star star, Entry* parent, Entry* left, Entry* right);
  Entry(Star star);
  ~Entry();
};
struct wrap
{
    float score;
    Star star;
    bool operator < (const wrap& other) const {
        return this->score < other.score;
    }
};


class KDtree {
private:
    Entry* mRoot;
public:
    KDtree();
    ~KDtree();
    size_t push(Entry* entry);
    std::vector<Star> find(size_t n, float x, float y, float z);
    Entry* nearestNeighbor(Entry* root, std::priority_queue<wrap> *neighbor, size_t n,float x, float y, float z);
    Entry* closest(Entry* entry1, Entry* entry2,  float x, float y, float z);
};



class StarMap {
public:
    // Required Class Function
    static StarMap* create(std::istream& stream);

private:
    // Member Variables
    KDtree *kdtree;

public:
    // Constructor & Destructor
    StarMap(std::istream& stream);
    ~StarMap();

    // Required Member Function
    std::vector<Star> find(size_t n, float x, float y, float z);

    // Other Member Functions
};




#endif
