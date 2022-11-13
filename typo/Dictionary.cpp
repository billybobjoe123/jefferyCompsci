#include "Dictionary.h"
#include <cmath>
bool isLowerCase(std::string str) {
    for(size_t i = 0;i<str.size();i++) {
        if(isupper(str[i])) {
            return false;
        }
    }
    return true;

}
Point letterToPoint(char c) {
    switch (c)
    {
    case 'a':
        return QWERTY[0];
        
    case 'b':
        /* code */
        return QWERTY[1];
        
    case 'c':
        /* code */
        return QWERTY[2];
        
    case 'd':
        /* code */
        return QWERTY[3];
        
    case 'e':
        /* code */
        return QWERTY[4];
        
    case 'f':
        /* code */
        return QWERTY[5];
        
    case 'g':
        /* code */
        return QWERTY[6];
        
    case 'h':
        /* code */
        return QWERTY[7];
        
    case 'i':
        /* code */
        return QWERTY[8];
        
    case 'j':
        /* code */
        return QWERTY[9];
        
    case 'k':
        /* code */
        return QWERTY[10];
        
    case 'l':
        /* code */
        return QWERTY[11];
        
    
    case 'm':
        /* code */
        return QWERTY[12];
        
    case 'n':
        /* code */
        return QWERTY[13];
        
    case 'o':
        /* code */
        return QWERTY[14];
        
    case 'p':
        /* code */
        return QWERTY[15];
        
    case 'q':
        /* code */
        return QWERTY[16];
        
    case 'r':
        /* code */
        return QWERTY[17];
        
    case 's':
        /* code */
        return QWERTY[18];
        
    case 't':
        /* code */
        return QWERTY[19];
        
    case 'u':
        /* code */
        return QWERTY[20];
        
    case 'v':
        /* code */
        return QWERTY[21];
        
    case 'w':
        /* code */
        return QWERTY[22];
        
    case 'x':
        /* code */
        return QWERTY[23];
        
    
    case 'y':
        /* code */
        return QWERTY[24];
        
    case 'z':
        /* code */
        return QWERTY[25];
    }
    Point point;
    point.x = 100;
    point.y = 100;
    return point;
}


Dictionary::Dictionary(std::istream& stream) {
    std::string line;
    while(std::getline(stream,line)) {
        if (line.length()>0 && line[0] != '#' && isLowerCase(line))  {
            mWords.push_back(line);
        }
    }
}

Heap Dictionary::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    Heap wordHeap = Heap(maxcount);
    
    for(size_t i = 0;i<mWords.size();i++) {
        std::string word = mWords[i];
        size_t wordSize = word.size();
        float score = 0;
        for(size_t i = 0;i<points.size();i++) {
            if (i>=wordSize) {
                break;
            }
            char c = word[i];
            Point p = letterToPoint(c);
            float dist = sqrt(pow(p.x - points[i].x,2) + pow(p.y - points[i].y,2));
            score = score + 1 / (10*pow(dist,2) + 1);
        }
        if(wordSize<points.size())
            score = score/points.size();
        if(wordSize>points.size())
            score = score/wordSize;
        if(score >= cutoff) {
            if(wordHeap.count()<wordHeap.capacity()) {
                wordHeap.push(word,score);
            }
            else {
                if(wordHeap.top().score<score) {
                    wordHeap.pushpop(word,score);
                }
            }
            
        }
    }
    return wordHeap;

}
