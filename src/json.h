/*
 *  This file is part of Poedit (https://poedit.net)
 *
 *  Copyright (C) 2016-2025 Vaclav Slavik
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a
 *  copy of this software and associated documentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef Poedit_json_h
#define Poedit_json_h

#include "str_helpers.h"

#include <boost/throw_exception.hpp>

#define JSON_USE_IMPLICIT_CONVERSIONS 0
#define JSON_THROW_USER(exception) boost::throw_exception(exception)

#ifdef HAVE_NLOHMANN_JSON_HPP
 #include <nlohmann/json.hpp>
#else
 #include "../deps/json/single_include/nlohmann/json.hpp"
#endif

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

// Implement conversion to and from std::wstring:
namespace nlohmann
{

template<>
struct adl_serializer<std::wstring>
{
    static void to_json(json& j, const std::wstring& s)
    {
        j = str::to_utf8(s);
    }

    static void from_json(const json& j, std::wstring& s)
    {
        s = str::to_wstring(j.get<std::string>());
    }
};

} // namespace nlohmann


/**
    Helper to get value from JSON key falling back to @a default.

    This differs from json::value() in that it yields the default even
    if the response contains that key, but has it set to null.
 */
template <class T>
inline T get_value(const json& j, const char *key, const T& defaultValue)
{
    auto i = j.find(key);
    if (i == j.end() || i->is_null())
        return defaultValue;
    return i->get<T>();
}

inline std::string get_value(const json& j, const char *key, const char *defaultValue)
{
    return get_value<std::string>(j, key, defaultValue);
}

#endif // Poedit_json_h
