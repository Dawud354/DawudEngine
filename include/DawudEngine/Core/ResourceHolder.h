//
// Created by dawud on 5/21/26.
//

#ifndef DAWUDENGINE_RESOURCEHOLDER_H
#define DAWUDENGINE_RESOURCEHOLDER_H
#include <memory>
#include <string>
#include <unordered_map>

template<typename Resource, typename Identifier>
class ResourceHolder {
public:
    void load(Identifier id, const std::string &path);
    // i forgot why this is here
    template<typename Parameter>
    void load(Identifier id, const std::string& filename, const Parameter& secondParam);

    Resource &get(Identifier id);
    const Resource &get(Identifier id) const;

private:
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);

    std::unordered_map<Identifier, std::unique_ptr<Resource> > resourceMap;
};

// This is here as for templates we cannot have a cpp file,
// so I am using a .inl and telling the compiler here is the code
#include "ResourceHolder.inl"

#endif //DAWUDENGINE_RESOURCEHOLDER_H
