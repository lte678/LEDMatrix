//
// Created by leon on 21.05.19.
//

#ifndef MATRIX_CORE_PROPERTY_H
#define MATRIX_CORE_PROPERTY_H

#include <string>
#include <vector>
#include <mutex>

class Property {
protected:
    //TODO: std::move
    Property(std::string _id) : id(_id), string("") {};
    Property(std::string _id, std::string _string) : id(_id), string(_string) {};

    std::string string;
    std::string id;

    std::mutex m_PropertyLock;
public:
    virtual std::string propType() = 0;

    std::string getString() { return string; };
    std::string getID() { return id; };

    virtual bool setValue(std::string valString) = 0;
};

class IntProperty : public Property {
protected:
    int value;
public:
    explicit IntProperty(std::string _id);
    IntProperty(std::string _id, int _value);

    void setValue(int _value);
    bool setValue(std::string valString) override;
    int getValue() const { return value; };

    std::string propType() override { return "int"; };

    operator int() const { return value; };

    IntProperty& operator = (int _value) {
        setValue(_value);
        return *this;
    }
};

class FloatProperty : public Property {
protected:
    float value;
public:
    explicit FloatProperty(std::string _id);
    FloatProperty(std::string _id, float _value);

    void setValue(float _value);
    bool setValue(std::string valString) override;
    float getValue() const { return value; };

    std::string propType() override { return "float"; };

    operator float() const { return value; };

    FloatProperty& operator= (float _value) {
        setValue(_value);
        return *this;
    }
};

class TextProperty : public Property {
public:
    explicit TextProperty(std::string _id);
    TextProperty(std::string _id, std::string _value);

    //We only need the universal assignment function since it already takes a string
    bool setValue(std::string valString) override;
    std::string getValue() { return string; }

    int length() { return string.length(); }

    std::string propType() override { return "string"; };

    operator std::string() { return string; };

    TextProperty& operator = (std::string _value) {
        setValue(std::move(_value));
        return *this;
    }
};

class ColorProperty : public Property {
protected:
    float r;
    float g;
    float b;
    float w;
public:
    explicit ColorProperty(std::string _id);
    ColorProperty(std::string _id, float _r, float _g, float _b);
    ColorProperty(std::string _id, float _r, float _g, float _b, float _w);

    void setValue(float _r, float _g, float _b);
    void setValue(float _r, float _g, float _b, float _w);
    bool setValue(std::string valString) override;

    float getR() const { return r; };
    float getG() const { return g; };
    float getB() const { return b; };
    float getW() const { return w; };

    void setR(float _r) { setValue(_r, g, b, w); };
    void setG(float _g) { setValue(r, _g, b, w); };
    void setB(float _b) { setValue(r, g, _b, w); };
    void setW(float _w) { setValue(r, g, b, _w); };

    std::string propType() override { return "color"; };

    //No implicit conversion, since we don't have an equivalent color object
};

class PropertyInterface {
private:
    std::vector<Property*> m_Properties;
    std::vector<PropertyInterface*> m_PropertyTrees;

    std::string m_ID;
public:
    PropertyInterface(std::string id);

    std::string getID() const { return m_ID; };

    bool hasProperty(std::string id);
    bool setProperty(std::string id, std::string value);
    std::string getProperty(std::string id) const;
    std::vector<std::string> getProperties() const;
    void registerProperty(Property *property);
    PropertyInterface* getPropertyTree(std::string id) const;
    std::vector<PropertyInterface*> getPropertyTrees() const;
    void registerPropTree(PropertyInterface *propTree);
};

#endif //MATRIX_CORE_PROPERTY_H
