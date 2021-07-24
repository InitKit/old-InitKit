#ifndef STRTONUM_H_
#define STRTONUM_H_

#include <stdlib.h>

#include "InitKit/ik_config.h"

#ifndef Have_strtonum
long long strtonum(const char *numstr, long long minval, long long maxval,
		   const char **errstrp);
#endif

#endif /* STRTONUM_H_ */
