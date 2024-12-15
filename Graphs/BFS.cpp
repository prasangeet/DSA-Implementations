#include <iostream>
#include <map>
#include <list>
#include <string>
#include <queue>

using namespace std;

class Object{};

class Decorator{
private: 
    map<string, Object*> attributes;
public:
    Object* get(const string& key){return attributes[key];}
    void set(const string& key, Object* value){attributes[key] = value;}
};

class Vertex