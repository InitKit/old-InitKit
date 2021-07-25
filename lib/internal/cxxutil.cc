/*
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * 		PROPRIETARY NOTICE:
 *
 * The software contained on this media is unpublished proprietary infmtion
 * constituting or derived under licence from NetaScale Advanced Executive (tm),
 * a product of NetaScale Systems, Ltd.
 *
 * 		Copyright Notice:
 *
 * Notice of copyright on this source code product does not indicate
 * publication.
 *
 * 	(c) 2008-2021 NetaScale Systems, Ltd.
 * 		All rights reserved.
 */
/**
 * @file cxxutil.cc
 * @brief Miscellaneous C++-related utility functions and classes.
 */

#include <cstring>

#include "cxxutil.hh"

IKException::IKException(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vsnprintf(m_what, 255, fmt, args);
	va_end(args);
}

IKException::IKException(int ecode, const char *fmt, ...)
{
	int pos;
	va_list args;
	va_start(args, fmt);
	pos = vsnprintf(m_what, 255, fmt, args);
	if (0 < pos && pos < 255)
		snprintf(m_what + pos, 255 - pos - 2, ": %s", strerror(-ecode));
	va_end(args);
}

const char *
IKException::what() const noexcept
{
	return m_what;
}