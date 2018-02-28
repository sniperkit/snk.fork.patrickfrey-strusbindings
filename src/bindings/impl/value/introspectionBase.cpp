/*
 * Copyright (c) 2017 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Abstract interface for introspection
#include "introspectionBase.hpp"
#include "private/internationalization.hpp"
#include "papuga/allocator.h"
#include "papuga/constants.h"
#include "papuga/serialization.h"
#include "serializer.hpp"
#include "strus/errorBufferInterface.hpp"
#include "strus/valueIteratorInterface.hpp"
#include "strus/base/local_ptr.hpp"
#include <stdexcept>

using namespace strus;
using namespace strus::bindings;

std::vector<std::string> IntrospectionBase::getList( const char** ar)
{
	std::vector<std::string> rt;
	char const** ai = ar;
	for (; *ai; ++ai)
	{
		rt.push_back( *ai);
	}
	return rt;
}

std::vector<std::string> IntrospectionBase::getKeyList( const std::vector<std::pair<std::string,std::string> >& ar)
{
	std::vector<std::string> rt;
	typename std::vector<std::pair<std::string,std::string> >::const_iterator ci = ar.begin(), ce = ar.end();
	for (; ci != ce; ++ci)
	{
		rt.push_back( ci->first);
	}
	return rt;
}

void IntrospectionBase::serializeList( papuga_Serialization& serialization) const
{
	std::vector<std::string> elems = this->list();
	std::vector<std::string>::const_iterator li = elems.begin(), le = elems.end();
	for (; li != le; ++li)
	{
		strus::local_ptr<IntrospectionBase> introspection( open( *li));
		if (introspection.get())
		{
			introspection->serializeStructureAs( serialization, li->c_str());
		}
	}
}

void IntrospectionBase::serializeStructureAs( papuga_Serialization& serialization, const char* name) const
{
	bool sc = true;
	const char* namecopy = papuga_Allocator_copy_charp( serialization.allocator, name);
	if (!namecopy) throw std::bad_alloc();
	sc &= papuga_Serialization_pushName_charp( &serialization, namecopy);
	sc &= papuga_Serialization_pushOpen( &serialization);
	this->serialize( serialization);
	sc &= papuga_Serialization_pushClose( &serialization);
	if (!sc) throw std::bad_alloc();
}

std::runtime_error bindings::introspection_error( const char* msg, ErrorBufferInterface* errorhnd)
{
	return strus::runtime_error( "%s: %s", msg, errorhnd->hasError() ? errorhnd->fetchError() : _TXT("unknown error"));
}

IntrospectionValueIterator::IntrospectionValueIterator( ErrorBufferInterface* errorhnd_, ValueIteratorInterface* impl_)
	:m_errorhnd(errorhnd_),m_impl(impl_){}

IntrospectionValueIterator::~IntrospectionValueIterator()
{
	if (m_impl) delete m_impl;
}

void IntrospectionValueIterator::serialize( papuga_Serialization& serialization) const
{
	std::vector<std::string> valuelist = m_impl->fetchValues( PAPUGA_MAX_ITERATOR_EXPANSION_LENGTH);
	Serializer::serialize( &serialization, valuelist, true/*deep*/);
}
IntrospectionBase* IntrospectionValueIterator::open( const std::string& name) const
{
	return NULL;
}
std::vector<std::string> IntrospectionValueIterator::list() const
{
	return std::vector<std::string>();
}
