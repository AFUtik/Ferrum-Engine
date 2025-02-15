#ifndef GAMEPROPERTIES
#define GAMEPROPERTIES

#include <string>
#include <unordered_map>
#include <variant>

enum property_t {
    p_null,
    p_string,
    p_integer,
    p_uinteger,
    p_ull,
    p_float,
    p_bool
};

typedef std::variant<std::monostate, std::string*, int*, unsigned int*, size_t*, float*, bool*> Property;

class GameProperties {
public:
    std::unordered_map<std::string, Property> properties;
private:
    void addProperty(std::string key, Property new_property) {
        properties.emplace(key, new_property);
    }

    template<typename T>
    inline const T& getProperty(std::string key) {
        return std::get<T>(properties[key]);
    }
    
    template<typename T>
    inline const void setProperty(std::string key, const T& value) {
        Property& property = properties[key];
        if(std::holds_alternative<T>(properties)) {
            property = value;
        }
    }

    inline int getPropertyInfo(std::string key) {
        return properties[key].index();
    }
};

#endif