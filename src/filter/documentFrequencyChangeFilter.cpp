/*
 * Copyright (c) 2017 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/*
 * DO NOT MODIFY THIS FILE !!!
 * 
 * This file has been generated with the script scripts/genFilters.py
 * Modifications on this file will be lost!
 */
/// \file documentFrequencyChangeFilter.cpp
#include "documentFrequencyChangeFilter.hpp"
#include "structElementArray.hpp"
#include "stateTable.hpp"
#include <cstring>

using namespace strus;

static const char* g_element_names[] = { "type","value","increment", 0};
static const filter::StructElementArray g_struct_elements( g_element_names);

enum TermState {
	StateEnd,
	StateTypeOpen,
	StateTypeValue,
	StateTypeClose,
	StateValueOpen,
	StateValueValue,
	StateValueClose,
	StateIncrementOpen,
	StateIncrementValue,
	StateIncrementClose
};

#define _OPEN	BindingFilterInterface::Open
#define _CLOSE	BindingFilterInterface::Close
#define _INDEX	BindingFilterInterface::Index
#define _VALUE	BindingFilterInterface::Value
#define _NULL	filter::StateTable::NullValue
#define _TAG	filter::StateTable::TagValue
#define _ELEM	filter::StateTable::ElementValue


// Element: index, tag, nextState, skipState, valueType, tagnameIndex, valueIndex
static const filter::StateTable::Element g_struct_statetable[] = {
	{StateEnd, _CLOSE, StateEnd, StateEnd, _NULL, 0, 0},
	{StateTypeOpen, _OPEN, StateTypeValue, StateValueOpen, _TAG, 0, -1},
	{StateTypeValue, _VALUE, StateTypeClose, StateTypeClose, _ELEM, -1, 0},
	{StateTypeClose, _CLOSE, StateValueOpen, StateValueOpen, _NULL, -1, -1},
	{StateValueOpen, _OPEN, StateValueValue, StateIncrementOpen, _TAG, 1, -1},
	{StateValueValue, _VALUE, StateValueClose, StateValueClose, _ELEM, -1, 1},
	{StateValueClose, _CLOSE, StateIncrementOpen, StateIncrementOpen, _NULL, -1, -1},
	{StateIncrementOpen, _OPEN, StateIncrementValue, StateEnd, _TAG, 2, -1},
	{StateIncrementValue, _VALUE, StateIncrementClose, StateIncrementClose, _ELEM, -1, 2},
	{StateIncrementClose, _CLOSE, StateEnd, StateEnd, _NULL, -1, -1}
};

DocumentFrequencyChangeFilter::DocumentFrequencyChangeFilter()
	:m_impl(0),m_ownership(0),m_state(0)
{
	std::memset( m_index, 0, sizeof(m_index));
}

DocumentFrequencyChangeFilter::DocumentFrequencyChangeFilter( const DocumentFrequencyChangeFilter& o)
	:m_impl(o.m_impl),m_ownership(o.m_ownership),m_state(o.m_state)
{
	std::memcpy( m_index, o.m_index, sizeof(m_index));
}

DocumentFrequencyChangeFilter::DocumentFrequencyChangeFilter( const bindings::DocumentFrequencyChange* impl)
	:m_impl(impl),m_ownership(0),m_state(1)
{
	std::memset( m_index, 0, sizeof(m_index));
}

DocumentFrequencyChangeFilter::DocumentFrequencyChangeFilter( bindings::DocumentFrequencyChange* impl, bool withOwnership)
	:m_impl(impl),m_ownership(impl),m_state(1)
{
	std::memset( m_index, 0, sizeof(m_index));
}

DocumentFrequencyChangeFilter::~DocumentFrequencyChangeFilter()
{
	if (m_ownership) delete( m_ownership);
}

static bindings::ValueVariant getElementValue( const bindings::DocumentFrequencyChange& elem, int valueIndex)
{
	switch (valueIndex) {

		case 0:
			return bindings::ValueVariant( (*m_impl).type());

		case 1:
			return bindings::ValueVariant( (*m_impl).value());

		case 2:
			return bindings::ValueVariant( (bindings::ValueVariant::IntType)(*m_impl).increment());

	}
	return bindings::ValueVariant();
}

BindingFilterInterface::Tag DocumentFrequencyChangeFilter::getNext( bindings::ValueVariant& val)
{
	const filter::StateTable::Element& st = g_struct_statetable[ m_state];
	Tag rt = st.tag;
	if (!m_impl)
	{
		val.clear();
		return rt;
	}
	switch (st.valueType)
	{
		case _NULL:
			val.clear();
			break;
		case _TAG:
			val = g_struct_elements[ st.tagnameIndex];
			break;
		case _ELEM:
			val = getElementValue( *m_impl, st.valueIndex);
			break;
	}
	m_state = st.nextState;
	return rt;
}

void DocumentFrequencyChangeFilter::skip()
{
	const filter::StateTable::Element& st = g_struct_statetable[ m_state];
	m_state = st.skipState;
}

BindingFilterInterface* DocumentFrequencyChangeFilter::createCopy() const
{
	return new DocumentFrequencyChangeFilter(*this);
}

