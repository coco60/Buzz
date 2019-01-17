#ifndef _PILE_H
#define _PILE_H

#define ITEM_ALLOC_ERROR  1
#define PILE_EMPTY       -1

#ifdef __cplusplus
  extern "C" {
#endif

    /*  Struct to handle the type of element in Pile. */
    typedef struct Titem
            {
                    int Value;
                    struct Titem *prec;
            } Titem ;

    /*  Pile Struct. */
    typedef struct TPile
        {
                int(*Push)(struct TPile*, int);

                int(*Pop)(struct TPile*);

                int(*Length)(struct TPile*);

                void(*Free)(struct TPile*);

                void(*Clear)(struct TPile*);

                int Nombre;

                struct Titem *Top;

            } TPile ;


    /*  Pile_Create crée une pile. */
    extern TPile TPile_Create();

    extern int TPile_Push(TPile*, int);

    extern int TPile_Pop(TPile*);

    extern void TPile_Clear(TPile*);

    extern int TPile_Length(TPile*);

    extern void TPile_Free(TPile*);

#ifdef __cplusplus
}
#endif

#endif
