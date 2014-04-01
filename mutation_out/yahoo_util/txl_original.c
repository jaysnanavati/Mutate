#if STDC_HEADERS
# include <string.h>
#else
# if !HAVE_STRCHR
#  define strchr index
#  define strrchr rindex
# endif
char * strchr (), * strrchr ();
# if !HAVE_MEMCPY
#  define memcpy(d, s, n) bcopy ((s), (d), (n))
#  define memmove(d, s, n) bcopy ((s), (d), (n))
# endif
#endif
#include "yahoo_util.h"

char * y_string_append (char * string, char * append) {
    int size = strlen (string) + strlen (append) + 1;
    char * new_string = y_renew (char, string, size);
    if (new_string == NULL) {
        new_string = y_new (char, size);
        strcpy (new_string, string);
        FREE (string);
    }
    strcat (new_string, append);
    return new_string;
}
#if !HAVE_GLIB

void y_strfreev (char * * vector) {
    char * * v;
    for (v = vector; *v; v++) {
        FREE (* v);
    }
    FREE (vector);
}

char * * y_strsplit (char * str, char * sep, int nelem) {
    char * * vector;
    char * s, * p;
    int i = 0;
    int l = strlen (sep);
    if (nelem <= 0) {
        char * s;
        nelem = 0;
        if (*str) {
            for (s = strstr (str, sep); s; s = strstr (s +l, sep), nelem++)
                ;
            if (strcmp (str +strlen (str) - l, sep))
                nelem++;
        }
    }
    vector = y_new (char *, nelem +1);
    for (p = str, s = strstr (p, sep); i < nelem && s; p = s + l, s = strstr (p, sep), i++) {
        int len = s - p;
        vector[i] = y_new (char, len +1);
        strncpy (vector [i], p, len);
        vector[i][len] = '\0';
    }
    if (i < nelem && *str)
        vector[i++] = strdup (p);
    vector[i] = NULL;
    return vector;
}

void * y_memdup (const void * addr, int n) {
    void * new_chunk = malloc (n);
    if (new_chunk)
        memcpy (new_chunk, addr, n);
    return new_chunk;
}
#endif
