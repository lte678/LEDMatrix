//
// Created by leon on 21.05.19.
//

#include "Property.h"

// ----- Integer Property -----

IntProperty::IntProperty(std::string _id) : Property(_id) {
    setValue(0);
};

IntProperty::IntProperty(std::string _id, int _value) : Property(_id) {
    setValue(_value);
}

void IntProperty::setValue(int _value) {
    m_PropertyLock.lock();
    string = std::to_string(_value);
    value = _value;
    m_PropertyLock.unlock();
}

bool IntProperty::setValue(std::string valString) {
    m_PropertyLock.lock();
    try {
        value = std::stoi(valString);
        string = std::to_string(value);
        m_PropertyLock.unlock();
        return true;
    } catch(...) {
        m_PropertyLock.unlock();
        return false;
    }
}


// ----- Float Property -----

FloatProperty::FloatProperty(std::string _id) : Property(_id) {
    setValue(0.0f);
};

FloatProperty::FloatProperty(std::string _id, float _value) : Property(_id) {
    setValue(_value);
}

void FloatProperty::setValue(float _value) {
    m_PropertyLock.lock();
    string = std::to_string(_value);
    value = _value;
    m_PropertyLock.unlock();
}

bool FloatProperty::setValue(std::string valString) {
    m_PropertyLock.lock();
    try {
        value = std::stof(valString);
        string = std::to_string(value);
    } catch(...) {
        m_PropertyLock.unlock();
        return false;
    }
    m_PropertyLock.unlock();
    return true;
}

// ----- Text Property -----

TextProperty::TextProperty(std::string _id) : Property(_id) {
    setValue("");
};

TextProperty::TextProperty(std::string _id, std::string _value) : Property(_id) {
    setValue(std::move(_value));
}

bool TextProperty::setValue(std::string valString) {
    // This is pretty simple, since no conversion is going on
    m_PropertyLock.lock();
    string = std::move(valString);
    m_PropertyLock.unlock();
    return true;
}

// ----- Boolean Property -----
// TODO

// ----- Color Property -----

ColorProperty::ColorProperty(std::string _id) : Property(std::move(_id)) {
    setValue(0.0f, 0.0f, 0.0f, 0.0f);
};

ColorProperty::ColorProperty(std::string _id, float _r, float _g, float _b) : Property(std::move(_id)) {
    setValue(_r, _g, _b, 0.0f);
}

ColorProperty::ColorProperty(std::string _id, float _r, float _g, float _b, float _w) : Property(std::move(_id)) {
    setValue(_r, _g, _b, _w);
}

void ColorProperty::setValue(float _r, float _g, float _b) {
    m_PropertyLock.lock();
    r = _r;
    g = _g;
    b = _b;
    string = std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "," + std::to_string(w);
    m_PropertyLock.unlock();
}

void ColorProperty::setValue(float _r, float _g, float _b, float _w) {
    m_PropertyLock.lock();
    r = _r;
    g = _g;
    b = _b;
    w = _w;
    string = std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "," + std::to_string(w);
    m_PropertyLock.unlock();
}

bool ColorProperty::setValue(std::string valString) {
    m_PropertyLock.lock();
    std::string delimiter = ",";
    std::vector<std::string> vals;
    try {
        size_t pos;
        while ((pos = valString.find(delimiter)) != std::string::npos) {
            vals.push_back(valString.substr(0, pos));
            valString.erase(0, pos + delimiter.length());
        }
        vals.push_back(valString);
        if(vals.size() == 3) {
            r = std::stof(vals.at(0));
            g = std::stof(vals.at(1));
            b = std::stof(vals.at(2));
        }
        else if(vals.size() == 4) {
            r = std::stof(vals.at(0));
            g = std::stof(vals.at(1));
            b = std::stof(vals.at(2));
            w = std::stof(vals.at(3));
        } else {
            // Invalid amount of parameters, not rgb nor rgbw
            m_PropertyLock.unlock();
            return false;
        }

        string = std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "," + std::to_string(w);
    } catch(...) {
        m_PropertyLock.unlock();
        return false;
    }
    m_PropertyLock.unlock();
    return true;
}

// ----- Property Interface -----
// used to manage collections of properties

PropertyInterface::PropertyInterface(std::string id) {
    m_ID = id;
}


bool PropertyInterface::hasProperty(std::string id) {
    for(Property* prop : m_Properties) {
        if(prop->getID() == id) return true;
    }
    return false;
}

bool PropertyInterface::setProperty(std::string id, std::string value) {
    for(Property* prop : m_Properties) {
        if(prop->getID() == id) {
            return prop->setValue(value);
            // Casting to property type not possible
        }
    }
    return false; // Could not find property with given id
}

std::string PropertyInterface::getProperty(std::string id) const {
    for(Property* prop : m_Properties) {
        if(prop->getID() == id) {
            return prop->getString();
        }
    }
    return "N/A"; // Could not find property with given id
}

std::vector<std::string> PropertyInterface::getProperties() const {
    std::vector<std::string> ids = std::vector<std::string>();
    for(Property *prop : m_Properties) {
        ids.push_back(prop->getID());
    }

    return ids;
}

std::vector<PropertyInterface*> PropertyInterface::getPropertyTrees() const {
    return m_PropertyTrees;
}

PropertyInterface* PropertyInterface::getPropertyTree(std::string id) const {
    for(PropertyInterface* prop : m_PropertyTrees) {
        if(prop->getID() == id) {
            return prop;
        }
    }
    return nullptr; // Could not find property with given id
}


void PropertyInterface::registerProperty(Property *property) {
    for(Property* prop : m_Properties) {
        if(property->getID() == prop->getID()) {
            return;
        }
    }

    m_Properties.push_back(property);
}

void PropertyInterface::registerPropTree(PropertyInterface *propTree) {
    for(PropertyInterface* tree : m_PropertyTrees) {
        if(tree->getID() == propTree->getID()) {
            return;
        }
    }

    m_PropertyTrees.push_back(propTree);
}