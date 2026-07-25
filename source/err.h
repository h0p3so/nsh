#ifndef NHS_ERR_H
#define NHS_ERR_H

#define NSH_ERR_CHECKPTR(p, s, m) do { \
	if (p) { break; }                     \
	err_fatal(s, m);                      \
} while (0)

void err_fatal (const char*, const char*);

#endif
