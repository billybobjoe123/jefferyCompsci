#ifndef ATLAS_H
#define ATLAS_H

#include <istream>
#include <string>
#include <set>
#include <unordered_map>
#include "Trip.h"






class Station {
  
  public:
  struct Edge {
  Station* away; //goes away from
  Station* to;   //heads to
  int dist;
  bool isTrain;
  std::string route;
  bool operator < (const Edge& other) const {
    return this->dist < other.dist;
  }
  };
  std::string name;
  std::vector<Edge> edges;
  Station(std::string name);
};




class Atlas {
public:
  // Required Class Function
  static Atlas* create(std::istream& stream);

private:
  // Member Variables
  std::unordered_map<std::string,Station*> stations;
public:
  // Constructor & Destructor
  Atlas(std::istream& stream);
  ~Atlas();

  // Required Member Function
  Trip route(const std::string& src, const std::string& dst);
};

#endif
