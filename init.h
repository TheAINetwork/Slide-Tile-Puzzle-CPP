#define init rlimit R; \
             getrlimit(RLIMIT_STACK, &R); \
             R.rlim_cur = R.rlim_max; \
             setrlimit(RLIMIT_STACK, &R); \
             srand(time(NULL));
