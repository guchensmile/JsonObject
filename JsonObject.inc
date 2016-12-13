/*
 * JsonObject.cpp
 *
 *  Created on: Sep 10, 2016
 *      Author: zwl
 */

#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <typeinfo>
#include <algorithm>

using boost::property_tree::ptree_error;

JsonObject::JsonObject(const string &jsonString):
		_pt(std::move(formatJson(jsonString))), _value(_pt) {

}

ptree JsonObject::formatJson(const string& jsonString) {
	ptree pt;
	try {
		std::stringstream ss(jsonString);
		read_json(ss, pt);
	} catch (ptree_error & e) {
		this->_status = PARSER_FAILED;
	}
	this->_status = SUCCESS;
	return pt;
}

bool JsonObject::isValidated() {
	return this->_status == SUCCESS;
}

inline bool JsonObject::exist(const string &key) {
	try {
		return this->_value.exist(key);
	} catch (ptree_error & e) {
		throw ReadJsonException("[" + key + "]" + e.what());
	}
}

JsonObject::JsonValue JsonObject::operator[](const string &key) {
	try {
		return this->_value[key];
	} catch (ptree_error & e) {
		throw ReadJsonException("[" + key + "]," + e.what());
	}
}

JsonObject::JsonValue JsonObject::operator[](const size_t index){
	try {
		return this->_value[index];
	} catch (ptree_error & e) {
		throw ReadJsonException("[index:" + std::to_string(index) + "]," + e.what());
	}
}

void JsonObject::clear() {
	try {
		this->_value.clear();
	} catch (ptree_error & e) {
		throw ReadJsonException(e.what());
	}
}

template<typename T>
void JsonObject::append(T value) {
	this->_value.append(value);
}

void JsonObject::append(const JsonObject &value) {
	this->_value.append(value._value);
}

void JsonObject::append(const JsonValue &value){
	this->_value.append(value);
}

void JsonObject::remove(const string& key){
    this->_value.remove(key);
}

template<typename T>
void JsonObject::add(const string &key, const T& value){
    this->_value.add(key,value);
}

template<typename T>
T JsonObject::as() {
	try {
		return this->_value.as<T>();
	} catch (ptree_error & e) {
		throw ReadJsonException(e.what());
	}
}

template<typename T>
vector<T> JsonObject::asArray() {
	try {
		return this->_value.asArray<T>();
	} catch (boost::bad_lexical_cast& e) {
		throw ReadJsonException(e.what());
	} catch (ptree_error & e) {
		throw ReadJsonException(e.what());
	}
}

vector<JsonObject::JsonValue> JsonObject::asArray() {
	try {
		return this->_value.asArray();
	} catch (ptree_error & e) {
		throw ReadJsonException(e.what());
	}
}

JsonObject::operator string() {
	try {
		return this->_value;
	} catch (ptree_error & e) {
		throw ReadJsonException(e.what());
	}
}

JsonObject::JsonValue& JsonObject::value() {
	return this->_value;
}

JsonObject::JsonValue::JsonValue(ptree &pt) :
		_pt(pt) {
}

JsonObject::JsonValue JsonObject::JsonValue::operator[](const string &key) {
	return JsonValue(this->_pt.get_child(key));
}

JsonObject::JsonValue JsonObject::JsonValue::operator[](const size_t index){
    size_t count=0;
    for(auto pos = this->_pt.begin(); pos != this->_pt.end(); ++pos){
    	if(count++==index){
    		return JsonValue(pos->second);
    	}
    }
    throw ReadJsonException("[index:" + std::to_string(index) + "]" + "out of range");
}

void JsonObject::JsonValue::clear() {
	this->_pt.clear();
}

template<typename T>
void JsonObject::JsonValue::append(T value) {
	boost::property_tree::ptree child;
	child.put("", value);
	this->_pt.push_back(std::make_pair("", child));
}

void JsonObject::JsonValue::append(const JsonObject::JsonValue &value) {
	this->_pt.get_child("").push_back(std::make_pair("", value._pt));
}

void JsonObject::JsonValue::append(const JsonObject &value){
	this->_pt.get_child("").push_back(std::make_pair("", value._pt));
}

void JsonObject::JsonValue::remove(const string& key){
    this->_pt.erase(key);
}

template<typename T>
void JsonObject::JsonValue::add(const string &key, const T& value){
    this->_pt.add(key,value);
}

template<typename T>
T JsonObject::JsonValue::as() {
	T value = this->_pt.get < T > ("");
	return value;
}

template<typename T>
vector<T> JsonObject::JsonValue::asArray() {
	vector<T> array;

	BOOST_FOREACH(boost::property_tree::ptree::value_type & v, this->_pt)
	{
		array.push_back(
				boost::lexical_cast < T > (v.second.get_value<string>()));
	}
	return array;
}

vector<JsonObject::JsonValue> JsonObject::JsonValue::asArray() {
	vector<JsonValue> array;
	BOOST_FOREACH(boost::property_tree::ptree::value_type & v, this->_pt)
	{
		array.push_back(JsonValue(v.second));
	}
	return array;
}

template<typename T>
JsonObject::JsonValue& JsonObject::JsonValue::operator=(const T value) {
	this->_pt.put("", value);
	return *this;
}

JsonObject::JsonValue& JsonObject::JsonValue::operator=(
		const JsonValue &value) {
	this->_pt = value._pt;
	return *this;
}

template<typename T>
JsonObject::JsonValue& JsonObject::JsonValue::operator=(
		const vector<T> &value) {
	this->_pt.clear();
	boost::property_tree::ptree child;
	boost::property_tree::ptree &pArray = this->_pt;
	for (size_t i = 0; i < value.size(); i++) {
		child.put("", value[i]);
		pArray.push_back(std::make_pair("", child));
	}
	return *this;
}

JsonObject::JsonValue::operator string() {
	if(this->_pt.size()==0)
		return this->_pt.get_value<string>("");
	std::stringstream ss;
	boost::property_tree::write_json(ss, this->_pt.get_child(""));
	return ss.str();
}

size_t JsonObject::JsonValue::size(){
	return this->_pt.size();
}

bool JsonObject::JsonValue::exist(const string &key) {
	return this->_pt.find(key) != this->_pt.not_found();
}

