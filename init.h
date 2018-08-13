#define init rlimit R; \
             getrlimit(RLIMIT_STACK, &R); \
             R.rlim_cur = R.rlim_max; \
             setrlimit(RLIMIT_STACK, &R); \
             srand(time(NULL)); \
             for (int i = 0; i < 10; i ++) weights[i] = 1;
