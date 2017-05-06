/*
 * Copyright (c) 2017 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include "structNameMap.hpp"
#include "internationalization.hpp"
#include "papuga/valueVariant.h"
#include <cstring>

using namespace strus;
using namespace strus::bindings;

StructureNameMap::StructureNameMap( const char* strings_, char delim)
	:m_strings(strings_),m_ar(std::strlen(strings_)+1, Undefined)
{
	char const* si = m_strings;
	char const* sn = std::strchr( si, delim);
	unsigned char idx = 0;
	for (; sn; si=sn+1,sn=std::strchr( si, delim))
	{
		m_ar[ sn-m_strings] = idx++;
		if (idx >= 127) throw strus::runtime_error(_TXT("too many structure elements defined"));
	}
	m_ar[ m_ar.size()-1] = idx;
}

int StructureNameMap::index( const char* id, std::size_t idsize) const
{
	char const* pi = std::strstr( m_strings, id);
	return pi ? m_ar[ (pi-m_strings+std::strlen(id))] : Undefined;
}
	
int StructureNameMap::index( const char* id) const
{
	return index( id, std::strlen(id));
}

int StructureNameMap::index( const papuga_ValueVariant& id) const
{
	if (id.valuetype == papuga_String)
	{
		return index( id.value.string, id.length);
	}
	if (id.valuetype == papuga_LangString)
	{
		enum {MaxIdSize=128};
		char buf[ MaxIdSize];
		if (!papuga_ValueVariant_toascii( buf, sizeof(buf), &id)) return Undefined;
		return index( buf, id.length);
	}
	return false;
}

