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
/// \file queryInstructionFilter.cpp
#include "queryInstructionFilter.hpp"
#include "structElementArray.hpp"
#include "stateTable.hpp"
#include <cstring>

using namespace strus;

static const char* g_element_names[] = { "opCode","idx","nofOperands", 0};
static const filter::StructElementArray g_struct_elements( g_element_names);

enum TermState {
	StateEnd,
	StateOpCodeOpen,
	StateOpCodeValue,
	StateOpCodeClose,
	StateIdxOpen,
	StateIdxValue,
	StateIdxClose,
	StateNofOperandsOpen,
	StateNofOperandsValue,
	StateNofOperandsClose
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
	{StateOpCodeOpen, _OPEN, StateOpCodeValue, StateIdxOpen, _TAG, 0, -1},
	{StateOpCodeValue, _VALUE, StateOpCodeClose, StateOpCodeClose, _ELEM, -1, 0},
	{StateOpCodeClose, _CLOSE, StateIdxOpen, StateIdxOpen, _NULL, -1, -1},
	{StateIdxOpen, _OPEN, StateIdxValue, StateNofOperandsOpen, _TAG, 1, -1},
	{StateIdxValue, _VALUE, StateIdxClose, StateIdxClose, _ELEM, -1, 1},
	{StateIdxClose, _CLOSE, StateNofOperandsOpen, StateNofOperandsOpen, _NULL, -1, -1},
	{StateNofOperandsOpen, _OPEN, StateNofOperandsValue, StateEnd, _TAG, 2, -1},
	{StateNofOperandsValue, _VALUE, StateNofOperandsClose, StateNofOperandsClose, _ELEM, -1, 2},
	{StateNofOperandsClose, _CLOSE, StateEnd, StateEnd, _NULL, -1, -1}
};

QueryInstructionFilter::QueryInstructionFilter()
	:m_impl(0),m_ownership(0),m_state(0)
{
	std::memset( m_index, 0, sizeof(m_index));
}

QueryInstructionFilter::QueryInstructionFilter( const QueryInstructionFilter& o)
	:m_impl(o.m_impl),m_ownership(o.m_ownership),m_state(o.m_state)
{
	std::memcpy( m_index, o.m_index, sizeof(m_index));
}

QueryInstructionFilter::QueryInstructionFilter( const analyzer::Query::Instruction* impl)
	:m_impl(impl),m_ownership(0),m_state(1)
{
	std::memset( m_index, 0, sizeof(m_index));
}

QueryInstructionFilter::QueryInstructionFilter( analyzer::Query::Instruction* impl, bool withOwnership)
	:m_impl(impl),m_ownership(impl),m_state(1)
{
	std::memset( m_index, 0, sizeof(m_index));
}

QueryInstructionFilter::~QueryInstructionFilter()
{
	if (m_ownership) delete( m_ownership);
}

static bindings::ValueVariant getElementValue( const analyzer::Query::Instruction& elem, int valueIndex)
{
	switch (valueIndex) {

		case 0:
			return bindings::ValueVariant( analyzer::Query::Instruction::opCodeName( (*m_impl).opCode()));

		case 1:
			return bindings::ValueVariant( (bindings::ValueVariant::UIntType)(*m_impl).idx());

		case 2:
			return bindings::ValueVariant( (bindings::ValueVariant::UIntType)(*m_impl).nofOperands());

	}
	return bindings::ValueVariant();
}

BindingFilterInterface::Tag QueryInstructionFilter::getNext( bindings::ValueVariant& val)
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

void QueryInstructionFilter::skip()
{
	const filter::StateTable::Element& st = g_struct_statetable[ m_state];
	m_state = st.skipState;
}

BindingFilterInterface* QueryInstructionFilter::createCopy() const
{
	return new QueryInstructionFilter(*this);
}

