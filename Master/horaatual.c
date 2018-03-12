
#include <stdio.h>
#include <time.h>

//-----------------------------------------------
// tempo do "clock" ( CLOCKS_PER_SEC ) em windows
//
// 1 segundo = 1000
// 1 minuto  = 1000 * 60 ... = 60.000
// ...
// entao, 30 minutos eh o mesmo que: 60.000 * 30
//
//-----------------------------------------------
//
#define TRINTA_MINUTOS 60000 * 30

int quit = 0;

// tempo definido ...
time_t tempo = TRINTA_MINUTOS;

void funcao_tinta_minuto (void)
{
    // seu codigo aqui ...
}

int main ()
{
    printf ("aguarde ...\n");

    while (!quit)
    {
        time_t t = clock ();

        if (t > tempo)
        {
            tempo += TRINTA_MINUTOS;

            // tudo aqui dentro executa a cada 30 MINUTOS ...
            // ...
            funcao_tinta_minuto ();
        }

//        Sleep (50);
    }

    return 0;
}
