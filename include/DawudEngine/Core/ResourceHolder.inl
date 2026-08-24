// include guard to stop multiple includes
#ifndef DAWUDENGINE_RESOURCEHOLDER_INL
#define DAWUDENGINE_RESOURCEHOLDER_INL

#include <cassert>

// bit weird we need to include this time before every function
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id,
const std::string& path)
{
    // use a ptr so we can easily pass around the object
    // and we can store objects like shaders
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(path))
        throw std::runtime_error("ResourceHolder::load - Failed to  load " + path);

    // insert and check status
    insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
template <typename Parameter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Parameter& secondParam) {
    // create and load resource
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, secondParam))
        throw std::runtime_error("ResourceHolder::load - Failed to  load " + filename);
    insertResource(id, std::move(resource));
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) {
    auto found = resourceMap.find(id);
    assert(found != resourceMap.end());
    return *found->second;
}

// the const one is for if we have a const instance
// idk when we
template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const {
    auto found = resourceMap.find(id);
    assert(found != resourceMap.end());
    return *found->second;
}

// less repeated lines
template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
    // Insert and check success
    auto inserted = resourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

#endif //DAWUDENGINE_RESOURCEHOLDER_INL



