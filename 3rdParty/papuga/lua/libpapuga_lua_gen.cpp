/*
* Copyright (c) 2017 Patrick P. Frey
*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
/// \brief Library interface for libpapuga_lua for generating lua bindings
/// \file libpapuga_lua.cpp
#include "papuga/lib/lua_gen.hpp"
#include "private/dll_tags.h"
#include "private/gen_utils.hpp"
#include "fmt/format.h"
#include <string>
#include <cstdio>
#include <cstdarg>
#include <stdexcept>
#include <sstream>

using namespace papuga;

#define INDENT "\t"

static void define_classdefmap(
		std::ostream& out,
		const papuga_InterfaceDescription& descr)
{
	ClassDescriptionMap descrmap = papuga::getClassDescriptionMap( descr);
	out << "static const papuga_lua_ClassDef* g_classidmap[] = { " << std::endl;
	unsigned int cidx = 0;
	ClassDescriptionMap::const_iterator ci = descrmap.begin(), ce = descrmap.end();
	for (; ci != ce; ++ci,++cidx)
	{
		for (; cidx+1 < ci->first; ++cidx)
		{
			out << "{NULL, NULL}";
		}
		out << "{\"" << ci->second.name << "\", " << ci->second.funcname_destructor << "}, ";
	}
	out << "NULL };" << std::endl << std::endl;
	out << "static const papuga_lua_ClassDefMap = { " << cidx << ", g_classidmap };";
}

static void define_method(
		std::ostream& out,
		const papuga_ClassDescription& classdef,
		const papuga_MethodDescription& method)
{
	std::string selfname = (method.self) ? (std::string("\"") + classdef.name + "\""):std::string("NULL");

	out << fmt::format( papuga::cppCodeSnippet( 0,
		"static int l_{funcname}( lua_State *ls)",
		"{",
		"int rt;",
		"papuga_lua_CallArgs arg;",
		"papuga_CallResult retval;",
		"char errorbuf[ 2048];",
		"if (!papuga_lua_init_CallArgs( ls, &arg, {selfname})) papuga_lua_error( ls, \"{classname}.{methodname}\", arg.errcode);",
		"papuga_init_CallResult( &retval, errorbuf, sizeof(errorbuf));",
		"if (!{funcname}( arg.self, &retval, arg.argc, arg.argv)) goto ERROR_CALL;",
		"papuga_lua_destroy_CallArgs( &arg);",
		"rt = papuga_lua_move_CallResult( ls, &retval, &papuga_lua_ClassIdMap, &arg.errcode);",
		"if (rt < 0) papuga_lua_error( ls, \"{classname}.{methodname}\", arg.errcode);",
		"return rt;",
		"ERROR_CALL:",
		"papuga_destroy_CallResult( &retval);",
		"papuga_lua_destroy_CallArgs( &arg);",
		"papuga_lua_error_str( ls, \"{classname}.{methodname}\", errorbuf);",
		"}",
		0),
			fmt::arg("methodname", method.name),
			fmt::arg("classname", classdef.name),
			fmt::arg("selfname", selfname),
			fmt::arg("funcname", method.funcname)
		) << std::endl;
}

static void define_constructor(
		std::ostream& out,
		const papuga_ClassDescription& classdef)
{
	out << fmt::format( papuga::cppCodeSnippet( 0,
		"static int l_new_{classname}( lua_State *ls)",
		"{",
		"int rt;",
		"papuga_lua_CallArgs arg;",
		"papuga_CallResult retval;",
		"char errorbuf[ 2048];",
		"papuga_lua_UserData* udata = papuga_lua_new_userdata( ls, \"{classname}\");",
		"if (!papuga_lua_init_CallArgs( ls, &arg, NULL)) papuga_lua_error( ls, \"{classname}.new\", arg.errcode);",
		"{classname}Impl* objref = {constructor}( arg.argc, arg.argv);",
		"if (!objref)) goto ERROR_CALL;",
		"papuga_lua_destroy_CallArgs( &arg);",
		"papuga_lua_init_UserData( udata, {classid}, objref, {destructor});",
		"return 1;",
		"ERROR_CALL:",
		"papuga_destroy_CallResult( &retval);",
		"papuga_lua_destroy_CallArgs( &arg);",
		"lua_pop(ls, 1);//... pop udata"
		"papuga_lua_error_str( ls, \"{classname}.new\", errorbuf);",
		"}",
		0),
			fmt::arg("classname", classdef.name),
			fmt::arg("classid", classdef.id),
			fmt::arg("constructor", classdef.funcname_constructor),
			fmt::arg("destructor", classdef.funcname_destructor)
		) << std::endl;
}

static void define_methodtable(
		std::ostream& out,
		const papuga_ClassDescription& classdef)
{
	out << fmt::format( papuga::cppCodeSnippet( 0,
			"static const luaL_Reg mt_{classname}[] =", "{", 0),
			fmt::arg("classname", classdef.name));
	std::size_t mi = 0;
	for (; classdef.methodtable[mi].name; ++mi)
	{
		out << fmt::format( papuga::cppCodeSnippet( 1, "{{ \"{methodmame}\", l_{funcname} }},", 0),
				fmt::arg("methodmame", classdef.methodtable[mi].name),
				fmt::arg("funcname", classdef.methodtable[mi].funcname));
	}
	out << "\t" << "{0,0}" << "};" << std::endl << std::endl;
}

static void define_main(
		std::ostream& out,
		const papuga_InterfaceDescription& descr)
{
	out << fmt::format( papuga::cppCodeSnippet( 0,
		"int luaopen_{modulename}( lua_State* L );",
		"{",
		0),
		fmt::arg("modulename", descr.name)
	) << std::endl;
	std::size_t ci = 0;
	for (; descr.classes[ci].name; ++ci)
	{
		const papuga_ClassDescription& classdef = descr.classes[ci];
		out << fmt::format( papuga::cppCodeSnippet( 1,
			"papuga_lua_declare_class( ls, {classid}, \"{modulename}_{classname}\", mt_{classname}, {destructor});",
			0),
			fmt::arg("modulename", descr.name),
			fmt::arg("classid", classdef.id),
			fmt::arg("classname", classdef.name),
			fmt::arg("destructor", classdef.funcname_destructor)
		) << std::endl;
	}
	out << "}" << std::endl << std::endl;
}


DLL_PUBLIC bool papuga::generateLuaSource(
	std::ostream& out,
	std::ostream& err,
	const std::string& what,
	const std::multimap<std::string,std::string>& args,
	const papuga_InterfaceDescription& descr)
{
	try
	{
		if (what == "header")
		{
			out << fmt::format( papuga::cppCodeSnippet( 0,
				"#ifndef _PAPUGA_{modulename}_LUA_INTERFACE__INCLUDED",
				"#define _PAPUGA_{modulename}_LUA_INTERFACE__INCLUDED",
				"///\\remark GENERATED FILE (libpapuga_lua_gen) - DO NOT MODIFY",
				"",
				"#include <lua.h>",
				"#ifdef __cplusplus",
				"extern \"C\" {",
				"#endif",
				"int luaopen_{modulename}( lua_State* L );",
				"",
				"#ifdef __cplusplus",
				"}",
				"#endif",
				"#endif",
				0),
				fmt::arg("modulename", descr.name)
			) << std::endl;
		}
		else if (what == "module")
		{
			out << papuga::cppCodeSnippet( 0,
				"#include <lauxlib.h>",
				"#include \"papuga.h\"",
				"#include \"papuga/lib/lua_dev.h\"",
				"#include \"strus/bindings/lua.h\"", 0) << std::endl;

			char const** fi = descr.includefiles;
			for (; *fi; ++fi)
			{
				out << "#include \"" << *fi << "\"" << std::endl;
			}
			typedef std::multimap<std::string,std::string>::const_iterator ArgIterator;
			std::pair<ArgIterator,ArgIterator> inclist = args.equal_range( "include");
			ArgIterator ai = inclist.first, ae = inclist.second;
			for (; ai != ae; ++ai)
			{
				out << "#include \"" << ai->second << "\"" << std::endl;
			}
			out << "///\\remark GENERATED FILE (libpapuga_lua_gen) - DO NOT MODIFY" << std::endl;
			out << std::endl;

			std::size_t ci;
			for (ci=0; descr.classes[ci].name; ++ci)
			{
				const papuga_ClassDescription& classdef = descr.classes[ci];
				if (classdef.funcname_constructor)
				{
					define_constructor( out, classdef);
				}
			}
			define_classdefmap( out, descr);

			for (ci=0; descr.classes[ci].name; ++ci)
			{
				std::size_t mi = 0;
				for (; classdef.methodtable[mi].name; ++mi)
				{
					define_method( out, classdef, classdef.methodtable[mi]);
				}
				define_methodtable( out, classdef);
			}
			define_main( out, descr);
		}
		else
		{
			throw papuga::runtime_error( "unknown item '%s'", what.c_str());
		}
		return true;
	}
	catch (const fmt::FormatError& ex)
	{
		err << "format error generating lua binding source '" << what << "': " << ex.what() << std::endl;
	}
	catch (const std::exception& ex)
	{
		err << "error generating lua binding source '" << what << "': " << ex.what() << std::endl;
	}
	return false;
}


