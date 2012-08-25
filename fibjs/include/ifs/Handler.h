/***************************************************************************
 *   Copyright (C) 2012 by Leo Hoo                                         *
 *   lion@9465.net                                                         *
 *                                                                         *
 ***************************************************************************/

#ifndef _Handler_base_H_
#define _Handler_base_H_

/**
 @author Leo Hoo <lion@9465.net>
 */

#include "../object.h"

namespace fibjs
{

class object_base;

class Handler_base : public object_base
{
public:
	// Handler_base
	virtual result_t invoke(obj_ptr<object_base>& v, obj_ptr<Handler_base>& retVal, exlib::AsyncEvent* ac) = 0;

	DECLARE_CLASSINFO(Handler_base);

public:
	static v8::Handle<v8::Value> s_invoke(const v8::Arguments& args);

public:
	ASYNC_MEMBER2(Handler_base, invoke);
	ASYNC_VALUEBACK1(Handler_base, invoke, obj_ptr<Handler_base>);
};

}


namespace fibjs
{
	inline ClassInfo& Handler_base::class_info()
	{
		static ClassData::ClassMethod s_method[] = 
		{
			{"invoke", s_invoke}
		};

		static ClassData s_cd = 
		{ 
			"Handler", NULL, 
			1, s_method, 0, NULL, 0, NULL, NULL, NULL,
			&object_base::class_info()
		};

		static ClassInfo s_ci(s_cd);
		return s_ci;
	}


	inline v8::Handle<v8::Value> Handler_base::s_invoke(const v8::Arguments& args)
	{
		obj_ptr<Handler_base> vr;

		METHOD_INSTANCE(Handler_base);
		METHOD_ENTER(1, 1);

		ARG(obj_ptr<object_base>, 0);

		hr = pInst->ac_invoke(v0, vr);

		METHOD_RETURN();
	}

}

#endif

