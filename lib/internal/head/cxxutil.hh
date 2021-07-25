/*
 * +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * 		PROPRIETARY NOTICE:
 *
 * The software contained on this media is unpublished proprietary information
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
 * @file cxxutil.hh
 * @brief Miscellaneous C++-related utility functions and classes.
 */

#ifndef CXXUTIL_HH_
#define CXXUTIL_HH_

#include <exception>
#include <sstream>
#include <string>

#pragma region Automatic wrappers

typedef void (*FreeLikeDeleter)(void *);

template <class T, class Deleter, Deleter deleter> class Auto {
	T m_obj;

	void assign(T newobj) /* maun also delete any old m_obj */
	{
		if (m_obj)
			(*deleter)(m_obj);
		m_obj = newobj;
	}

    public:
	Auto(T newobj = 0) : m_obj(newobj){};
	virtual ~Auto()
	{
		assign(0);
	}

	operator T() const
	{
		return m_obj;
	}
	T operator->() const
	{
		return m_obj;
	}
	T release()
	{
		assign(0);
		return m_obj;
	}
	Auto &operator=(T newobj)
	{
		assign(newobj);
		return *this;
	}
};

typedef Auto<FILE *, int (*)(FILE *), fclose> FileStar;

#pragma endregion

template <typename T>
inline std::string
toStr(const T &n)
{
	std::ostringstream stm;
	stm << n;
	return stm.str();
}

class IKException : public std::exception {
	char m_what[255];

    public:
	IKException(const char *msg, ...);
	IKException(int ecode, const char *msg, ...);

	virtual const char *what() const noexcept override;
};

#endif /* CXXUTIL_HH_ */
