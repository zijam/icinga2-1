/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012-2015 Icinga Development Team (http://www.icinga.org)    *
 *                                                                            *
 * This program is free software; you can redistribute it and/or              *
 * modify it under the terms of the GNU General Public License                *
 * as published by the Free Software Foundation; either version 2             *
 * of the License, or (at your option) any later version.                     *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with this program; if not, write to the Free Software Foundation     *
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.             *
 ******************************************************************************/

#ifndef PRIMITIVETYPE_H
#define PRIMITIVETYPE_H

#include "base/i2-base.hpp"
#include "base/type.hpp"
#include "base/initialize.hpp"

namespace icinga
{

class I2_BASE_API PrimitiveType : public Type
{
public:
	PrimitiveType(const String& name, const ObjectFactory& factory = ObjectFactory());

	virtual String GetName(void) const;
	virtual Type::Ptr GetBaseType(void) const;
	virtual int GetAttributes(void) const;
	virtual int GetFieldId(const String& name) const;
	virtual Field GetFieldInfo(int id) const;
	virtual int GetFieldCount(void) const;

protected:
	virtual ObjectFactory GetFactory(void) const;

private:
	String m_Name;
	ObjectFactory m_Factory;
};

#define REGISTER_BUILTIN_TYPE(type, prototype)					\
	namespace { namespace UNIQUE_NAME(prt) { namespace prt ## type {	\
		void RegisterBuiltinType(void)					\
		{								\
			icinga::Type::Ptr t = new PrimitiveType(#type);		\
			t->SetPrototype(prototype);				\
			icinga::Type::Register(t);				\
		}								\
		INITIALIZE_ONCE_WITH_PRIORITY(RegisterBuiltinType, 15);		\
	} } }

#define REGISTER_PRIMITIVE_TYPE_FACTORY(type, prototype, factory)		\
	namespace { namespace UNIQUE_NAME(prt) { namespace prt ## type {	\
		void RegisterPrimitiveType(void)				\
		{								\
			icinga::Type::Ptr t = new PrimitiveType(#type, factory);\
			t->SetPrototype(prototype);				\
			icinga::Type::Register(t);				\
			type::TypeInstance = t;					\
		}								\
		INITIALIZE_ONCE_WITH_PRIORITY(RegisterPrimitiveType, 15);	\
	} } }									\
	DEFINE_TYPE_INSTANCE(type)

#define REGISTER_PRIMITIVE_TYPE(type, prototype)				\
	REGISTER_PRIMITIVE_TYPE_FACTORY(type, prototype, DefaultObjectFactory<type>)

#define REGISTER_PRIMITIVE_TYPE_NOINST(type, prototype)				\
	REGISTER_PRIMITIVE_TYPE_FACTORY(type, prototype, NULL)

}

#endif /* PRIMITIVETYPE_H */
