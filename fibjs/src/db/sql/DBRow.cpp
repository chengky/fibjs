/*
 * DBRow.cpp
 *
 *  Created on: Jul 27, 2012
 *      Author: lion
 */

#include "DBRow.h"

namespace fibjs
{

result_t DBRow::_indexed_getter(uint32_t index, v8::Local<v8::Value> &retVal)
{
    if (index >= m_cols.size())
        return CHECK_ERROR(CALL_E_BADINDEX);

    retVal = m_cols[index];

    return 0;
}

result_t DBRow::_named_getter(const char *property,
                              v8::Local<v8::Value> &retVal)
{
    int32_t i = m_fields->index(property);

    if (i >= 0)
        return _indexed_getter(i, retVal);

    return 0;
}

result_t DBRow::_named_enumerator(v8::Local<v8::Array> &retVal)
{
    m_fields->names(retVal);
    return 0;
}

result_t DBRow::toJSON(const char *key, v8::Local<v8::Value> &retVal)
{
    Isolate* isolate = Isolate::now();
    v8::Local<v8::Object> o = v8::Object::New(isolate->m_isolate);
    int32_t i;

    for (i = 0; i < (int32_t) m_cols.size(); i++)
    {
        std::string &s = m_fields->name(i);
        o->Set(v8::String::NewFromUtf8(isolate->m_isolate, s.c_str(), v8::String::kNormalString,
                                       (int32_t)s.length()), m_cols[i]);
    }

    retVal = o;

    return 0;
}

} /* namespace fibjs */
