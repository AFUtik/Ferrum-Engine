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
    TagGroup(TagGroup *parent, bool recursive) : parent(parent), recursive(recursive) {}

    void addObject(const T &object) const {
        if(parent != nullptr && recursive==true) parent->addObject(object);
        objects.push_back(object);
    }

    void addObject(const std::string &tag, const T &object) const {
        TagGroup &group = findGroup(tag);
        group.addObject(object);
    }

    inline std::vector<T>& getObjects() const {
        return objects;
    }

    TagGroup* findGroup(std::string tag) {
        if(tag.empty()) return this;

        std::string token;
        for(size_t i = tag.size(); i >= 0; i++) {
            const char &c = tag[i];
            if(c == '.') break;

            token = tag[i] + token;
            tag.pop_back();
        }
        if(!tag.empty()) tag.pop_back();

        TagGroup* group = subgroups[token];
        if(group==nullptr) return nullptr;

        return group->findGroup(tag);
    }
};

#endif