#include "CJson.h"
#include <string.h>
#include <memory.h>

/// rapid libraries
#include <frame/rapidjson/document.h>
#include <frame/rapidjson/prettywriter.h>
#include <frame/rapidjson/writer.h>

#include <QFile>
#include <QDebug>


using namespace std;
using namespace rapidjson;



JsonHandler::~JsonHandler() {}


JsonHandler::JsonHandler(const char* str) { handler.Parse(str); }


JsonHandler::JsonHandler(const QString &name)
{
    // parse an empty string
    if (name.isEmpty()) {
        handler.Parse("{}");
    }

    // open file
    QFile file(name);
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
    } else {
        qDebug() << "File open!";
    }

    // load content from file
    QString value = file.readAll();
    file.close();

    // parse json string
    handler.Parse(value.toUtf8());
}

void JsonHandler::from_json(std::string str)
{
    handler.Parse(str.c_str());
};


string JsonHandler::to_str(bool well_format)
{
    if (well_format) {
        StringBuffer buffer;
        PrettyWriter<StringBuffer> writer(buffer);
        handler.Accept(writer);

        return std::string(buffer.GetString());
    }
    else {
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        handler.Accept(writer);

        return std::string(buffer.GetString());
    }
}


bool JsonHandler::has_item(string key)
{
    return handler.HasMember(key.c_str());
}


bool JsonHandler::is_list(std::string key)
{
    return has_item(key) && handler[key.c_str()].IsArray();
}


JsonHandler& JsonHandler::set_null(std::string k)
{
    if (!has_item(k)) {
        // create a pair value
        Value val;
        Value key(k.c_str(), k.length(), handler.GetAllocator());

        // add val to document
        handler.AddMember(key, val, handler.GetAllocator());
    }
    else {
        Value& val = handler[k.c_str()];
        val.SetNull();
    }

    // return this
    return *this;
}


bool JsonHandler::is_null(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].IsNull();
    }

    return false;
}


JsonHandler& JsonHandler::set_bool(std::string k, bool b)
{
    if (!has_item(k)) {
        // create a pair value
        Value val(true);
        Value key(k.c_str(), k.size(), handler.GetAllocator());

        // add val to document
        handler.AddMember(key, val, handler.GetAllocator());
    }
    else {
        Value& val = handler[k.c_str()];
        val.SetBool(b);
    }

    // return this
    return *this;
}


bool JsonHandler::get_bool(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].GetBool();
    }

    return false;
}


JsonHandler& JsonHandler::set_int(std::string k, int n)
{
    if (!has_item(k)) {
        // create a pair value
        Value val(n);
        Value key(k.c_str(), k.size(), handler.GetAllocator());

        // add val to document
        handler.AddMember(key, val, handler.GetAllocator());
    }
    else {
        Value& val = handler[k.c_str()];
        val.SetInt(n);
    }

    // return this
    return *this;
}


int JsonHandler::get_int(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].GetInt();
    }

    return 0;
}


JsonHandler& JsonHandler::set_double(std::string k, double n)
{
    if (!has_item(k)) {
        // create a pair value
        Value val(n);
        Value key(k.c_str(), k.size(), handler.GetAllocator());

        // add val to document
        handler.AddMember(key, val, handler.GetAllocator());
    }
    else {
        Value& val = handler[k.c_str()];
        val.SetDouble(n);
    }

    // return this
    return *this;
}


double JsonHandler::get_double(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].GetDouble();
    }

    return 0;
}


JsonHandler& JsonHandler::set_string(std::string k, std::string str)
{
    if (!has_item(k)) {
        // create a pair value
        Value val(str.c_str(), str.length(), handler.GetAllocator());
        Value key(k.c_str(), k.size(), handler.GetAllocator());

        // add val to document
        handler.AddMember(key, val, handler.GetAllocator());
    }
    else {
        Value& val = handler[k.c_str()];
        val.SetString(str.c_str(), str.length(), handler.GetAllocator());
    }

    // return this
    return *this;
}


const char* JsonHandler::get_string(std::string key)
{
    if (has_item(key)) {
        return handler[key.c_str()].GetString();
    }

    return nullptr;
}


void JsonHandler::remove(std::string key)
{
    if (has_item(key)) {
        handler.RemoveMember(key.c_str());
    }
}


void JsonHandler::clear() { handler.RemoveAllMembers(); }


vector<std::string> JsonHandler::keys()
{
    vector<string> keys;

    // iterate the given json object and add each item to handler
    rapidjson::Value::MemberIterator m;
    for (m = handler.MemberBegin(); m != handler.MemberEnd(); m++) {

        std::string str(m->name.GetString());
        keys.push_back(str);
    }

    return keys;
}

JsonHandler::ValueType JsonHandler::item_type(std::string key)
{
    if (!has_item(key)) return ValueType::NoneEntity;

    Value& val = handler[key.c_str()];
    if (val.IsNull()) return ValueType::VaccumValue;

    if (val.IsBool()) return ValueType::BooleanValue;
    if (val.IsInt()) return ValueType::IntegerValue;
    if (val.IsDouble()) return ValueType::DoubleValue;
    if (val.IsString()) return ValueType::StringValue;

    if (is_list(key) and val.Capacity() <= 0) return ValueType::EmptyList;
    if (is_list(key) and val[0].IsNull()) return ValueType::VaccumList;

    if (is_list(key) and val[0].IsBool()) return ValueType::BooleanList;
    if (is_list(key) and val[0].IsInt()) return ValueType::IntegerList;
    if (is_list(key) and val[0].IsDouble()) return ValueType::DoubleList;
    if (is_list(key) and val[0].IsString()) return ValueType::StringList;

    if (is_list(key) and val[0].IsArray()) return ValueType::ArrayList;
    if (is_list(key) and val[0].IsObject()) return ValueType::JsonList;

    if (val.IsObject()) return ValueType::JsonObject;

    return ValueType::NoneEntity;
}


template<typename T>
void generic_append_array(Document& handler, string k, T list[], int size)
{
    // create an object type
    Value key(k.c_str(), k.size(), handler.GetAllocator());

    // to get the allocator handler to iteratively append the values to the value object
    Document::AllocatorType& allocator = handler.GetAllocator();
    // value object to stores the array
    Value value(rapidjson::kArrayType);

    // iterative appending the values
    for (int i = 0; i < size; i++) {
        value.PushBack(list[i], allocator);
    }

    // add the value to the document
    handler.AddMember(key, value, allocator);
}


template<typename T>
void generic_update_array(Document& handler, string k, T list[], int size)
{
    // remove the original key from json
    handler.RemoveMember(k.c_str());

    // re-call
    generic_append_array(handler, k, list, size);
}


JsonHandler& JsonHandler::set_bool_list(std::string key, bool list[], int size)
{
    if (!has_item(key)) {
        generic_append_array<bool>(handler, key, list, size);
    }
    else {
        generic_update_array<bool>(handler, key, list, size);
    }

    // return this
    return *this;
}


std::vector<bool> JsonHandler::get_bool_list(std::string key)
{
    vector<bool> list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            list.push_back(a[i].GetBool());
        }
    }

    return list;
}


JsonHandler& JsonHandler::set_int_list(std::string key, int list[], int size)
{
    if (!has_item(key)) {
        generic_append_array<int>(handler, key, list, size);
    }
    else {
        generic_update_array<int>(handler, key, list, size);
    }

    // return this
    return *this;
}


std::vector<int> JsonHandler::get_int_list(std::string key)
{
    vector<int> list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            list.push_back(a[i].GetInt());
        }
    }

    return list;
}


JsonHandler& JsonHandler::set_double_list(std::string key, double list[], int size)
{
    if (!has_item(key)) {
        generic_append_array<double>(handler, key, list, size);
    }
    else {
        generic_update_array<double>(handler, key, list, size);
    }

    // return this
    return *this;
}

std::vector<double> JsonHandler::get_double_list(std::string key)
{
    vector<double> list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            list.push_back(a[i].GetDouble());
        }
    }

    return list;
}

JsonHandler& JsonHandler::set_string_list(std::string k,
    const char* list[], int elems)
{
    if (has_item(k)) { remove(k); }

    // create an object key
    Value key(k.c_str(), k.size(), handler.GetAllocator());

    // to get the allocator handler to iteratively append the values to the value object
    Document::AllocatorType& allocator = handler.GetAllocator();

    // value object to stores the array
    Value value(kArrayType);

    // iterative appending the values
    for (int i = 0; i < elems; i++) {
        Value item(list[i], strlen(list[i]), handler.GetAllocator());
        value.PushBack(item, allocator);
    }

    // add the value to the document
    handler.AddMember(key, value, allocator);

    // return this
    return *this;
}

std::vector<std::string> JsonHandler::get_string_list(std::string key)
{
    vector<string> list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            string str(a[i].GetString());
            list.push_back(str);
        }
    }

    return list;
}

JsonHandler& JsonHandler::set_json(std::string k, std::string json)
{
    if (has_item(k)) { remove(k); }

    // create key-value pair
    Value key(k.c_str(), k.size(), handler.GetAllocator());
    Value value(kObjectType);

    // document parse the json
    Document sub_json;
    sub_json.Parse(json.c_str());

    // copy data from document
    value.CopyFrom(sub_json, handler.GetAllocator());

    // add the value to the document
    handler.AddMember(key, value, handler.GetAllocator());

    return *this;
}

JsonHandler& JsonHandler::set_json(std::string key, JsonHandler& json)
{
    return set_json(key, json.to_str());
}

std::string JsonHandler::get_json(std::string key)
{
    if (has_item(key)) {
        Value& val = handler[key.c_str()];

        StringBuffer buffer;
        PrettyWriter<StringBuffer> writer(buffer);
        val.Accept(writer);

        return std::string(buffer.GetString());
    }

    return "{}";
}

template<typename T>
std::vector<T> generic_list_from_value(const Value& val) {
    std::vector<T> list;

    for (SizeType i = 0; i < val.Size(); i++) {
        if (strcmp(typeid(T).name(), typeid(int).name()) == 0) {
            list.push_back(val[i].GetInt());
            continue;
        }
        if (strcmp(typeid(T).name(), typeid(double).name()) == 0) {
            list.push_back(val[i].GetDouble());
            continue;
        }
        if (strcmp(typeid(T).name(), typeid(double).name()) == 0) {
            list.push_back(val[i].GetBool());
            continue;
        }
    }

    return list;
}


template<typename T>
void generic_append_multi_list(Document::AllocatorType& allocator, Value &val, std::vector<T> elems) {
    Value value(rapidjson::kArrayType);

    // push items to inner list first
    for (auto iter = elems.begin(); iter != elems.end(); iter++) {
        value.PushBack(*iter, allocator);
    }

    // push updated inner list to outter list
    val.PushBack(value, allocator);
}


template<typename T>
void generic_append_multi_arrays(Document& handler, string k, std::vector<std::vector<T>> multi)
{
    // create an object type
    Value key(k.c_str(), k.size(), handler.GetAllocator());

    // to get the allocator handler to iteratively append the values to the value object
    Document::AllocatorType& allocator = handler.GetAllocator();
    // value object to stores the array
    Value value(rapidjson::kArrayType);

    // iterative appending the values
    for (auto iter = multi.begin(); iter != multi.end(); iter++) {
        generic_append_multi_list(allocator, value, *iter);
    }

    // add the value to the document
    handler.AddMember(key, value, allocator);
}



// { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
JsonHandler& JsonHandler::set_multi_int_lists(std::string key, std::vector<std::vector<int>> multi)
{
    if (!has_item(key)) {
        generic_append_multi_arrays<int>(handler, key, multi);
    }
    else {
        // remove the original key from json
        handler.RemoveMember(key.c_str());

        generic_append_multi_arrays<int>(handler, key, multi);
    }

    // return this
    return *this;
};

std::vector<std::vector<int>> JsonHandler::get_multi_int_lists(std::string key)
{
    std::vector<std::vector<int>> multi_list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            std::vector<int> list = generic_list_from_value<int>(a[i]);
            multi_list.push_back(list);
        }
    }

    return multi_list;
};


// { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
JsonHandler& JsonHandler::set_multi_bool_lists(std::string key, std::vector<std::vector<bool>> multi)
{
    if (!has_item(key)) {
        generic_append_multi_arrays<bool>(handler, key, multi);
    }
    else {
        // remove the original key from json
        handler.RemoveMember(key.c_str());

        generic_append_multi_arrays<bool>(handler, key, multi);
    }

    // return this
    return *this;
};

std::vector<std::vector<bool>> JsonHandler::get_multi_bool_lists(std::string key)
{
    std::vector<std::vector<bool>> multi_list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            std::vector<bool> list = generic_list_from_value<bool>(a[i]);
            multi_list.push_back(list);
        }
    }

    return multi_list;
};


// { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
JsonHandler& JsonHandler::set_multi_double_lists(std::string key, std::vector<std::vector<double>> multi)
{
    if (!has_item(key)) {
        generic_append_multi_arrays<double>(handler, key, multi);
    }
    else {
        // remove the original key from json
        handler.RemoveMember(key.c_str());

        generic_append_multi_arrays<double>(handler, key, multi);
    }

    // return this
    return *this;
};

std::vector<std::vector<double>> JsonHandler::get_multi_double_lists(std::string key)
{
    std::vector<std::vector<double>> multi_list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            std::vector<double> list = generic_list_from_value<double>(a[i]);
            multi_list.push_back(list);
        }
    }

    return multi_list;
};


JsonHandler& JsonHandler::set_multi_string_lists(std::string k, std::vector<std::vector<std::string>> multi)
{
    if (has_item(k)) { remove(k); }

    // create an object key
    Value key(k.c_str(), k.size(), handler.GetAllocator());

    // to get the allocator handler to iteratively append the values to the value object
    Document::AllocatorType& allocator = handler.GetAllocator();

    // value object to stores the array
    Value value(kArrayType);

    // iterative appending the values
    for (auto iter = multi.begin(); iter != multi.end(); iter++) {
        Value list(kArrayType);

        // append item to list
        for (auto inner = iter->begin(); inner != iter->end(); inner++) {
            std::string temp(*inner);
            Value item(temp.c_str(), temp.length(), allocator);
            list.PushBack(item, allocator);
        }

        // append list to value
        value.PushBack(list, allocator);
    }

    // add the value to the document
    handler.AddMember(key, value, allocator);

    // return this
    return *this;
};

std::vector<std::vector<std::string>> JsonHandler::get_multi_string_lists(std::string key)
{
    std::vector<std::vector<std::string>> multi_list;

    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {

            std::vector<std::string> list;
            const Value& inner = a[i];

            for (SizeType j = 0; j < inner.Size(); j++) {
                  const char * elem = inner[j].GetString();
                  list.push_back(std::string(elem));
            }

            multi_list.push_back(list);
        }
    }

    return multi_list;
};


// { "foo" : [{"fo1": ...}, {"fo2": ...}, ... {"fon": ...}]}
JsonHandler& JsonHandler::set_multi_json_lists(std::string k, std::vector<std::string> multi)
{
    if (has_item(k)) { remove(k); }

    // create an object key
    Value key(k.c_str(), k.size(), handler.GetAllocator());

    // to get the allocator handler to iteratively append the values to the value object
    Document::AllocatorType& allocator = handler.GetAllocator();

    // value object to stores the array
    Value value(kArrayType);

    // append sub json strings to value
    for (auto iter = multi.begin(); iter != multi.end(); iter++) {
        Document sub_json;
        sub_json.Parse(iter->c_str());
        value.PushBack(sub_json, allocator);
    }

    // add the value to the document
    handler.AddMember(key, value, allocator);

    // return this
    return *this;
};

std::vector<std::string> JsonHandler::get_multi_json_lists(std::string key)
{
    std::vector<std::string> multi_json;
    if (is_list(key)) {
        const Value& a = handler[key.c_str()];

        for (SizeType i = 0; i < a.Size(); i++) {
            const Value& val = a[i];

            rapidjson::StringBuffer sbBuf;
            rapidjson::Writer<rapidjson::StringBuffer> jWriter(sbBuf);
            val.Accept(jWriter);

            std::string json(sbBuf.GetString());
            multi_json.push_back(json);
        }
    }

    return multi_json;
};
