#define OBJRELEASE(X) if (X) (X)->Release(); X = NULL;
#define OBJDELETE(X) if (X) delete X; X = NULL;
#define OBJSDELETE(X) if (X) delete [] X; X = NULL;
#define OBJFREE(X) if (X) free(X); X = NULL;

#define GET_CONJOINED_PATH(path, res) (!path || !res)?"":path##res
#define SET_CONJOINED_PATH(buffer, path, res) (!path || !res)?(buffer = ""):(buffer = &string(path).append(res)[0u])

#define DEFAULT "DEFAULT"

typedef char * _charP;