//
// Created by dawud on 5/21/26.
//

#ifndef DAWUDENGINE_RESOURCEHOLDER_H
#define DAWUDENGINE_RESOURCEHOLDER_H
#include <memory>
#include <string>
#include <unordered_map>

template<typename Resource, typename Identifier >
class ResourceHolder {
    public:
    void load(Identifier id, const std::string &path);


    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;
    private:
    std::unordered_map<Identifier, std::unique_ptr<Resource>> resourceMap;

};

// This is here as for templates we cannot have a cpp file
// so i am using a .inl and telling the compiler here is the code
#include "ResourceHolder.inl"

#endif //DAWUDENGINE_RESOURCEHOLDER_H
