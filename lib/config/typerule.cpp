/******************************************************************************
 * Icinga 2                                                                   *
 * Copyright (C) 2012 Icinga Development Team (http://www.icinga.org/)        *
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

#include "i2-config.h"

using namespace icinga;

TypeRule::TypeRule(TypeSpecifier type, const String& namePattern,
    const TypeRuleList::Ptr& subRules, const DebugInfo& debuginfo)
	: m_Type(type), m_NamePattern(namePattern), m_SubRules(subRules), m_DebugInfo(debuginfo)
{ }

TypeRuleList::Ptr TypeRule::GetSubRules(void) const
{
	return m_SubRules;
}

bool TypeRule::MatchName(const String& name) const
{
	return (Utility::Match(m_NamePattern, name));
}

bool TypeRule::MatchValue(const Value& value) const
{
	if (value.IsEmpty())
		return true;

	switch (m_Type) {
		case TypeAny:
			return true;

		case TypeString:
			/* fall through; any scalar can be converted to a string */
		case TypeScalar:
			return value.IsScalar();

		case TypeNumber:
			try {
				Convert::ToDouble(value);
			} catch (...) {
				return false;
			}
			
			return true;

		case TypeDictionary:
			return value.IsObjectType<Dictionary>();

		default:
			return false;
	}
}

