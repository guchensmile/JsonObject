/*
 * JsonHelper.h
 *
 *  Created on: Sep 10, 2016
 *      Author: zwl
 */

#ifndef JSONOBJECT_HPP_
#define JSONOBJECT_HPP_


#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <vector>
#include <map>
#include <exception>

using std::string;
using std::vector;
using std::map;
using boost::property_tree::ptree;

class ReadJsonException:public std::exception{
public:
    explicit ReadJsonException(const string &errInfo):_M_msg(errInfo){

    }
    explicit ReadJsonException(){}

    virtual const char* what() const throw(){
        return ("ReadJsonException: " + _M_msg).c_str();
    }
private:
    string _M_msg;
};

//note: key not contain "."
class JsonObject
{
public:
    enum JSON_STATUS{SUCCESS,PARSER_FAILED};
public:
    class JsonValue{
    public:
        inline JsonValue operator[](const string &key);
//      inline JsonValue operator[](const size_t index);
        inline void clear();
        template<typename T>
        void append(T value);
        inline void append(const JsonValue &value);
        inline void append(const JsonObject &value);
        template<typename T>
        T as();
        template<typename T>
        vector<T> asArray();
        inline vector<JsonValue> asArray();
        template<typename T>
        JsonValue& operator=(const T value);
        inline JsonValue& operator=(const JsonValue &value);
        inline JsonValue& operator=(const JsonObject &value);
        template<typename T>
        JsonValue& operator=(const vector<T> &value);
        inline operator string();
        inline size_t size();
        inline bool exist(const string &key);
    private:
        friend class JsonObject;
        inline JsonValue(ptree &pt);
        ptree &_pt;
    };
    inline explicit JsonObject(const string &jsonString);
    inline bool isValidated();
    inline bool exist(const string &key)throw (ReadJsonException);
    inline JsonObject::JsonValue operator[](const string &key);
//    inline JsonObject::JsonValue operator[](const size_t index);
    inline void clear();
    template<typename T>
    void append(T value);
    inline void append(const JsonObject &value);
    inline void append(const JsonValue &value);
    template<typename T>
    T as();
    template<typename T>
    vector<T> asArray();
    inline vector<JsonObject::JsonValue> asArray();
    inline operator string();
    inline JsonValue& value();
private:
    ptree formatJson(const string& jsonString);
private:
    ptree _pt;
    JsonValue _value;
    JSON_STATUS _status;
};

#include "JsonObject.inc"

#endif /* JSONOBJECT_HPP_ */
