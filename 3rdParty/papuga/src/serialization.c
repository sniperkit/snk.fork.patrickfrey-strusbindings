/*
 * Copyright (c) 2017 Patrick P. Frey
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
/// \brief Serialization of structures for papuga language bindings
/// \file serialization.c
#include "papuga/serialization.h"
#include <stdlib.h>

static bool alloc_nodes( papuga_Serialization* self, size_t addsize)
{
	size_t newsize = self->arsize + addsize;
	if (newsize < self->arsize) return false;
	size_t mm = self->arsize * 2;
	while (mm > self->arsize && mm < newsize) mm *= 2;
	mm *= sizeof(papuga_Node);
	if (mm < newsize) return false;
	papuga_Node* newmem = (papuga_Node*)realloc( self->ar, mm);
	if (newmem == NULL) return false;
	self->ar = newmem;
	return true;
}

static inline bool add_node( papuga_Serialization* self, const papuga_Node nd)
{
	if (!alloc_nodes( self, 1)) return false;
	memcpy( self->ar + self->arsize, &nd, sizeof(papuga_Node));
	self->arsize += 1;
	return true;
}

static inline bool add_nodes( papuga_Serialization* self, const papuga_Node* ar, size_t arsize)
{
	if (!alloc_nodes( self, arsize)) return false;
	memcpy( self->ar + self->arsize, ar, arsize * sizeof(papuga_Node));
	self->arsize += arsize;
	return true;
}

#define PUSH_NODE_1(self,TAG,CONV,p1)\
	papuga_Node nd;\
	nd.tag = TAG;\
	CONV( &nd, p1);\
	return add_node( self, nd);

#define PUSH_NODE_2(self,TAG,CONV,p1,p2)\
	papuga_Node nd;\
	nd.tag = TAG;\
	CONV( &nd, p1, p2);\
	return add_node( self, nd);

#define PUSH_NODE_3(self,TAG,CONV,p1,p2,p3)\
	papuga_Node nd;\
	nd.tag = TAG;\
	CONV( &nd, p1, p2, p3);\
	return add_node( self, nd);


bool papuga_Serialization_pushOpen( papuga_Serialization* self)
{
	papuga_Node nd;
	nd.tag = papuga_TagOpen;
	nd.value.init();
	return add_node( self, nd);
}

bool papuga_Serialization_pushClose( papuga_Serialization* self)
{
	papuga_Node nd;
	nd.tag = papuga_TagClose;
	nd.value.init();
	return add_node( self, nd);
}

bool papuga_Serialization_pushName( papuga_Serialization* self, const papuga_ValueVariant* name)
	{PUSH_NODE_1(self,papuga_TagName,papuga_assign_ValueVariant,name)}

bool papuga_Serialization_pushName_string( papuga_Serialization* self, const char* name, int namelen)
	{PUSH_NODE_2(self,papuga_TagName,papuga_init_ValueVariant_string,name,namelen)}

bool papuga_Serialization_pushName_charp( papuga_Serialization* self, const char* name)
	{PUSH_NODE_1(self,papuga_TagName,papuga_init_ValueVariant_charp,name)}

bool papuga_Serialization_pushName_langstring( papuga_Serialization* self, papuga_StringEncoding enc, const char* name, int namelen)
	{PUSH_NODE_3(self,papuga_TagName,papuga_init_ValueVariant_langstring,enc,name,namelen)}

bool papuga_Serialization_pushName_int( papuga_Serialization* self, int64_t name)
	{PUSH_NODE_1(self,papuga_TagName,papuga_init_ValueVariant_int,name)}

bool papuga_Serialization_pushName_uint( papuga_Serialization* self, uint64_t name)
	{PUSH_NODE_1(self,papuga_TagName,papuga_init_ValueVariant_uint,name)}

bool papuga_Serialization_pushName_double( papuga_Serialization* self, double name)
	{PUSH_NODE_1(self,papuga_TagName,papuga_init_ValueVariant_double,name)}


bool papuga_Serialization_pushValue( papuga_Serialization* self, const papuga_ValueVariant* value)
	{PUSH_NODE_1(self,papuga_TagValue,papuga_assign_ValueVariant,value)}

bool papuga_Serialization_pushValue_string( papuga_Serialization* self, const char* value, int valuelen)
	{PUSH_NODE_2(self,papuga_TagValue,papuga_init_ValueVariant_string,value,valuelen)}

bool papuga_Serialization_pushValue_charp( papuga_Serialization* self, const char* value)
	{PUSH_NODE_1(self,papuga_TagValue,papuga_init_ValueVariant_charp,value)}

bool papuga_Serialization_pushValue_langstring( papuga_Serialization* self, papuga_StringEncoding enc, const char* value, int valuelen)
	{PUSH_NODE_3(self,papuga_TagValue,papuga_init_ValueVariant_langstring,enc,value,valuelen)}

bool papuga_Serialization_pushValue_int( papuga_Serialization* self, int64_t value)
	{PUSH_NODE_1(self,papuga_TagValue,papuga_init_ValueVariant_int,value)}

bool papuga_Serialization_pushValue_uint( papuga_Serialization* self, uint64_t value)
	{PUSH_NODE_1(self,papuga_TagValue,papuga_init_ValueVariant_uint,value)}

bool papuga_Serialization_pushValue_double( papuga_Serialization* self, double value)
	{PUSH_NODE_1(self,papuga_TagValue,papuga_init_ValueVariant_double,value)}



bool papuga_Serialization_append( papuga_Serialization* self, const papuga_Serialization* o)
{
	return add_nodes( self, o.ar, o.arsize);
}

bool papuga_Serialization_islabeled( const papuga_Serialization* self)
{
	papuga_Node const* nd;
	size_t ni = 0, ne = self.arsize;
	for (; ni != ne; ++ni)
	{
		if (ni->tag == papuga_TagName) return true;
		if (ni->tag == papuga_TagValue) return false;
	}
	return false;
}

#ifdef __cplusplus
}
#endif
#endif


