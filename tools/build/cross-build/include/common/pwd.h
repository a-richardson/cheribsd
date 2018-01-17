#pragma once

#include_next <pwd.h>

#define	user_from_uid	__nbcompat_user_from_uid

int
pwcache_userdb(
        int		(*a_setpassent)(int),
        void		(*a_endpwent)(void),
        struct passwd *	(*a_getpwnam)(const char *),
        struct passwd *	(*a_getpwuid)(uid_t));

int
uid_from_user(const char *name, uid_t *uid);

int
setpassent(int stayopen);

int
uid_from_user(const char *name, uid_t *uid);
const char *
user_from_uid(uid_t uid, int noname);
