/*
 * Copyright (c) 2017 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Code generator for strusBindings
/// \file strusTraceCodeGen.cpp
#include "interfaceParser.hpp"
#include "fillTypeTables.hpp"
#include "printFrame.hpp"
#include "strus/base/fileio.hpp"
#include "strus/base/string_format.hpp"
#include <stdexcept>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>

#undef STRUS_LOWLEVEL_DEBUG

/// \brief List of interface files parsed without path
std::vector<std::string> g_inputFiles;

typedef void (*PrintInterface)( std::ostream& out, const strus::InterfacesDef& interfaceDef);

static void printOutput( const char* filename, PrintInterface print, const strus::InterfacesDef& interfaceDef)
{
	try
	{
		std::ofstream out;
		out.open( filename, std::ofstream::out);
		if (!out)
		{
			throw std::runtime_error( std::string("could not open file '") + filename + "' for writing: " + std::strerror( errno));
		}
		print( out, interfaceDef);
		out.close();
	}
	catch (const std::bad_alloc&)
	{
		throw std::runtime_error( std::string("out of memory writing file '") + filename + "'");
	}
	catch (const std::runtime_error& err)
	{
		throw std::runtime_error( std::string("could not write file '") + filename + "': " + err.what());
	}
	catch (const std::exception& err)
	{
		throw std::runtime_error( std::string("could not write file '") + filename + "'");
	}
}

static std::string methodFunctionName( const std::string& cl, const std::string& mt)
{
	return "_strus_binding_" + cl + "__" + mt;
}

static std::string constructorFunctionName( const std::string& cl)
{
	return "_strus_binding_constructor__" + cl;
}

static std::string destructorFunctionName( const std::string& cl)
{
	return "_strus_binding_destructor__" + cl;
}

static void print_BindingInterfaceDescriptionHpp( std::ostream& out, const strus::InterfacesDef& interfaceDef)
{
	strus::printHppFrameHeader( out, "bindings_description", "Strus interface description used for generating language bindings");
	out << "#include \"papuga/interfaceDescription.h\"" << std::endl;
	out << "#include <cstddef>" << std::endl;
	out << std::endl
		<< "namespace strus {" << std::endl
		<< std::endl << std::endl;

	out << "const papuga_InterfaceDescription* getBindingsInterfaceDescription();"
		<< std::endl << std::endl;

	out << "}//namespace" << std::endl;
	strus::printHppFrameTail( out);
}

static void print_BindingInterfaceDescriptionCpp( std::ostream& out, const strus::InterfacesDef& interfaceDef)
{
	strus::printCppFrameHeader( out, "bindings_description", "Strus interface description used for generating language bindings");
	out << "#include \"strus/lib/bindings_description.hpp\"" << std::endl;
	out << "#include \"strus/bindingClassId.hpp\"" << std::endl;
	out << "#include \"strus/base/dll_tags.hpp\"" << std::endl;
	out << "#include \"internationalization.hpp\"" << std::endl;
	out << "#include \"papuga/typedefs.h\"" << std::endl;

	out << "#include <cstddef>" << std::endl;
	out
		<< std::endl
		<< "using namespace strus;" << std::endl
		<< std::endl << std::endl;
	int max_argc = 0;
	std::vector<strus::ClassDef>::const_iterator
		ci = interfaceDef.classDefs().begin(),
		ce = interfaceDef.classDefs().end();
	for (; ci != ce; ++ci)
	{
		out << "static const papuga_MethodDescription g_methods_" << ci->name() << "[" << (ci->methodDefs().size()+1) << "] = " << std::endl
			<< "{" << std::endl;
		std::vector<strus::MethodDef>::const_iterator
			mi = ci->methodDefs().begin(),
			me = ci->methodDefs().end();
		for (; mi != me; ++mi)
		{
			int argc = mi->parameters().size();
			if (argc > max_argc) max_argc = argc;
			out << "\t{\"" << mi->name() <<  "\", \"" << methodFunctionName(ci->name(),mi->name()) << "\", true, " << argc << "}," << std::endl;
		}
		out << "\t{0,0,0}" << std::endl;
		out << "};" << std::endl;
	}

	out << "static const papuga_ClassDescription g_classes[" << (interfaceDef.classDefs().size()+1) << "] = " << std::endl
		<< "{" << std::endl;
	ci = interfaceDef.classDefs().begin();
	for (; ci != ce; ++ci)
	{
		std::string classid = std::string("Class") + ci->name();
		std::string constructorid = ci->constructorDefs().empty()?std::string("NULL"):(std::string("\"")+constructorFunctionName(ci->name())+std::string("\""));

		out << "\t{ " << classid << ", \"" << ci->name() << "\", " << constructorid << ", \"" << destructorFunctionName(ci->name()) << "\", g_methods_" << ci->name() << "}," << std::endl;
	}
	out << "\t{0,0}" << std::endl;
	out << "};" << std::endl << std::endl;
	out << "static const papuga_ErrorDescription g_errors[] = {" << std::endl;
	out << "\t{papuga_Ok,_TXT(\"Ok\")}," << std::endl;
	out << "\t{papuga_LogicError,_TXT(\"logic error\")}," << std::endl;
	out << "\t{papuga_NoMemError,_TXT(\"out of memory\")}," << std::endl;
	out << "\t{papuga_TypeError,_TXT(\"type mismatch\")}," << std::endl;
	out << "\t{papuga_EncodingError,_TXT(\"string character encoding error\")}," << std::endl;
	out << "\t{papuga_BufferOverflowError,_TXT(\"internal buffer not big enough\")}," << std::endl;
	out << "\t{papuga_OutOfRangeError,_TXT(\"value out of range\")}," << std::endl;
	out << "\t{papuga_NofArgsError,_TXT(\"number of arguments does not match\")}," << std::endl;
	out << "\t{papuga_MissingSelf,_TXT(\"self argument is missing\")}," << std::endl;
	out << "\t{0,NULL}" << std::endl;
	out << "};" << std::endl << std::endl;

	out << "static const papuga_InterfaceDescription g_descr = { \"strus\", \"strus/bindingObjects.h\", g_classes, g_errors };"
		<< std::endl << std::endl;

	out << "DLL_PUBLIC const papuga_InterfaceDescription* strus::getBindingsInterfaceDescription()" << std::endl;
	out << "{" << std::endl;
	out << "\treturn &g_descr;" << std::endl;
	out << "}" << std::endl;
}

static void print_BindingObjectsH( std::ostream& out, const strus::InterfacesDef& interfaceDef)
{
	strus::printHFrameHeader( out, "bindingObjects", "Identifiers for objects and methods for serialization");
	out << "#include \"papuga/valueVariant.h\"" << std::endl;
	out << "#include \"papuga/callResult.h\"" << std::endl;
	out << "#include \"papuga/serialization.h\"" << std::endl;
	out << "#include \"papuga/hostObjectReference.h\"" << std::endl;
	out << "#include <stddef.h>" << std::endl;
	out << "#include <stdbool.h>" << std::endl;

	out << "#ifdef __cplusplus" << std::endl;
	out << "extern \"C\" {" << std::endl;
	out << "#endif" << std::endl;

	std::vector<strus::ClassDef>::const_iterator
		ci = interfaceDef.classDefs().begin(),
		ce = interfaceDef.classDefs().end();
	for (; ci != ce; ++ci)
	{
		out << "bool " << destructorFunctionName( ci->name()) << "( void* self);" << std::endl;
		out << std::endl;

		if (ci->constructorDefs().size() > 1) throw std::runtime_error( std::string("only one constructor allowed for '") + ci->name() + "'");
		std::vector<strus::ConstructorDef>::const_iterator
			ki = ci->constructorDefs().begin(),
			ke = ci->constructorDefs().end();
		for (; ki != ke; ++ki)
		{
			out 
			<< "bool " << constructorFunctionName( ci->name())
			<< "( papuga_CallResult& retval, "
			<< "size_t argc, const papuga_ValueVariant* argv);" << std::endl;
		}

		std::vector<strus::MethodDef>::const_iterator
			mi = ci->methodDefs().begin(),
			me = ci->methodDefs().end();
		for (; mi != me; ++mi)
		{
			out 
			<< "bool " << methodFunctionName( ci->name(), mi->name())
			<< "( void* self, papuga_CallResult& retval, "
			<< "size_t argc, const papuga_ValueVariant* argv);" << std::endl;
		}
	}
	out << "#ifdef __cplusplus" << std::endl;
	out << "}" << std::endl;
	out << "#endif" << std::endl;

	strus::printHFrameTail( out);
}

struct ParameterSructureExpanded
{
	std::size_t min_nofargs;
	std::vector<std::string> param_converted;
	std::vector<std::string> param_defaults;
	std::vector<std::string> param_declarations;

	std::size_t size() const	{return param_converted.size();}

	ParameterSructureExpanded( const ParameterSructureExpanded& o)
		:min_nofargs(o.min_nofargs),param_converted(o.param_converted),param_defaults(o.param_defaults),param_declarations(o.param_declarations){}
	ParameterSructureExpanded()
		:min_nofargs(0){}
	ParameterSructureExpanded( const std::vector<strus::VariableValue>& parameters)
		:min_nofargs(0)
	{
		std::vector<strus::VariableValue>::const_iterator
			pi = parameters.begin(),
			pe = parameters.end();
		for (; pi != pe; ++pi,++min_nofargs)
		{
			if (pi->type().hasEvent( "argv_default")) break;
		}
		// Declare some conversions, if needed:
		pi = parameters.begin();
		for (std::size_t pidx=0; pi != pe; ++pi,++pidx)
		{
			if (pi->type().hasEvent( "argv_decl"))
			{
				std::string val = strus::string_format( "argv[%u]", (unsigned int)pidx);
				std::string nam = strus::string_format( "conv_argv%u", (unsigned int)pidx);
				param_declarations.push_back( pi->expand( "argv_decl", nam.c_str(), val.c_str()));
			}
			else
			{
				param_declarations.push_back(std::string());
			}
		}
		// Collect argument values:
		std::vector<std::string> params_converted;
		std::vector<std::string> params_default;
		pi = parameters.begin();
		for (std::size_t pidx=0; pi != pe; ++pi,++pidx)
		{
			std::string val = strus::string_format( "argv[%u]", (unsigned int)pidx);
			std::string nam = strus::string_format( "conv_argv%u", (unsigned int)pidx);
			param_converted.push_back( pi->expand( "argv_map", nam.c_str(), val.c_str()));
			param_defaults.push_back( min_nofargs <= pidx ? pi->expand( "argv_default", nam.c_str(), val.c_str()) : std::string());
		}
	}

	std::string expandCallParameter(
		std::size_t nofargs)
	{
		std::ostringstream out;
		std::size_t pi = 0, pe = param_converted.size();
		for (; pi != pe; ++pi)
		{
			if (pi) out << ", "; else out << " ";
			out << ((pi >= nofargs) ? param_defaults[ pi] : param_converted[ pi]);
		}
		return out.str();
	}

	void printConstructorCall( std::ostream& out, const std::string& indent, const std::string& classname)
	{
		if (param_converted.size() == 0)
		{
			out << indent << "if (argc > 0) throw strus::runtime_error(_TXT(\"no arguments expected\"));" << std::endl;
			out << indent << "papuga::HostObjectReference::initOwnership( &retval, new " << classname << "Impl());" << std::endl;
		}
		else
		{
			out << indent << "switch (argc)" << std::endl;
			out << indent << "{" << std::endl;
			for (std::size_t pidx=min_nofargs; pidx<=param_converted.size(); ++pidx)
			{
				out << indent << "\tcase " << pidx << ": papuga::HostObjectReference::initOwnership( &retval, new " << classname << "(" << expandCallParameter( pidx) << "); break;" << std::endl;
			}
			out << indent << "\tdefault: throw strus::runtime_error(_TXT(\"too many arguments\"));" << std::endl;
			out << indent << "}" << std::endl;
		}
	}

	std::string mapInitReturnValue( const strus::VariableValue& returnvalue, const std::string& expression)
	{
		if (returnvalue.type().hasEvent("retv_map"))
		{
			return returnvalue.expand( "retv_map", "retval", expression.c_str());
		}
		else if (returnvalue.type().source() == "void")
		{
			return expression;
		}
		else
		{
			throw std::runtime_error( std::string("no return value type map declared for '") + returnvalue.type().source() + "'");
		}
	}

	void printMethodCall( std::ostream& out, const std::string& indent, const std::string& methodname, const strus::VariableValue& returnvalue)
	{
		std::string expression;
		if (param_converted.size() == 0)
		{
			out << indent << "if (argc > 0) throw strus::runtime_error(_TXT(\"no arguments expected\"));" << std::endl;
			std::string expression = "THIS->" + methodname + "()";
			out << indent << mapInitReturnValue( returnvalue, expression) << std::endl;
		}
		else
		{
			out << indent << "switch (argc)" << std::endl;
			out << indent << "{" << std::endl;
			for (std::size_t pidx=min_nofargs; pidx<=param_converted.size(); ++pidx)
			{
				std::string expression = "THIS->" + methodname + "(" + expandCallParameter( pidx) + ")";
				out << indent << "\tcase " << pidx << ": " << mapInitReturnValue( returnvalue, expression) << " break;" << std::endl;
			}
			out << indent << "\tdefault: throw strus::runtime_error(_TXT(\"too many arguments\"));" << std::endl;
			out << indent << "}" << std::endl;
		}
	}
};

static void print_BindingObjectsCpp( std::ostream& out, const strus::InterfacesDef& interfaceDef)
{
	strus::printCppFrameHeader( out, "bindingObjects", "Identifiers for objects and methods for serialization");
	out << "#include \"strus/bindingObjects.hpp\"" << std::endl;
	out << "#include \"strus/base/dll_tags.hpp\"" << std::endl;
	out << "#include \"impl/context.hpp\"" << std::endl;
	out << "#include \"impl/storage.hpp\"" << std::endl;
	out << "#include \"impl/vector.hpp\"" << std::endl;
	out << "#include \"impl/analyzer.hpp\"" << std::endl;
	out << "#include \"impl/query.hpp\"" << std::endl;
	out << "#include \"impl/statistics.hpp\"" << std::endl;
	out << "#include \"internationalization.hpp\"" << std::endl;

	out << std::endl
		<< "using namespace strus;" << std::endl
		<< "using namespace strus::bindings;" << std::endl
		<< std::endl;

	out << "#define CATCH_METHOD_CALL_ERROR( retval, classnam, methodnam)\\" << std::endl;
	out << "\tcatch (const std::runtime_error& err)\\" << std::endl;
	out << "\t{\\" << std::endl;
	out << "\t\tretval.reportError( _TXT(\"error calling method %s::%s(): %s\"), classnam, methodnam, err.what());\\" << std::endl;
	out << "\t}\\" << std::endl;
	out << "\tcatch (const std::bad_alloc& err)\\" << std::endl;
	out << "\t{\\" << std::endl;
	out << "\t\tretval.reportError( _TXT(\"out of memory calling method %s::%s()\"), classnam, methodnam);\\" << std::endl;
	out << "\t}\\" << std::endl;
	out << "\tcatch (const std::exception& err)\\" << std::endl;
	out << "\t{\\" << std::endl;
	out << "\t\tretval.reportError( _TXT(\"uncaught exception calling method %s::%s(): %s\"), classnam, methodnam, err.what());\\" << std::endl;
	out << "\t}\\" << std::endl;
	out << "\treturn false;" << std::endl << std::endl;

	std::vector<strus::ClassDef>::const_iterator
		ci = interfaceDef.classDefs().begin(),
		ce = interfaceDef.classDefs().end();
	for (; ci != ce; ++ci)
	{
		out << "void " << destructorFunctionName( ci->name()) << "( void* self)" << std::endl;
		out << "{" << std::endl;
		out << "	delete reinterpret_cast<" << ci->name() << "Impl>( self);" << std::endl;
		out << "}" << std::endl;
		out << std::endl;

		if (ci->constructorDefs().size() > 1) throw std::runtime_error( std::string("only one constructor allowed for '") + ci->name() + "'");
		std::vector<strus::ConstructorDef>::const_iterator
			ki = ci->constructorDefs().begin(),
			ke = ci->constructorDefs().end();
		for (; ki != ke; ++ki)
		{
			out 
			<< "bool " << constructorFunctionName( ci->name())
			<< "( papuga_CallResult& retval, "
			<< "size_t argc, const papuga_ValueVariant* argv)" << std::endl
			<< "{" << std::endl;
			ParameterSructureExpanded paramstruct( ki->parameters());
			if (paramstruct.min_nofargs)
			{
				out << "\t\tif (argc < " << paramstruct.min_nofargs << ") throw strus::runtime_error(_TXT(\"too few arguments\"));" << std::endl;
			}
			// Do some declarations and conversions, if needed:
			for (std::size_t pidx=0; pidx < paramstruct.size(); ++pidx)
			{
				if (!paramstruct.param_declarations[pidx].empty())
				{
					out << "\t\t" << paramstruct.param_declarations[pidx] << std::endl;
				}
			}
			// Print call:
			paramstruct.printConstructorCall( out, "\t\t", ci->name());

			out << "\t\treturn true;" << std::endl;
			out << "\t}" << std::endl;
			out << "\tCATCH_METHOD_CALL_ERROR( retval, \"" << ci->name().c_str() << "\", \"constructor\")" << std::endl;
			out << "}" << std::endl << std::endl;
		}

		std::vector<strus::MethodDef>::const_iterator
			mi = ci->methodDefs().begin(),
			me = ci->methodDefs().end();
		for (; mi != me; ++mi)
		{
			out << "extern \"C\" DLL_PUBLIC bool " << methodFunctionName( ci->name(), mi->name())
				<< "( void* self, papuga_CallResult& retval, "
				<< "size_t argc, const papuga_ValueVariant* argv)" << std::endl;
			out << "{" << std::endl;
			out << "\ttry {" << std::endl;
			out << "\t\t" << ci->name() << "Impl* THIS = ("<< ci->name() << "Impl*)(self);" << std::endl;

			ParameterSructureExpanded paramstruct( mi->parameters());
			if (paramstruct.min_nofargs)
			{
				out << "\t\tif (argc < " << paramstruct.min_nofargs << ") throw strus::runtime_error(_TXT(\"too few arguments\"));" << std::endl;
			}
			// Do some declarations and conversions, if needed:
			for (std::size_t pidx=0; pidx < paramstruct.size(); ++pidx)
			{
				if (!paramstruct.param_declarations[pidx].empty())
				{
					out << "\t\t" << paramstruct.param_declarations[pidx] << std::endl;
				}
			}
			// Print call:
			paramstruct.printMethodCall( out, "\t\t", mi->name(), mi->returnValue());

			out << "\t\treturn true;" << std::endl;
			out << "\t}" << std::endl;
			out << "\tCATCH_METHOD_CALL_ERROR( retval, \"" << ci->name().c_str() << "\", \"" << mi->name().c_str() << "\")" << std::endl;
			out << "}" << std::endl << std::endl;
		}
	}
}

int main( int argc, const char* argv[])
{
	int ec = 0;
	try
	{
		strus::TypeSystem typeSystem;
		strus::fillTypeTables( typeSystem);

#ifdef STRUS_LOWLEVEL_DEBUG
		std::cout << "TypeSystem:" << std::endl << typeSystem.tostring() << std::endl;
#endif
		strus::InterfacesDef interfaceDef( &typeSystem);
		int argi=1;
		for (; argi < argc; ++argi)
		{
			std::string source;
			ec = strus::readFile( argv[ argi], source);
			if (ec)
			{
				std::ostringstream msg;
				msg << ec;
				throw std::runtime_error( std::string( "error '") + ::strerror(ec) + "' (errno " + msg.str() + ") reading file " + argv[argi]);
			}
			try
			{
				char const* fi = argv[ argi];
				char const* fn = std::strchr( fi, strus::dirSeparator());
				for (;fn; fi=fn+1,fn=std::strchr( fi, strus::dirSeparator())){}

				g_inputFiles.push_back( fi);
				interfaceDef.addSource( source);
			}
			catch (const std::runtime_error& err)
			{
				throw std::runtime_error( std::string( "error parsing interface file ") + argv[argi] + ": " + err.what());
			}
			std::cerr << "processed file " << argv[argi] << std::endl;
		}
		interfaceDef.checkUnresolved();

		//Output:
#ifdef STRUS_LOWLEVEL_DEBUG
		std::cout << interfaceDef.tostring() << std::endl;
#endif
		printOutput( "include/strus/bindingObjects.h", &print_BindingObjectsH, interfaceDef);
		printOutput( "src/bindingObjects.cpp", &print_BindingObjectsCpp, interfaceDef);

		printOutput( "include/strus/lib/bindings_description.hpp", &print_BindingInterfaceDescriptionHpp, interfaceDef);
		printOutput( "src/libstrus_bindings_description.cpp", &print_BindingInterfaceDescriptionCpp, interfaceDef);

		std::cerr << "done." << std::endl;
		return 0;
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "ERROR memory allocation error in code generator" << std::endl;
		return 12/*ENOMEM*/;
	}
	catch (const std::runtime_error& err)
	{
		std::cerr << "ERROR in code generator: " << err.what() << std::endl;
		return (ec == 0)?-1:ec;
	}
	catch (...)
	{
		std::cerr << "ERROR uncaught exception in code generator" << std::endl;
		return -1;
	}
}


