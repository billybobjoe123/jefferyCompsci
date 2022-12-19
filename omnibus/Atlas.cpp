#include "Atlas.h"
#include<bits/stdc++.h> 
#include "Trip.h"
#include <algorithm>
#define INF 0x3f3f3f3f
Station::Station(std::string name) {
  this->name = name;
  edges = std::vector<Edge>();
}


Atlas::Atlas(std::istream& stream) {
  stations = std::unordered_map<std::string,Station*>();

  bool isTrain = false;
  std::string line,identifier,numS, name, lane;
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
      std::getline(sstream, lane);
      isTrain = true;
      prev = "";
      prevNum = 0;
    }
    else if (identifier == "BUS:") {
      sstream >> std::ws;
      std::getline(sstream, lane);
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
        //std::cout<<"new Station"<<station->name<<std::endl;
        stations[name] = station;
      }
      if (prev == "") {
        prev = name;
        prevNum = num;
      }
      else {
        Station::Edge edge;
        Station::Edge ed;
        //std::cout<<prev<<std::endl;
        //std::cout<<name<<std::endl;
        edge.away = stations[name];
        edge.to = stations[prev];
        edge.dist = num-prevNum;
        edge.isTrain = isTrain;
        edge.route = lane;
        if(edge.isTrain) {
          edge.dist = edge.dist*100;
        }
        stations[name]->edges.push_back(edge);
        
        ed.away = edge.to;
        ed.to = edge.away;
        ed.dist = edge.dist;
        ed.isTrain = isTrain;
        ed.route = lane;
        stations[prev]->edges.push_back(ed);
        prevNum = num;
        prev = name;
        //std::cout<<"edge Away:"<<edge.away->name<<" edge to:"<<edge.to->name<<" ed away:"<<ed.away->name<<" ed to:"<<ed.to->name<<std::endl;
        //std::cout<<stations[name]->edges.size()<<" "<<stations[name]->edges.size()<<std::endl;
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
  //std::cout<<stations.size()<<std::endl;
  bool touchedDST = false; //to check if desstination has been visited, if false at the end, throw error
  if(stations.find(src)==stations.end() || stations.find(dst)==stations.end()) { //see if src and dst exist in stations map
    throw std::runtime_error("No route.");
  }

  for(auto iter : stations) { //initializes distances map with distances other than src as inf and pushes src onto pq
    if(iter.first == src) {
      distances.insert(std::make_pair(iter.first,0));
      pq.push(std::make_pair(0,stations[src]));
    }
    else {
      distances.insert(std::make_pair(iter.first,INF));
    }
  }
  //std::cout<<"line 106"<<std::endl;
  while(!pq.empty()) { //dijkstras
    Station* s = pq.top().second;
    //std::cout<<s->name<<std::endl; 
    pq.pop();
    if(visited.count(s->name)) {
      continue;
    }
    if(dst == s->name) {
      touchedDST = true;
    }
    //std::cout<<"line 118 before iteration"<<std::endl;
    for(auto i : s->edges) {
      //std::cout<<"to:"<<i.to->name<<" away:"<<i.away->name<<" dist:"<<i.dist<<" isTrain:"<<i.isTrain<<" route:"<<i.route<<" eStart:"<<distances[i.away->name]<<" eEnd:"<<distances[i.to->name]<<std::endl;
      //std::cout<<"number of edges: "<<s->edges.size()<<std::endl;
      if(i.isTrain && distances[i.to->name]>i.dist + distances[i.away->name]) {
        distances[i.to->name] = i.dist + distances[i.away->name];
        howTFdidIgethere[i.to->name] = i;
        pq.push(std::make_pair(distances[i.to->name],i.to));
        //std::cout<<"Train, eEnd new dist:"<<distances[i.to->name]<<std::endl;
      }
      else if (!i.isTrain && distances[i.to->name] > 1 + distances[i.away->name]) {
        
        distances[i.to->name] = 1 + distances[i.away->name];
        howTFdidIgethere[i.to->name] = i;
        pq.push(std::make_pair(distances[i.to->name],i.to));
        //std::cout<<"bus , eEnd new dist:"<<distances[i.to->name]<<std::endl;
      }
    }
    visited.insert(s->name);
    //std::cout<<pq.size()<<std::endl;
  }
  //std::cout<<"line 136 after whileloop"<<std::endl;
  if(!touchedDST) {
    throw std::runtime_error("No route.");
  }
  std::vector<Station::Edge> srcToDst;
  std::string name = dst;
  Station::Edge returnEdge;
  //std::cout<<"line 143 before trip"<<std::endl;
  while (true) {
    //std::cout<<"line 145: "<<name<<std::endl;
    returnEdge = howTFdidIgethere[name];
    srcToDst.push_back(returnEdge);
    name = returnEdge.away->name;
    //std::cout<<"line 149: "<<name<<std::endl;
    if(howTFdidIgethere.find(name) == howTFdidIgethere.end()) {
      break;
    }
  }
  Trip trip;
  trip.start = src;
  if (srcToDst.size()==0) {
    return trip;
  }
  //std::cout<<"line 159"<<std::endl;
  std::reverse(srcToDst.begin(),srcToDst.end());
  std::vector<Station::Edge> queue;
  std::string lastStation = "";
  std::string prevRoute = "";
  //std::cout<<"line 164"<<std::endl;
  for(size_t i = 0;i<srcToDst.size()-1;i++) { 
    queue.push_back(srcToDst[i]);
    if(queue.back().route!=prevRoute && queue.size()>1) {
      Station::Edge temp = queue.back();
      queue.pop_back();
      Trip::Leg leg;
      leg.stop = queue.back().to->name;
      leg.line = queue.back().route;
      queue.clear();
      queue.push_back(temp);
      trip.legs.push_back(leg);
    }
    prevRoute = srcToDst[i].route;

  }
  //std::cout<<"line 179"<<std::endl;
  Trip::Leg l;
  l.stop = dst;
  l.line = srcToDst.back().route;
  trip.legs.push_back(l);
  //std::cout<<"line 184"<<std::endl;

  return trip;
}


Atlas* Atlas::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new Atlas(stream);
}
