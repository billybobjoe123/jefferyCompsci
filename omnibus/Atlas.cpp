#include "Atlas.h"
#include<bits/stdc++.h> 
#include "Trip.h"
#include <algorithm>
#define INF 0x3f3f3f3f
Station::Station(std::string name) {
  this->name = name;
  edges = std::set<Edge>();
}


Atlas::Atlas(std::istream& stream) {
  stations = std::unordered_map<std::string,Station*>();

  bool isTrain = false;
  std::string line,identifier,numS, name;
  int num,prevNum = 0;
  std::string prev = "";
  stream >> std::ws;
  while(std::getline(stream,line)) {
    if(line.length() == 0 || line[0] == '#') 
		  continue;
    std::istringstream sstream(line);
    sstream >> identifier;

    
    if(identifier == "TRAIN:") {
      sstream >> std::ws;
      std::getline(sstream, line);
      isTrain = true;
      prev = "";
      prevNum = 0;
    }
    else if (identifier == "BUS:") {
      sstream >> std::ws;
      std::getline(sstream, line);
      isTrain = false;
      prev = "";
      prevNum = 0;
    }
    else if(identifier == "-") {
      sstream >> numS; num = stoi(numS);
      sstream >> std::ws;
      std::getline(sstream, name);	
      if (stations.find(name) == stations.end()) {
        Station *station = new Station(name);
        stations[name] = station;
      }
      if (prev == "") {
        prev = name;
      }
      else {
        Station::Edge edge;
        edge.away = stations[prev];
        edge.to = stations[name];
        edge.dist = num-prevNum;
        prevNum = num;
        prev = name;
        edge.isTrain = isTrain;
        edge.route = line;
        stations[name]->edges.insert(edge);
      }
    }
  }
}

Atlas::~Atlas() {
  for(auto iter = stations.begin();iter!=stations.end();iter++) {
    delete iter->second;
    iter->second = nullptr;
  }
}

Trip Atlas::route(const std::string& src, const std::string& dst) {
  std::unordered_set<std::string> visited;
  std::priority_queue<std::pair<int, Station*>,std::vector<std::pair<int,Station*>>> pq;
  std::unordered_map<std::string,int> distances;
  std::unordered_map<std::string,Station::Edge> howTFdidIgethere;
  bool touchedDST = false;
  if(stations.find(src)==stations.end()) {
    throw std::runtime_error("No route.");
  }
  for(auto iter : stations) {
    if(iter.first == src) {
      distances.insert(std::make_pair(iter.first,0));
      pq.push(std::make_pair(0,stations[src]));
    }
    else {
      distances.insert(std::make_pair(iter.first,INF));
    }
  }
  while(!pq.empty()) {
    Station* s = pq.top().second;
    pq.pop();
    if(visited.count(s->name)) {
      continue;
    }
    if(dst == s->name) {
      touchedDST = true;
    }
    for(auto i : s->edges) {
      if(i.isTrain && distances[i.away->name]>i.dist + distances[i.to->name]) {
        distances[i.away->name] = i.dist + distances[i.to->name];
        howTFdidIgethere[i.away->name] = i;
        pq.push(std::make_pair(i.dist,i.to));
      }
      else if (!i.isTrain && distances[i.away->name]>1 + distances[i.to->name]) {
        distances[i.away->name] = distances[i.to->name];

        howTFdidIgethere[i.away->name] = i;

        pq.push(std::make_pair(0,i.away));
      }
    }
    visited.insert(s->name);
  }

  if(!touchedDST) {
    throw std::runtime_error("No route.");
  }
  std::vector<Station::Edge> srcToDst;
  std::string name = dst;
  Station::Edge returnEdge;

  while (true) {
    returnEdge = howTFdidIgethere[name];
    srcToDst.push_back(returnEdge);
    name = returnEdge.to->name;
    if(howTFdidIgethere.find(name) == howTFdidIgethere.end()) {
      break;
    }
  }
  Trip trip;
  trip.start = src;
  std::reverse(srcToDst.begin(),srcToDst.end());
  for(size_t i = 0;i<srcToDst.size();i++) {
    Trip::Leg leg;
    leg.line = srcToDst[i].route;
    leg.stop = srcToDst[i].away->name;
    trip.legs.push_back(leg);
  }
  return trip;
}


Atlas* Atlas::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new Atlas(stream);
}
