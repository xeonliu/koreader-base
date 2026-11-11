/* Shim for PSP/newlib: <syslog.h>. Logging calls are no-ops. */
#ifndef KO_PSP_SYSLOG_H
#define KO_PSP_SYSLOG_H
#define LOG_EMERG 0
#define LOG_ALERT 1
#define LOG_CRIT 2
#define LOG_ERR 3
#define LOG_WARNING 4
#define LOG_NOTICE 5
#define LOG_INFO 6
#define LOG_DEBUG 7
#define LOG_PID 1
#define LOG_CONS 2
#define LOG_NDELAY 8
#define LOG_USER (1 << 3)
#define LOG_DAEMON (3 << 3)
#define LOG_AUTH (4 << 3)
#define LOG_LOCAL0 (16 << 3)
#define LOG_LOCAL1 (17 << 3)
#define LOG_LOCAL2 (18 << 3)
#define LOG_LOCAL3 (19 << 3)
#define LOG_LOCAL4 (20 << 3)
#define LOG_LOCAL5 (21 << 3)
#define LOG_LOCAL6 (22 << 3)
#define LOG_LOCAL7 (23 << 3)
static inline void openlog(const char *i, int o, int f) { (void)i; (void)o; (void)f; }
static inline void syslog(int p, const char *f, ...) { (void)p; (void)f; }
static inline void closelog(void) {}
#endif
