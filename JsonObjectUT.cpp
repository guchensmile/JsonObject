/*
 * JsonObjectUT.cpp
 *
 *  Created on: Sep 10, 2016
 *      Author: zwl
 */

//#include "../JsonObject.h"
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "JsonObject.hpp"
using std::cout;
using std::endl;

void testBase() {
	JsonObject js("{"
			"\"int\": 0,"
			"\"string\": \"get a string!\""
			"}");
	cout << string(js) << endl;
	cout << js["int"].as<int>() << endl;
	cout << js["string"].as<string>() << endl;
}

void testOperator() {
	JsonObject js("{\"root\":"
			"{"
			"\"l2\":"
			"{"
			"\"l3_1\":0,"
			"\"l3_2\":\"1\""
			"}"
			"}"
			"}");
	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	cout << string(js) << endl;
	cout << string(js["root"]) << endl;
	cout << string(js["root.l2"]) << endl;
	cout << js["root.l2"].as<string>() << endl;
	cout << js["root.l2.l3_1"].as<string>() << endl;
	cout << js["root.l2.l3_2"].as<int>() << endl;
}

void testOperatorNesting() {
	JsonObject js("{\"root\":"
			"{"
			"\"l2\":"
			"{"
			"\"l3_1\":0,"
			"\"l3_2\":\"1\""
			"}"
			"}"
			"}");
	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	cout << string(js) << endl;
	cout << string(js["root"]) << endl;
	cout << string(js["root"]["l2"]) << endl;
	cout << js["root"]["l2"].as<string>() << endl;
	cout << js["root"]["l2"]["l3_1"].as<string>() << endl;
	cout << js["root"]["l2"]["l3_2"].as<int>() << endl;
}

void testArrayGet() {
	JsonObject js("{\"root\":"
			"{"
			"\"l2_1\":"
			"{"
			"\"l3_1\":[0,1],"
			"\"l3_2\":[\"s1\",\"s2\"]"
			"},"
			"\"l2_2\":"
			"["
			"{"
			"\"l3_1\":\"item1\","
			"\"l3_2\":\"item2\""
			"},"
			"{"
			"\"l3_1\":\"item1\","
			"\"l3_2\":\"item2\""
			"}"
			"]"
			"}"
			"}");
	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	cout << string(js["root"]["l2_1"]) << endl;
	cout << js["root"]["l2_1"].as<string>() << endl;
	vector<int> array_int = js["root"]["l2_1"]["l3_1"].asArray<int>();
	for (size_t i = 0; i < array_int.size(); i++) {
		cout << array_int[i] << endl;
	}
	vector < string > array_string =
			js["root"]["l2_1"]["l3_2"].asArray<string>();
	for (size_t i = 0; i < array_string.size(); i++) {
		cout << array_string[i] << endl;
	}
	vector<JsonObject::JsonValue> array_object = js["root"]["l2_2"].asArray();
	for (size_t i = 0; i < array_object.size(); i++) {
		cout << string(array_object[i]) << endl;
		cout << array_object[i]["l3_1"].as<string>() << endl;
		cout << array_object[i]["l3_2"].as<string>() << endl;
	}
}

void testIndex(){
	JsonObject js("{\"root\":"
				"{"
				"\"l2_1\":"
				"{"
				"\"l3_1\":[0,1],"
				"\"l3_2\":[\"s1\",\"s2\"]"
				"},"
				"\"l2_2\":"
				"["
				"{"
				"\"l3_1\":\"item1\","
				"\"l3_2\":\"item2\""
				"},"
				"{"
				"\"l3_1\":\"item1\","
				"\"l3_2\":\"item2\""
				"}"
				"]"
				"}"
				"}");
	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	cout << js["root"]["l2_1"]["l3_1"][0].as<int>() << endl;
	cout << js["root"]["l2_1"]["l3_1"][1].as<int>() << endl;
	cout << js["root"]["l2_2"][1]["l3_2"].as<string>() << endl;
}

void testArraySet() {
	JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2_name\":\"array\","
			"\"l2_content1\":[],"
			"\"l2_content2\":\"this should be array\""
			"}"
			"}");

	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	uint32_t array_int[] = { 1, 2, 1, 3, 0 };
	js["root.l2_name"] = "set_array";
	js["root.l2_content1"] = vector < uint32_t > (array_int, array_int + 5);
	cout << string(js["root"]) << endl;
	cout << js["root"].size() << endl;
	cout << string(js["root.l2_name"]) << endl;
	cout << js["root.l2_name"].size() << endl;
	cout << string(js["root.l2_content1"]) << endl;
	cout << js["root.l2_content1"].size() << endl;
	vector < uint32_t > array_int_copy1 = js["root"]["l2_content1"].asArray<
			uint32_t>();
	for (size_t i = 0; i < array_int_copy1.size(); i++) {
		cout << array_int_copy1[i] << endl;
	}

	js["root.l2_content2"] = vector<float>();
	cout << string(js["root.l2_content2"]) << endl;
	cout << js["root.l2_content2"].size() << endl;
	vector<float> array_int_copy2 = js["root"]["l2_content2"].asArray<float>();
	for (size_t i = 0; i < array_int_copy2.size(); i++) {
		cout << array_int_copy2[i] << endl;
	}
	cout << string(js) << endl;
}

void testArraySet2() {
	JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2_name\":\"array\","
			"\"l2_content\":\"\""
			"}"
			"}");

	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	JsonObject js1("{"
			"\"l2_name\":\"array\","
			"\"l2_content\":\"\""
			"}");
	vector<JsonObject> array_json;
	for (size_t i = 0; i < 3; i++) {
		array_json.push_back(js1);
	}
	cout << string(js["root"]) << endl;
	cout << js["root"].size() << endl;
	cout << string(js["root.l2_name"]) << endl;
	cout << js["root.l2_name"].size() << endl;
	cout << string(js["root.l2_content"]) << endl;
	cout << js["root.l2_content"].size() << endl;
	vector<JsonObject::JsonValue> array_int =
			js["root"]["l2_content"].asArray();
	for (size_t i = 0; i < array_int.size(); i++) {
		cout << string(array_int[i]) << endl;
	}
	cout << string(js) << endl;
}

void testClear() {
	JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2_name\":\"array\","
			"\"l2_content\":[1,2,3]"
			"}"
			"}");

	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	cout << string(js["root.l2_name"]) << endl;
	js["root.l2_name"].clear();
	cout << string(js["root.l2_name"]) << endl;
	cout << string(js["root.l2_content"]) << endl;
	js["root.l2_content"].clear();
	cout << string(js["root.l2_content"]) << endl;
	cout << string(js["root"]) << endl;
	js["root"].clear();
	cout << string(js["root"]) << endl;
}

void testAppend() {
	JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2_name\":\"array\","
			"\"l2_content\":[]"
			"}"
			"}");
	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	js["root.l2_content"].append("s1");
	js["root.l2_content"].append("s2");
	cout << string(js) << endl;
	vector < string > array_string = js["root"]["l2_content"].asArray<string>();
	for (size_t i = 0; i < array_string.size(); i++) {
		cout << array_string[i] << endl;
	}
}

void testAppend2() {
	JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2_name\":\"array\","
			"\"l2_content\":[]"
			"}"
			"}");

	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	JsonObject js1("{\"string\":\"s1\"}");
	cout << string(js1) << endl;
	JsonObject js2("{\"string\":\"s2\"}");
	cout << string(js2) << endl;
	js["root.l2_content"].append(js1);
	js["root.l2_content"].append(js2.value());
	cout << string(js) << endl;
	vector<JsonObject::JsonValue> array_js = js["root"]["l2_content"].asArray();
	for (size_t i = 0; i < array_js.size(); i++) {
		cout << string(array_js[i]) << endl;
	}
	//TODO add json with key
	JsonObject js_copy("{"
			"\"root2\":"
			"{"
			"\"l2_name\":\"array\","
			"\"l2_content\":[]"
			"}"
			"}");
	js.append(js_copy);
	cout << string(js) << endl;
}

void testAppend3() {
	JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2_name\":\"array\","
			"\"l2_content\":[]"
			"}"
			"}");

	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	vector < ulong > tmp_ids;
	tmp_ids.push_back(0);
	tmp_ids.push_back(1);
	js["root.l2_content"] = tmp_ids;
	cout << string(js) << endl;
}

void test2String() {
	JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2_name\":\"array\","
			"\"l2_content\":"
			"{"
			"\"l3\":\"l3_string\""
			"}"
			"}"
			"}");

	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	cout << js["root.l2_content.l3"].as<string>() << endl;
}

void testPointer() {
	JsonObject *js_pointer = new JsonObject("{"
			"\"root\":"
			"{"
			"\"l2_name\":\"array\","
			"\"l2_content\":"
			"{"
			"\"l3\":[]"
			"}"
			"}"
			"}");

	if (!js_pointer->isValidated()) {
		throw ReadJsonException("invalid json format!");
	}
	(*(js_pointer))["root.l2_content.l3"] = vector<int>();
	cout << string(*(js_pointer)) << endl;
}

void testBool() {
	JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2_false\":false,"
			"\"l2_content\":"
			"{"
			"\"l3_true\":true"
			"}"
			"}"
			"}");

	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}

	cout << js["root.l2_false"].as<bool>() << endl;
	cout << js["root.l2_content.l3_true"].as<bool>() << endl;

	js["root.l2_false"] = true;
	js["root.l2_content.l3_true"] = false;
	cout << js["root.l2_false"].as<bool>() << endl;
	cout << js["root.l2_content.l3_true"].as<bool>() << endl;
}

void testFloat() {
	JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2_int\":1,"
			"\"l2_content\":"
			"{"
			"\"l3_float\":1.0"
			"}"
			"}"
			"}");

	if (!js.isValidated()) {
		throw ReadJsonException("invalid json format!");
	}

	cout << js["root.l2_int"].as<float>() << endl;
	cout << js["root.l2_content.l3_float"].as<float>() << endl;

	js["root.l2_int"] = 1.1;
	js["root.l2_content.l3_float"] = 0;
	cout << js["root.l2_int"].as<float>() << endl;
	cout << js["root.l2_content.l3_float"].as<float>() << endl;
}

void testRemove(){
    JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2\":1,"
			"\"l2_another\":2"
			"}"
			"}");

    cout<<string(js)<<endl;
    js["root"].remove("l2_another");
    cout<<string(js)<<endl;
}

void testAdd(){
    JsonObject js("{"
			"\"root\":"
			"{"
			"\"l2\":1"
			"}"
			"}");
    cout<<string(js)<<endl;
    js["root"]["l2"].add("has_brother",false);
    cout<<string(js)<<endl;
    js.add("root_brother","root2");
    cout<<string(js)<<endl;
}

void testException() {
	try {
		JsonObject js("{"
				"\"int\": 0,"
				"\"string\": "//try "\"string\": \"\""
				"}");
		cout << string(js) << endl;
		cout << js["int"].as<int>() << endl;
	} catch (ReadJsonException &e) {
		cout << e.what() << endl;
	}
	try {
		//wrong js format, last element should no ,
		JsonObject js("{"
				"\"int\": 0,"
				"\"string\": \"haha\","//try "\"string\": \"haha\""
				"}");
		cout << string(js) << endl;
		cout << js["string"].as<string>() << endl;
	} catch (ReadJsonException &e) {
		cout << e.what() << endl;
	}
	try {
		JsonObject js("{"
				"\"array_int\": [0,1],"
				"\"array_string\": [\"first\",\"second\"]"
				"}");
		cout << string(js) << endl;
		cout << js["array_int"][2].as<int>() << endl;
	} catch (ReadJsonException &e) {
		cout << e.what() << endl;
	}
	try {
		JsonObject js("{"
				"\"array_int\": [0,1],"
				"\"array_string\": [\"first\",\"second\"]"
				"}");
		cout << string(js) << endl;
		cout << js["array_string"][2].as<string>() << endl;
	} catch (ReadJsonException &e) {
		cout << e.what() << endl;
	}
}

int main() {
	int i = 0;
	cout << "testBase:" << i++ << endl;
	testBase();
	cout << "testOperator:" << i++ << endl;
	testOperator();
	cout << "testOperatorNesting:" << i++ << endl;
	testOperatorNesting();
	cout << "testArrayGet:" << i++ << endl;
	testArrayGet();
	cout << "testIndex" << i++ << endl;
	testIndex();
	cout << "testArraySet:" << i++ << endl;
	testArraySet();
	cout << "testArraySet2:" << i++ << endl;
	testArraySet2();
	cout << "testClear:" << i++ << endl;
	testClear();
	cout << "testAppend:" << i++ << endl;
	testAppend();
	cout << "testAppend2:" << i++ << endl;
	testAppend2();
	cout << "testAppend3:" << i++ << endl;
	testAppend3();
	cout << "test2String:" << i++ << endl;
	test2String();
	cout << "testPointer:" << i++ << endl;
	testPointer();
	cout << "testBool:" << i++ << endl;
	testBool();
	cout << "testFloat:" << i++ << endl;
	testFloat();
	cout << "testRemove:" << i++ << endl;
	testRemove();
	cout << "testAdd:" << i++ << endl;
	testAdd();
	cout << "testException:" << i++ << endl;
	testException();
}
