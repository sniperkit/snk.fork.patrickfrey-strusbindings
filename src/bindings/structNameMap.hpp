/*
 * Copyright (c) 2017 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#ifndef _STRUS_BINDINGS_STRUCTURE_NAME_MAP_HPP_INCLUDED
#define _STRUS_BINDINGS_STRUCTURE_NAME_MAP_HPP_INCLUDED
#include "papuga/typedefs.h"
#include <vector>
#include <string>

namespace strus {
namespace bindings {

class StructureNameMap
{
public:
	enum {Undefined=-1};

	explicit StructureNameMap( const char* strings_, char delim=',');
	~StructureNameMap(){}

	int index( const char* id, std::size_t idsize) const;
	int index( const char* id) const;
	int index( const papuga_ValueVariant& id) const;
	const char* name( int idx) const;

private:
	const char* m_strings;
	std::vector<signed char> m_ar;
	std::vector<std::string> m_names;
};

}}//namespace
#endif

