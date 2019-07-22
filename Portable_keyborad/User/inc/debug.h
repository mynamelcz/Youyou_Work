#ifndef DEBUG_H__
#define DEBUG_H__



#define DBG_ENABLE
#define DBG_COLOR




/* DEBUG level */
#define DBG_LOG             0
#define DBG_INFO            1
#define DBG_WARNING         2
#define DBG_ERROR           3

#ifndef DBG_SECTION_NAME
#define DBG_SECTION_NAME    "DBG"
#endif


#ifdef DBG_ENABLE

#ifndef DBG_LEVEL
#define DBG_LEVEL         DBG_LOG
#endif

/*
 * The color for terminal (foreground)
 * BLACK    30
 * RED      31
 * GREEN    32
 * YELLOW   33
 * BLUE     34
 * PURPLE   35
 * CYAN     36
 * WHITE    37
 */
#ifdef DBG_COLOR
#define _DBG_COLOR(n)        DBUG_Printf("\033["#n"m")
#define _DBG_LOG_HDR(lvl_name, color_n)                    \
    DBUG_Printf("\033["#color_n"m["lvl_name"/"DBG_SECTION_NAME"] ")
#else
#define _DBG_COLOR(n)
#define _DBG_LOG_HDR(lvl_name, color_n)                    \
    DBUG_Printf("["lvl_name"/"DBG_SECTION_NAME"] ")
#endif /* DBG_COLOR */

/*
 * static debug routine
 */
#define dbg_log(level, fmt, ...)                            \
    if ((level) >= DBG_LEVEL)                               \
    {                                                       \
        switch(level)                                       \
        {                                                   \
            case DBG_ERROR:   _DBG_LOG_HDR("E", 31); break; \
            case DBG_WARNING: _DBG_LOG_HDR("W", 33); break; \
            case DBG_INFO:    _DBG_LOG_HDR("I", 34); break; \
            case DBG_LOG:     _DBG_LOG_HDR("D", 0); break;  \
            default: break;                                 \
        }                                                   \
        DBUG_Printf(fmt, ##__VA_ARGS__);                     \
        _DBG_COLOR(0);                                      \
    }

#define dbg_here                                            \
    if ((DBG_LEVEL) >= DBG_LOG){                            \
        DBUG_Printf(DBG_SECTION_NAME " Here %s:%d\n",        \
            __FUNCTION__, __LINE__);                        \
    }

#define dbg_enter                                           \
    if ((DBG_LEVEL) >= DBG_LOG){                            \
        _DBG_COLOR(32);                                     \
        DBUG_Printf(DBG_SECTION_NAME " Enter %s\n",          \
            __FUNCTION__);                                  \
        _DBG_COLOR(0);                                      \
    }

#define dbg_exit                                            \
    if ((DBG_LEVEL) >= DBG_LOG){                            \
        _DBG_COLOR(32);                                     \
        DBUG_Printf(DBG_SECTION_NAME " Exit  %s:%d\n",       \
            __FUNCTION__);                                  \
        _DBG_COLOR(0);                                      \
    }

#define dbg_log_line(level, ...)                            \
    dbg_log(level, __VA_ARGS__);                            \
    if ((level) >= DBG_LEVEL) {                             \
        DBUG_Printf("\n");                                   \
    }

#define dbg_raw(...)         DBUG_Printf(__VA_ARGS__);

#else
#define dbg_log(level, fmt, ...)
#define dbg_here
#define dbg_enter
#define dbg_exit
#define dbg_log_line(level, ...)
#define dbg_raw(...)
#endif

#define LOG_D(...)           dbg_log_line(DBG_LOG    , __VA_ARGS__)
#define LOG_I(...)           dbg_log_line(DBG_INFO   , __VA_ARGS__)
#define LOG_W(...)           dbg_log_line(DBG_WARNING, __VA_ARGS__)
#define LOG_E(...)           dbg_log_line(DBG_ERROR  , __VA_ARGS__)
#define LOG_RAW(...)         dbg_raw(__VA_ARGS__)

		
		
		
		
		
		
		
		
		
		
#endif /* RT_DBG_H__ */
		
		
		
		
		
		
		
		
		
		
		
		
		
		








