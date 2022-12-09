#ifndef ATLAS_H
#define ATLAS_H

#include <istream>
#include <string>
#include <set>
#include <unordered_map>
#include "Trip.h"
struct Edge {
  Station* start;
  Station* end;
  int dist;
  bool isTrain;
  std::string route;
  bool operator > (const Edge& other) const {
    return this->dist < other.dist;
  }
};

struct compare {
  bool operator()(const std::pair<int, Station*>& l, const std::pair<int, Station*>& r)  
   {  
       return l.first > r.first;  
   }  
};


class Station {
  public:
  std::string name;
  std::set<Edge> edges;
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
