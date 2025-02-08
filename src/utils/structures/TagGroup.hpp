#ifndef TAGGROUP_HPP
#define TAGGROUP_HPP

#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

template<typename T>
class TagGroup {
protected:
    std::unordered_map<std::string, std::shared_ptr<TagGroup<T>>> subgroups;
    std::vector<T> objects;

    std::shared_ptr<TagGroup> parent = nullptr;
    bool recursive = true;
public:
    TagGroup<T>(TagGroup<T> *parent, bool recursive) : parent(parent), recursive(recursive) {}

    void addObject(const T &object) {
        if(parent != nullptr && recursive==true) parent->addObject(object);
        objects.push_back(object);
    }

    void addObject(const std::string &tag, const T &object) {
        TagGroup &group = findGroup(tag);
        group.addObject(object);
    }

    inline std::vector<T>& getObjects() {
        return objects;
    }

    TagGroup* findOrCreateGroup(std::string tag) {
        if(tag.empty()) return this;

        size_t dotPos = tag.find('.');
        std::string currentTag = (dotPos == std::string::npos) ? tag : tag.substr(0, dotPos);
        std::string remainingTags = (dotPos == std::string::npos) ? "" : tag.substr(dotPos + 1);

        auto& subgroup = subgroups[currentTag];
        if (!subgroup) subgroup = std::make_shared<TagGroup>(this, recursive);

        return subgroup->findOrCreateGroup(remainingTags);
    }
};

#endif