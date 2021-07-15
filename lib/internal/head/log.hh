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
 * @file log.hh
 * @brief Logging
 */

#ifndef LOG_HH_
#define LOG_HH_

struct LogLevel {
	enum {
		kDebug,
		kInfo,
		kWarning,
		kError,
		kCritical,
		kStartup, /* critical error on startup (immediate quit) */
	};
};

#define log_startup_errno(error, ...)                                          \
	log_full_errno(LogLevel::kEmergency, VA_ARGS)

#endif /* LOG_HH_ */
