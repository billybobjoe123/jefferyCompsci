#include "GenePool.h"
#include <vector>
#include <sstream>
// GenePool Member Functions


GenePool::GenePool(std::istream& stream) {
    map = new std::map<std::string,Person*>;
    std::string line;
    while (std::getline(stream, line)) {
        if (line.length()>0 && line[0] != '#') {
            std::vector<std::string> tokens;
            std::string token;
            std::stringstream ss(line);
            while (std::getline(ss, token, '\t')){
                tokens.push_back(token);
            }
            std::string name =  tokens[0];
            Gender gender;
            if(tokens[1]=="male") {
                gender = Gender::MALE;
            }
            else {
                gender = Gender::FEMALE;
            }
            Person* mother;
            if (tokens[2]=="???") {
                mother = nullptr;
            } 
            else {
                mother = find(tokens[2]);
            }
            Person* father;
            if (tokens[3]=="???") {
                father = nullptr;
            } 
            else {
                father = find(tokens[3]);
            }
            Person *person = new Person(name,mother,father,gender);
            if(mother) {
                mother->addChild(person);
            }
            if(father) {
                father->addChild(person);
            }
            map->insert({name,person});
        }

    } 

}

GenePool::~GenePool() {
    for(std::map<std::string, Person*>::iterator itr = map->begin(); itr != map->end(); itr++)
    {
        delete (itr->second);
    }
    map->clear();
    delete map;
}

Person* GenePool::find(const std::string& name) const {
    auto p = map->find(name);
    Person* person = p->second;
    return person;
}
