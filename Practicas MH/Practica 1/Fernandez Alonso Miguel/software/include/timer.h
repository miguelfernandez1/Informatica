typedef enum type_timer {REAL, VIRTUAL} TIMER_TYPE;

extern clock_t start_time;

extern double elapsed;

int time_expired();

void start_timers();

double elapsed_time( TIMER_TYPE type );