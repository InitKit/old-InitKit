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
 * @file auto.hh
 * @brief Wrappers to give automatic storage-duration to some other datatypes.
 */

#ifndef AUTO_HH_
#define AUTO_HH_

#include <stdio.h>

template <class T> class Auto {
    public:
	T obj;
	/* A function of this signature is called on going out-of-scope. */
	typedef void (*Deleter)(T &);
};

template <class T> class AutoPtr {
    public:
	T *ptr;

	AutoPtr()
	{
		ptr = NULL;
	}
	AutoPtr(T *ptr) : ptr(ptr){};
	AutoPtr(const AutoPtr &other) = delete;
	~AutoPtr()
	{
		free(ptr);
	}

	AutoPtr &operator=(T *dat)
	{
		release();
		ptr = dat;
		return *this;
	}

	operator T *()
	{
		return ptr;
	}

	void release()
	{
		free(ptr);
		ptr = NULL;
	}
};

class FileStar {
    public:
	FILE *file;

	FileStar() : file(NULL){};
	FileStar(FILE *file) : file(file){};
	FileStar(const FileStar &other) = delete;
	~FileStar()
	{
		if (file != NULL)
			fclose(file);
	}

	FileStar &operator=(FILE *dat)
	{
		if (file)
			fclose(file);
		file = dat;
		return *this;
	}

	operator FILE *()
	{
		return file;
	}

	void release()
	{
		if (file)
			fclose(file);
		file = NULL;
	}
};

#endif /* AUTO_HH_ */
