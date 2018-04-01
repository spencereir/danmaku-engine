#ifndef __RESOURCES_H_
#define __RESOURCES_H_

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

template<typename T>
T &getResource(std::string resource_name) {
    static std::map<std::string, T> resource_map;
    auto it = resource_map.find(resource_name);
    if (it == resource_map.end()) {
        T new_resource;
        new_resource.loadFromFile(resource_name);
        return resource_map[resource_name] = new_resource;
    } else {
        return it->second;
    }
}

#endif
