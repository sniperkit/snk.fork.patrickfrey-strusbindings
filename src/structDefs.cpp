/*
* Copyright (c) 2017 Patrick P. Frey
*
* This Source Code Form is subject to the terms of the Mozilla Public
* License, v. 2.0. If a copy of the MPL was not distributed with this
* file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "structDefs.hpp"
#include "wcharString.hpp"
#include "valueVariantConv.hpp"
#include "internationalization.hpp"
#include "deserializer.hpp"
#include "strus/bindings/serialization.hpp"

using namespace strus;
using namespace strus::bindings;

static const ValueVariant& getValue(
		Serialization::const_iterator& si,
		const Serialization::const_iterator& se)
{
	if (si != se && si->tag == Serialization::Value)
	{
		return *si++;
	}
	else
	{
		throw strus::runtime_error(_TXT("expected value in serialization"));
	}
}

void AnalyzerFunctionDef::deserialize( Serialization::const_iterator& si, const Serialization::const_iterator& se)
{
	static const StructureNameMap namemap( "name,arg", ',');
	if (si == se) throw strus::runtime_error(_TXT("unexpected end of serialization: analyzer function structure expected"));

	bool name_defined = false;
	if (si->tag == Serialization::Name)
	{
		do
		{
			switch (namemap.index(*si++))
			{
				case 0: name_defined = true;
					name = Deserializer::getString( si, se);
					break;
				case 1: args = Deserializer::getStringList( si, se);
					break;
				default: throw strus::runtime_error(_TXT("unknown tag name in analyzer function structure"));
			}
		} while (si != se && si->tag == Serialization::Name);
		Deserializer::consumeClose( si, se);
	}
	else if (si->tag == Serialization::Value)
	{
		name = Deserializer::getString( si, se);
		name_defined = true;
		if (si != se && si->tag != Serialization::Close)
		{
			args = Deserializer::getStringList( si, se);
		}
		Deserializer::consumeClose( si, se);
	}
	else
	{
		throw strus::runtime_error(_TXT("analyzer function definition structure expected"));
	}
	if (!name_defined)
	{
		throw strus::runtime_error(_TXT("name not defined in analyzer function"));
	}
}

void TermDef::deserialize( Serialization::const_iterator& si, const Serialization::const_iterator& se)
{
	static const StructureNameMap namemap( "type,value,variable,len", ',');
	if (si == se) throw strus::runtime_error(_TXT("unexpected end of serialization: term structure expected"));

	bool type_defined = false;
	if (si->tag == Serialization::Name)
	{
		do
		{
			switch (namemap.index( *si++))
			{
				case 0: type_defined = true;
					type = Deserializer::getString( si, se);
					break;
				case 1: value_defined = true;
					value = Deserializer::getString( si, se);
					break;
				case 2: variable = Deserializer::getString( si, se);
					break;
				case 3: length_defined = true;
					length = Deserializer::getUint( si, se);
					break;
				default: throw strus::runtime_error(_TXT("unknown tag name in term structure"));
			}
		} while (si != se && si->tag == Serialization::Name);
		Deserializer::consumeClose( si, se);
	}
	else if (si->tag == Serialization::Value)
	{
		if (Deserializer::isStringWithPrefix( *si, '='))
		{
			variable = Deserializer::getPrefixStringValue( *si++, '=');
		}
		if (si == se) throw strus::runtime_error(_TXT("unexpected end of serialization: term structure expected"));

		if (si->tag == Serialization::Value)
		{
			type = Deserializer::getString( si, se);
			type_defined = true;
			if (si != se && si->tag != Serialization::Close)
			{
				value = Deserializer::getString( si, se);
				value_defined = true;
				if (si != se && si->tag != Serialization::Close)
				{
					length_defined = true;
					length = Deserializer::getUint( si, se);
				}
			}
		}
		else
		{
			throw strus::runtime_error(_TXT("term definition expected"));
		}
		Deserializer::consumeClose( si, se);
	}
	else
	{
		throw strus::runtime_error(_TXT("term definition expected"));
	}
	if (!value_defined && length_defined)
	{
		throw strus::runtime_error(_TXT("terms with length defined without value defined are not accepted"));
	}
	if (!type_defined)
	{
		throw strus::runtime_error(_TXT("type not defined in term expression"));
	}
}

void MetaDataRangeDef::deserialize( Serialization::const_iterator& si, const Serialization::const_iterator& se)
{
	static const StructureNameMap namemap( "from,to", ',');
	if (si == se) throw strus::runtime_error(_TXT("unexpected end of serialization: term structure expected"));

	if (si->tag == Serialization::Name)
	{
		do
		{
			switch (namemap.index( *si++))
			{
				case 0: from = Deserializer::getString( si, se);
					break;
				case 1:	to = Deserializer::getString( si, se);
					break;
				default: throw strus::runtime_error(_TXT("unknown tag name in term structure"));
			}
		} while (si != se && si->tag == Serialization::Name);
		Deserializer::consumeClose( si, se);
	}
	else if (si->tag == Serialization::Value)
	{
		from = Deserializer::getPrefixStringValue( *si++, '@');
		if (si != se && si->tag != Serialization::Close)
		{
			to = Deserializer::getPrefixStringValue( *si++, '@');
		}
		Deserializer::consumeClose( si, se);
	}
}

void QueryEvalFunctionParameterDef::deserialize( Serialization::const_iterator& si, const Serialization::const_iterator& se)
{
	static const StructureNameMap namemap( "name,value,feature", ',');
	if (si->tag == Serialization::Open)
	{
		++si;
		if (si == se) throw strus::runtime_error(_TXT("unexpected end of configuration definition"));
		if (si->tag == Serialization::Value)
		{
			type = Undefined;
			name = Deserializer::getString( si, se);
			value = getValue( si, se);
			Deserializer::consumeClose( si, se);
		}
		else
		{
			unsigned char name_defined = 0;
			while (si->tag == Serialization::Name)
			{
				switch (namemap.index( *si++))
				{
					case 0: if (name_defined++) throw strus::runtime_error(_TXT("duplicate definition of '%s'"), "name");
						name = Deserializer::getString( si, se);
						break;
					case 1: if (type != Undefined) throw strus::runtime_error(_TXT("contradicting definitions in query evaluation function parameter: only one allowed of 'value', 'result', or 'feature'"));
						type = Value; value = getValue( si, se);
						break;
					case 2:	if (type != Undefined) throw strus::runtime_error(_TXT("contradicting definitions in query evaluation function parameter: only one allowed of 'value', 'result', or 'feature'"));
						type = Feature; value = getValue( si, se);
						break;
					default: throw strus::runtime_error(_TXT("unknown tag name in query evaluation function config"));
				}
			}
			Deserializer::consumeClose( si, se);
			if (!name_defined || type == Undefined)
			{
				throw strus::runtime_error(_TXT("incomplete query evaluation function definition"));
			}
		}
	}
	else if (si->tag == Serialization::Name)
	{
		name = Deserializer::getString( si, se);
		if (si == se) throw strus::runtime_error(_TXT("unexpected end of query evaluation function parameter definition"));

		std::pair<ValueVariant,ValueVariant> paramdecl = Deserializer::getValueWithOptionalName( si, se);
		if (paramdecl.first.defined())
		{
			if (ValueVariantConv::isequal_ascii( paramdecl.first, "feature"))
			{
				value = paramdecl.second;
				type = Feature;
			}
			else if (ValueVariantConv::isequal_ascii( paramdecl.first, "value"))
			{
				value = paramdecl.second;
				type = Value;
			}
			else
			{
				std::string typname = ValueVariantConv::tostring( paramdecl.first);
				throw strus::runtime_error(_TXT("unexpected parameter type name '%s', expected 'feature' or 'value'"), typname.c_str());
			}
		}
		else
		{
			type = Undefined;
			value = paramdecl.second;
		}
	}
	else
	{
		throw strus::runtime_error(_TXT("argument name expected as as start of a query evaluation function parameter"));
	}
}


void ConfigDef::deserialize( Serialization::const_iterator& si, const Serialization::const_iterator& se)
{
	static const StructureNameMap namemap( "name,value", ',');
	if (si->tag == Serialization::Open)
	{
		++si;
		if (si == se) throw strus::runtime_error(_TXT("unexpected end of configuration definition"));
		if (si->tag == Serialization::Value)
		{
			name = Deserializer::getString( si, se);
			value = getValue( si, se);
			Deserializer::consumeClose( si, se);
		}
		else
		{
			unsigned char defined[2] = {0,0};
			while (si->tag == Serialization::Name)
			{
				switch (namemap.index( *si++))
				{
					case 0: if (defined[0]++) throw strus::runtime_error(_TXT("duplicate definition of '%s'"), "name");
						name = Deserializer::getString( si, se);
						break;
					case 1:	if (defined[1]++) throw strus::runtime_error(_TXT("duplicate definition of '%s'"), "value");
						value = getValue( si, se);
						break;
					default: throw strus::runtime_error(_TXT("unknown tag name in configuration, 'name' or 'value' expected"));
				}
			}
			Deserializer::consumeClose( si, se);
			if (!defined[0] || !defined[1])
			{
				throw strus::runtime_error(_TXT("incomplete configuration definition"));
			}
		}
	}
	else if (si->tag == Serialization::Name)
	{
		name = Deserializer::getString( si, se);
		if (si == se) throw strus::runtime_error(_TXT("unexpected end of configuration definition"));

		value = *si++;
	}
	else
	{
		throw strus::runtime_error(_TXT("argument name expected as as start of a configuration parameter"));
	}
}


