#pragma once
#ifndef _JsonHandler_h_
#define _JsonHandler_h_

/// c++ libraries
#include <string>
#include <memory>
#include <vector>

/// rapid libraries
#include <QString>
#include "rapidjson/document.h"


class JsonHandler
{
private:
    rapidjson::Document handler;

private:
    bool is_list(std::string key);

public:
    virtual ~JsonHandler();

    enum ValueType {
        NoneEntity,

        VaccumValue,
        BooleanValue,
        IntegerValue,
        DoubleValue,
        StringValue,

        EmptyList,
        VaccumList,
        BooleanList,
        IntegerList,
        DoubleList,
        StringList,
        ArrayList,
        JsonList,

        JsonObject
    };

public:

    /*-------------------------------------------------------------------------*/

    /// <summary>
    /// default constructor
    /// </summary>
    explicit JsonHandler();

    /*-------------------------------------------------------------------------*/

    std::string to_str(bool well_format=false);

    bool has_item(std::string key);

    std::vector<std::string> keys();

    ValueType item_type(std::string key);

    void remove(std::string key);

    void clear();

    void from_json(std::string str);

    /*-------------------------------------------------------------------------*/

    JsonHandler& set_bool(std::string key, bool b);

    bool get_bool(std::string key);


    JsonHandler& set_int(std::string key, int n);

    int get_int(std::string key);


    JsonHandler& set_double(std::string key, double n);

    double get_double(std::string key);


    JsonHandler& set_string(std::string key, std::string str);

    const char* get_string(std::string key);


    JsonHandler& set_null(std::string key);

    bool is_null(std::string key);

    /*-------------------------------------------------------------------------*/

    // { "foo" : [v1, v2, v3, v4, v5, ..., vn]}
    JsonHandler& set_bool_list(std::string key, bool list[], int size);

    std::vector<bool> get_bool_list(std::string key);


    // { "foo" : [v1, v2, v3, v4, v5, ..., vn]}
    JsonHandler& set_int_list(std::string key, int list[], int size);

    std::vector<int> get_int_list(std::string key);


    // { "foo" : [v1, v2, v3, v4, v5, ..., vn]}
    JsonHandler& set_double_list(std::string key, double list[], int size);

    std::vector<double> get_double_list(std::string key);


    // { "foo" : [v1, v2, v3, v4, v5, ..., vn]}
    JsonHandler& set_string_list(std::string skey, const char* list[], int elems);

    std::vector<std::string> get_string_list(std::string key);


    // { "foo" : {"fo1":"va1", "fo2":"va2", ..., "fon":"van"}}
    JsonHandler& set_json(std::string key, std::string json);

    std::string get_json(std::string key);


    // Json handler as sub json string
    JsonHandler& set_json(std::string key, JsonHandler& json);


    // { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
    JsonHandler& set_multi_int_lists(std::string key, std::vector<std::vector<int>> multi);

    std::vector<std::vector<int>> get_multi_int_lists(std::string key);


    // { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
    JsonHandler& set_multi_bool_lists(std::string key, std::vector<std::vector<bool>> multi);

    std::vector<std::vector<bool>> get_multi_bool_lists(std::string key);


    // { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
    JsonHandler& set_multi_double_lists(std::string key, std::vector<std::vector<double>> multi);

    std::vector<std::vector<double>> get_multi_double_lists(std::string key);


    // { "foo" : [[va1, va2, va3, ..., van], [vb1, vb2, vb3, ..., vbn], ... [vn1, vn2, vn3, ..., vnn]]}
    JsonHandler& set_multi_string_lists(std::string key, std::vector<std::vector<std::string>> multi);

    std::vector<std::vector<std::string>> get_multi_string_lists(std::string key);


    // { "foo" : [{"fo1": ...}, {"fo2": ...}, ... {"fon": ...}]}
    JsonHandler& set_multi_json_lists(std::string key, std::vector<std::string> multi);

    JsonHandler& set_multi_json_lists(std::string key, std::vector<JsonHandler> multi);

    std::vector<std::string> get_multi_json_lists(std::string key);
};

#endif
