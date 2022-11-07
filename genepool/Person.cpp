#include "Person.h"
#include <algorithm>
#include <set>
// Person Member Functions
Person::Person(std::string n,Person* mother, Person* father, Gender gender) {
    this->Name = n;
    this->mommy = mother;
    this->daddy = father;
    this->gend = gender;
    kids = std::set<Person*>();
}

void Person::addChild(Person* person) {
    if (person) {
        kids.insert(person);
    }
}
Gender Person::gender() const{
    return gend;
}
Person* Person::mother() {
    return mommy;
}
Person* Person::father() {
    return daddy;
}
const std::string& Person::name()  const{
    return Name;
}
std::set<Person*> Person::ancestorHelper(Person* person) {
    std::set<Person*> ancestor = std::set<Person*>();
    if(!person) {
        return ancestor;
    }
    ancestor.insert(this);
    ancestor.merge(ancestorHelper(person->mother()));
    ancestor.merge(ancestorHelper(person->father()));
    return ancestor;
}
std::set<Person*> Person::ancestors(PMod pmod) {
     std::set<Person*> ancestor;
    if(pmod == PMod::MATERNAL) {
        ancestor = ancestorHelper(mommy);
    }
    else if( pmod == PMod::PATERNAL) {
        ancestor = ancestorHelper(daddy);
    }
    else {
        ancestor =  ancestorHelper(daddy);
        ancestor.merge(ancestorHelper(mommy));
    }
    ancestor.erase(this);
    return ancestor;
}
    
std::set<Person*> Person::descendantHelper(Person* person) {
    std::set<Person*> descendant = std::set<Person*>();
    if(!person) {
        return descendant;
    }
    std::set<Person*> kid = person->children();
    
    for(auto iter = kid.begin();iter!=kid.end();iter++) {
        Person* person = *iter;
        descendant.merge(descendantHelper(person));
    }
    descendant.merge(kid);
    return descendant;
}
std::set<Person*> Person::descendants() {

    std::set<Person*> desc = descendantHelper(this);
    desc.erase(this);
    return desc;
}
std::set<Person*> Person::aunts(PMod pmod, SMod smod) {
    std::set<Person*> aunt = std::set<Person*>();
    if (pmod == PMod::MATERNAL && mommy) {
        aunt.merge(mommy->sisters(PMod::ANY,smod));
    }
    else if (pmod == PMod::PATERNAL && daddy) {
        aunt.merge(daddy->sisters(PMod::ANY,smod));
    }
    else {
        if (mommy) {
            aunt.merge(mommy->sisters(PMod::ANY,smod));
        }
        if (daddy) {
            aunt.merge(daddy->sisters(PMod::ANY,smod));
        }
    }
    return aunt;

}

std::set<Person*> Person::brothers(PMod pmod, SMod smod) {
    std::set<Person*> bro = std::set<Person*>();
    std::set<Person*> sibs = siblings(pmod,smod);
    for(auto iter = sibs.begin();iter!=sibs.end();iter++) {
        Person* person = *iter;
        if (person->gender() == Gender::MALE) {
            bro.insert(person);
        }
    }
    return bro;
}
std::set<Person*> Person::sisters(PMod pmod, SMod smod) {
    std::set<Person*> sis = std::set<Person*>();
    std::set<Person*> sibs = siblings(pmod,smod);
    for(auto iter = sibs.begin();iter!=sibs.end();iter++) {
        Person* person = *iter;
        if (person->gender() == Gender::FEMALE) {
            sis.insert(person);
        }
    }
    return sis;

}
std::set<Person*> Person::children() {
    return kids;
}
std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
    std::set<Person*> parentsibs = std::set<Person*>();
    std::set<Person*> cousin = std::set<Person*>();
    if(pmod == PMod::PATERNAL && daddy) {
        parentsibs.merge(daddy->siblings(PMod::ANY,smod));
    }
    else if(pmod == PMod::MATERNAL && mommy) {
        parentsibs.merge(mommy->siblings(PMod::ANY,smod));
    }
    else {
        if(mommy) {
            parentsibs.merge(mommy->siblings());
            
        }
        if (daddy) {
            parentsibs.merge(daddy->siblings());
        }
    }
    for(auto iter = parentsibs.begin();iter!=parentsibs.end();iter++) {
        Person* person = *iter;
        cousin.merge(person->children());
    }
    return cousin;
}
std::set<Person*> Person::daughters() {
    std::set<Person*> daughter = std::set<Person*>();
    for(auto iter = kids.begin() ;iter!= kids.end();iter++) {
        Person* kid = *iter;
        if (kid->gender() == Gender::FEMALE) {
            daughter.insert(kid);
        }
    }
    return daughter;
}
std::set<Person*> Person::sons() {
    std::set<Person*> son = std::set<Person*>();
    
    for(auto iter = kids.begin() ;iter!= kids.end();iter++) {
        Person* kid = *iter;
        if (kid->gender() == Gender::MALE) {
            son.insert(kid);
        }
    }
    return son;
}

std::set<Person*> Person::grandchildren() {
    std::set<Person*> grandkids = std::set<Person*>();
    for(auto iter = kids.begin(); iter!=kids.end();iter++) {
        Person* person = *iter;
        grandkids.merge(person->children());
    }
    return grandkids;
}
std::set<Person*> Person::granddaughters() {
    std::set<Person*> grandkids = std::set<Person*>();
    for(auto iter = kids.begin(); iter!=kids.end();iter++) {
        Person* person = *iter;
        grandkids.merge(person->daughters());
    }
    return grandkids;
}
std::set<Person*> Person::grandsons() {
    std::set<Person*> grandkids = std::set<Person*>();
    for(auto iter = kids.begin(); iter!=kids.end();iter++) {
        Person* person = *iter;
        grandkids.merge(person->sons());
    }
    return grandkids;
}
std::set<Person*> Person::grandfathers(PMod pmod) {
    std::set<Person*> grandfather = std::set<Person*>();
    std::set<Person*> grandparent = grandparents(pmod);
    for(auto iter = grandparent.begin(); iter!=grandparent.end();iter++) {
        Person* person = *iter;
        if (person->gender() == Gender::MALE) {
            grandfather.insert(person);
        }
    }
    return grandfather;
}
std::set<Person*> Person::grandmothers(PMod pmod) {
    std::set<Person*> grandmother = std::set<Person*>();
    std::set<Person*> grandparent = grandparents(pmod);
    for(auto iter = grandparent.begin(); iter!=grandparent.end();iter++) {
        Person* person = *iter;
        if (person->gender() == Gender::FEMALE) {
            grandmother.insert(person);
        }
    }
    return grandmother;
}
std::set<Person*> Person::grandparents(PMod pmod) {
    std::set<Person*> grandparents = std::set<Person*>();
    if (pmod == PMod::MATERNAL) {
        if (mommy) {
            if (mommy->father())
                grandparents.insert(mommy->father());
            if (mommy->mother()) 
                grandparents.insert(mommy->mother());
        }
    }
    else if(pmod == PMod::PATERNAL) {
        if (daddy) {
            if (daddy->father())
                grandparents.insert(daddy->father());
            if (daddy->mother())
                grandparents.insert(daddy->mother());
        }
    }
    else {
        if (mommy) {
            if (mommy->father())
                grandparents.insert(mommy->father());
            if (mommy->mother()) 
                grandparents.insert(mommy->mother());
        }
        if (daddy) {
            if (daddy->father())
                grandparents.insert(daddy->father());
            if (daddy->mother())
                grandparents.insert(daddy->mother());
        }
    }
    return grandparents;
}

std::set<Person*> Person::nephews(PMod pmod, SMod smod) {
    std::set<Person*> sibs = siblings(pmod,smod);
    std::set<Person*> nefs = std::set<Person*>();
    for(auto iter = sibs.begin(); iter!=sibs.end();iter++) {
        Person* person = *iter;
        std::set<Person*> son = person->sons();
        nefs.merge(son);
    }
    return nefs;

}
std::set<Person*> Person::nieces(PMod pmod, SMod smod) {
    std::set<Person*> sibs = siblings(pmod,smod);
    std::set<Person*> niece = std::set<Person*>();
    for(auto iter = sibs.begin(); iter!=sibs.end();iter++) {
        Person* person = *iter;
        std::set<Person*> dau = person->daughters();
        niece.merge(dau);
    }
    return niece;
}
std::set<Person*> Person::parents(PMod pmod) {
    std::set<Person*> P = std::set<Person*>();
    if(mommy && (pmod == PMod::MATERNAL || pmod == PMod::ANY)) {
        P.insert(mommy);
    }
    if(daddy && (pmod == PMod::PATERNAL || pmod == PMod::ANY)) {
        P.insert(daddy);
    }
    return P;
}
std::set<Person*> Person::siblings(PMod pmod, SMod smod) {
    std::set<Person*> motherside = std::set<Person*>();
    std::set<Person*> fatherside = std::set<Person*>();
    std::set<Person*> sibling = std::set<Person*>();
    if(mommy) {
        motherside.merge(mommy->children());
    }
    if(daddy){
        fatherside.merge(daddy->children());
    }
    fatherside.erase(this);
    motherside.erase(this);
    if(pmod == PMod::PATERNAL) {
        if (smod == SMod::ANY) {
            sibling.merge(fatherside);
        }
        else if (smod == SMod::FULL) {
            std::set_intersection(fatherside.begin(),fatherside.end(), motherside.begin(),motherside.end(), inserter(sibling,sibling.begin()));
        }
        else {
            std::set_difference(fatherside.begin(),fatherside.end(), motherside.begin(),motherside.end(), inserter(sibling,sibling.begin()));
        }
    }
    else if(pmod == PMod::MATERNAL) {
        if (smod == SMod::ANY) {
            sibling.merge(motherside);
        }
        else if (smod == SMod::FULL) {
            std::set_intersection(fatherside.begin(),fatherside.end(), motherside.begin(),motherside.end(), inserter(sibling,sibling.begin()));
        }
        else {
            std::set_difference(motherside.begin(),motherside.end(), fatherside.begin(),fatherside.end(), inserter(sibling,sibling.begin()));
        }
    }
    else {
        if(smod == SMod::ANY) {
            std::set_union(fatherside.begin(),fatherside.end(), motherside.begin(),motherside.end(), inserter(sibling,sibling.begin()));
        }
        else if(smod == SMod::FULL) {
            std::set_intersection(fatherside.begin(),fatherside.end(), motherside.begin(),motherside.end(), inserter(sibling,sibling.begin()));
        }
        else {
            std::set_symmetric_difference(motherside.begin(),motherside.end(),fatherside.begin(),fatherside.end(), inserter(sibling,sibling.begin()));
        }
    }
    return sibling;

}


std::set<Person*> Person::uncles(PMod pmod, SMod smod) {
    std::set<Person*> uncle = std::set<Person*>();
    if (pmod == PMod::MATERNAL && mommy) {
        uncle.merge(mommy->brothers(PMod::ANY,smod));
    }
    else if (pmod == PMod::PATERNAL && daddy) {
        uncle.merge(daddy->brothers(PMod::ANY,smod));
    }
    else {
        if (mommy) {
            uncle.merge(mommy->brothers(PMod::ANY,smod));
        }
        if (daddy) {
            uncle.merge(daddy->brothers(PMod::ANY,smod));
        }
    }
    return uncle;

}
