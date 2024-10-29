// Maximum number of elements in a queue
//
#define MAX_Q_SIZE	10

// declare prototypes below
void enq(double);
double deq();
void clear_sum(double *);
double sum(double, double);
double prod(double, double);
double reduce();
void clear_sum(double *);
void clear_prod(double *);   
double flex_reduce(void (*clear)(double *), double (*op)(double, double));
