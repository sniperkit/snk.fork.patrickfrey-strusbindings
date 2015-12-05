/*
---------------------------------------------------------------------
    The C++ library strus implements basic operations to build
    a search engine for structured search on unstructured data.

    Copyright (C) 2013,2014 Patrick Frey

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

--------------------------------------------------------------------

	The latest version of strus can be found at 'http://github.com/patrickfrey/strus'
	For documentation see 'http://patrickfrey.github.com/strus'

--------------------------------------------------------------------
*/
#ifndef _STRUS_BINDING_PHP_OBJECT_INITIALIZERS_HPP_INCLUDED
#define _STRUS_BINDING_PHP_OBJECT_INITIALIZERS_HPP_INCLUDED
#include <php.h>
#include "strus/bindingObjects.hpp"
#include <vector>

int initVariant( Variant& result, zval* obj);
int initTokenizer( Tokenizer& result, zval* obj);
int initNormalizer( Normalizer& result, zval* obj);
int initNormalizerList( std::vector<Normalizer>& result, zval* obj);
int initAggregator( Aggregator& result, zval* obj);
int initSummarizerConfig( SummarizerConfig& result, zval* obj);
int initWeightingConfig( WeightingConfig& result, zval* obj);
int initQueryExpression( QueryExpression& result, zval* obj);
int initStringVector( std::vector<std::string>& result, zval* obj);
int initIntVector( std::vector<int>& result, zval* obj);
int initGlobalStatistics( GlobalStatistics& result, zval* obj);
int initTermStatistics( TermStatistics& result, zval* obj);

int getTermVector( zval* result, const std::vector<Term>& ar);
int getRankVector( zval* result, const std::vector<Rank>& ar);

#endif
