#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;

const int NUM_CASILLAS = 63;

const int TURNO_POSADA = 1;
const int TURNO_PRISION = 2;
const int TURNO_POZO = 3;

const int NUM_JUGADORES = 4;
const int MAX_JUGADORES = 4;
const int NUM_FILAS_A_DIBUJAR = 3;
typedef enum { NORMAL, OCA, PUENTE1, PUENTE2, POZO, POSADA, LABERINTO, DADO1, DADO2, CARCEL, CALAVERA } tCasillas;
typedef tCasillas tTablero[NUM_CASILLAS];
typedef int tJugadores[NUM_JUGADORES];

int tirarDado();
int tirardadoManual();
int quienEmpieza();
void pintaTablero(const tTablero tablero, const tJugadores casillasJ);
void pintaNumCasilla(int fila, int casillasPorFila);
void pintaBorde(int casillasPorFila);
void pintaTipoCasilla(const tTablero tablero, int fila, int casillasPorFila);
void pintaJugadores(const tJugadores casillasJ, int fila, int casillasPorFila);
string casillaAstring(tCasillas casilla);
bool cargaTablero(tTablero tablero);
void iniciaTablero(tTablero tablero);
void buscaCasillaRetrocediendo(const tTablero tablero, tCasillas tipo, int& posicion);
void buscaCasillaAvanzando(const tTablero tablero, tCasillas tipo, int& posicion);
void efectoTirada(const tTablero tablero, int& casillaJ, int& penalizacion);
int saltaACasilla(const tTablero tablero, int casillaActual);
void iniciaJugadores(tJugadores casillaJ, tJugadores penalizacion);
bool esCasillaPremio(const tTablero tablero, int casilla);
int partida(const tTablero tablero);
void tirada(const tTablero tablero, int& casillaActual, int& penalizacion, bool MODO_DEBUG);

bool MODO_DEBUG;






int main() {
    tTablero tablero;
    iniciaTablero(tablero);
    cargaTablero(tablero);
    partida(tablero);
    return 0;
}



void iniciaTablero(tTablero tablero) {
    for (int i = 0; i < NUM_CASILLAS; i++) {
        tablero[i] = NORMAL;
    }
    tablero[NUM_CASILLAS - 1] = OCA;

}


bool cargaTablero(tTablero tablero) {
    ifstream archivo;
    int normal;
    //tCasillas casillas;
    string nombres_normal;
    bool abre_fichero = false;

    archivo.open("tablero.txt");
    if (archivo.is_open()) {
        abre_fichero = true;
        archivo >> normal >> nombres_normal;
        while (normal != 0) {

            //cout << normal << " " << nombres_normal << endl;
            //archivo >> normal >> nombres_normal;

            if (nombres_normal == "OCA") {
                //casillas = OCA;
                tablero[normal - 1] = OCA;
            }
            else if (nombres_normal == "PUENTE1") {
                tablero[normal - 1] = PUENTE1;
            }
            else if (nombres_normal == "PUENTE2") {
                tablero[normal - 1] = PUENTE2;
            }
            else if (nombres_normal == "POSADA") {
                tablero[normal - 1] = POSADA;
            }
            else if (nombres_normal == "DADO1") {
                tablero[normal - 1] = DADO1;
            }
            else if (nombres_normal == "POZO") {
                tablero[normal - 1] = POZO;
            }
            else if (nombres_normal == "LABERINTO") {
                tablero[normal - 1] = LABERINTO;
            }
            else if (nombres_normal == "CARCEL") {
                tablero[normal - 1] = CARCEL;
            }
            else if (nombres_normal == "DADO2") {
                tablero[normal - 1] = DADO2;
            }
            else if (nombres_normal == "CALAVERA") {
                tablero[normal - 1] = CALAVERA;
            }

            archivo >> normal >> nombres_normal;







        }
    }
    else {
        cout << "No se ha podido abrir el archivo" << endl;

    }

    archivo.close();







    return abre_fichero;
}

int tirarDado() {
    int dado;
    srand(time(0));
    dado = rand() % 6 + 1;
    return dado;
}
int tirardadoManual() {
    int dado;
    cin >> dado;
    return dado;
}
int quienEmpieza() {
    int jugador;
    srand(time(0));
    jugador = rand() % NUM_JUGADORES + 1;
    cout << "\tCOMIENZA EL JUGADOR " << jugador << endl;
    return jugador;
}
bool esCasillaPremio(const tTablero tablero, int casilla) {
    bool premio = false;
    if (tablero[casilla - 1] == OCA || tablero[casilla - 1] == PUENTE1 || tablero[casilla - 1] == DADO1) {
        premio = true;
    }
    return premio;
}
int saltaACasilla(const tTablero tablero, int casillaActual) {
    if (esCasillaPremio(tablero, casillaActual)) {
        if (tablero[casillaActual - 1] == OCA && casillaActual < NUM_CASILLAS) {
            tCasillas tipo = OCA;
            cout << "HAS CAIDO EN UNA OCA, PASAS A LA SIGUIENTE OCA" << endl;
            buscaCasillaAvanzando(tablero, tipo, casillaActual);
            cout << "CASILLA ACTUAL: " << casillaActual << endl;
            cout << "DE OCA EN OCA Y TIRO PORQUE ME TOCA" << endl;
        }
        else {
            if (tablero[casillaActual - 1] == PUENTE1) {
                tCasillas tipo = PUENTE1;
                cout << "HAS CAIDO EN UN PUENTE, PASAS A EL SIGUIENTE PUENTE" << endl;
                buscaCasillaAvanzando(tablero, tipo, casillaActual);
                cout << "CASILLA ACTUAL: " << casillaActual << endl;
                cout << "DE PUENTE EN PUENTE Y TIRO PORQUE ME LLEVA LA CORRIENTE" << endl;
            }
            else {
                if (tablero[casillaActual - 1] == DADO1) {
                    tCasillas tipo = DADO2;
                    cout << "HAS CAIDO EN UN DADO, PASAS A EL SIGUIENTE DADO" << endl;
                    buscaCasillaAvanzando(tablero, tipo, casillaActual);
                    cout << "CASILLA ACTUAL: " << casillaActual << endl;
                    cout << "DE DADO A DADO Y TIRO PORQUE ME HA TOCADO" << endl;
                }
            }
        }

    }
    else {
        if (tablero[casillaActual - 1] == CALAVERA) {
            cout << "HAS CAIDO EN LA CALAVERA, RETROCEDES A LA PRIMERA CASILLA" << endl;
            casillaActual = 1;
            cout << "CASILLA ACTUAL: " << casillaActual << endl;
        }
        else {
            if (tablero[casillaActual - 1] == LABERINTO) {
                cout << "HAS CAIDO EN EL LABERINTO, RETROCEDES 12 CASILLAS" << endl;
                casillaActual = casillaActual - 12;
                cout << "CASILLA ACTUAL: " << casillaActual << endl;
            }
            else {
                if (tablero[casillaActual - 1] == DADO2) {
                    tCasillas tipo = DADO2;
                    cout << "HAS CAIDO EN UN DADO, RETROCEDES A EL SIGUIENTE DADO" << endl;
                    buscaCasillaRetrocediendo(tablero, tipo, casillaActual);
                    cout << "CASILLA ACTUAL: " << casillaActual << endl;
                }
                else {
                    if (tablero[casillaActual - 1] == PUENTE2) {
                        tCasillas tipo = PUENTE2;
                        cout << "HAS CAIDO EN UN PUENTE, RETROCEDES AL PUENTE ANTERIOR" << endl;
                        buscaCasillaRetrocediendo(tablero, tipo, casillaActual);
                        cout << "CASILLA ACTUAL: " << casillaActual << endl;

                    }
                }
            }
        }
    }
    return casillaActual;
}
void efectoTirada(const tTablero tablero, int& casillaJ, int& penalizacion) {


    if (esCasillaPremio(tablero, casillaJ)) {
        casillaJ = saltaACasilla(tablero, casillaJ);
    }
    else {
        if (tablero[casillaJ - 1] == CALAVERA) {
            casillaJ = saltaACasilla(tablero, casillaJ);

        }
        else {
            if (tablero[casillaJ - 1] == LABERINTO) {
                casillaJ = saltaACasilla(tablero, casillaJ);

            }
            else {
                if (tablero[casillaJ - 1] == POSADA) {
                    //casillaJ = saltaACasilla(tablero, casillaJ);
                    cout << "HAS CAIDO EN LA POSADA, PIERDES UN TURNO" << endl;
                    penalizacion = penalizacion + 1;

                }
                else {
                    if (tablero[casillaJ - 1] == CARCEL) {
                        //casillaJ = saltaACasilla(tablero, casillaJ);
                        cout << "HAS CAIDO EN LA CARCEL, PIERDES DOS TURNOS" << endl;
                        penalizacion = penalizacion + 2;

                    }
                    else {
                        if (tablero[casillaJ - 1] == POZO) {
                            //casillaJ = saltaACasilla(tablero, casillaJ);
                            cout << "HAS CAIDO EN EL POZO, PIERDES TRES TURNOS" << endl;
                            penalizacion = penalizacion + 3;

                        }
                        else {
                            if (tablero[casillaJ - 1] == DADO2) {
                                casillaJ = saltaACasilla(tablero, casillaJ);
                            }
                            else {
                                if (tablero[casillaJ - 1] == PUENTE2) {
                                    casillaJ = saltaACasilla(tablero, casillaJ);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}




void buscaCasillaAvanzando(const tTablero tablero, tCasillas tipo, int& posicion) {
    //int i = posicion;
    if (tipo == DADO1) {
        tipo = DADO2;
    }
    else {
        if (tipo == PUENTE1) {
            tipo = PUENTE2;
        }
    }
    while (posicion < NUM_CASILLAS && tablero[posicion] != tipo) {
        posicion++;

    }
    posicion++;
}

void buscaCasillaRetrocediendo(const tTablero tablero, tCasillas tipo, int& posicion) {
    //int i = posicion;
    if (tipo == DADO2) {
        tipo = DADO1;
    }
    else {
        if (tipo == PUENTE2) {
            tipo = PUENTE1;
        }
    }
    while (posicion < NUM_CASILLAS && tablero[posicion] != tipo) {
        posicion--;

    }
    posicion++;

}


void iniciaJugadores(tJugadores casillasJ, tJugadores penalizacion) {

    casillasJ[0] = 1;
    casillasJ[1] = 1;
    casillasJ[2] = 1;
    casillasJ[3] = 1;

    penalizacion[0] = 0;
    penalizacion[1] = 0;
    penalizacion[2] = 0;
    penalizacion[3] = 0;

}

string casillaAstring(tCasillas casilla) {
    string cadena;
    switch (casilla) {
    case NORMAL:
        cadena = " ";
        break;
    case OCA:
        cadena = "OCA";
        break;
    case DADO1:
    case DADO2:
        cadena = "DADO";
        break;
    case PUENTE1:
    case PUENTE2:
        cadena = "PNTE";
        break;
    case POSADA:
        cadena = "PSDA";
        break;
    case CALAVERA:
        cadena = "MUER";
        break;
    case LABERINTO:
        cadena = "LBRN";
        break;
    case POZO:
        cadena = "POZO";
        break;
    case CARCEL:
        cadena = "CRCL";
        break;
    }
    return cadena;
}

void pintaTablero(const tTablero tablero, const tJugadores casillasJ) {


    int casillasPorFila = NUM_CASILLAS / NUM_FILAS_A_DIBUJAR;
    cout << endl;
    for (int fila = 0; fila < NUM_FILAS_A_DIBUJAR; fila++) {
        pintaBorde(casillasPorFila);
        pintaNumCasilla(fila, casillasPorFila);
        pintaTipoCasilla(tablero, fila, casillasPorFila);
        pintaJugadores(casillasJ, fila, casillasPorFila);
    }
    pintaBorde(casillasPorFila);
    cout << endl;
}


void pintaBorde(int casillasPorFila) {

    for (int i = 1; i <= casillasPorFila; i++)
        cout << "|====";

    cout << "|" << endl;

}


void pintaNumCasilla(int fila, int casillasPorFila) {

    for (int i = 1; i <= casillasPorFila; i++)
        cout << "| " << setw(2) << setfill('0') << i + fila * casillasPorFila << " ";

    cout << "|" << endl;

}


void pintaTipoCasilla(const tTablero tablero, int fila, int casillasPorFila) {

    for (int i = 1; i <= casillasPorFila; i++)
        cout << "|" << setw(4) << setfill(' ') << casillaAstring(tablero[i - 1 + fila * casillasPorFila]);

    cout << "|" << endl;

}

void pintaJugadores(const tJugadores casillasJ, int fila, int casillasPorFila) {
    int casilla;

    int blancos = MAX_JUGADORES - NUM_JUGADORES;
    string b = "";
    for (int i = 0; i < blancos; i++) b = b + " ";
    cout << "|";
    for (int i = 1; i <= casillasPorFila; i++) {
        casilla = i + fila * casillasPorFila;
        for (int jug = 0; jug < NUM_JUGADORES; jug++) {
            if (casillasJ[jug] == casilla)
                cout << jug + 1;
            else
                cout << " ";
        }
        cout << b;
        cout << "|";
    }
    cout << endl;

}

void tirada(const tTablero tablero, int& casillaActual, int& penalizacion, bool MODO_DEBUG) {
    bool premio = esCasillaPremio(tablero, casillaActual);
    char siguiente = '\n';
    int dado;
    if (premio) {
        while (premio && casillaActual < NUM_CASILLAS) {
            cout << "VUELVES A TIRAR" << endl;
            cin.get(siguiente);
            if (MODO_DEBUG == true) {
                cout << "VALOR DEL DADO: ";
                dado = tirardadoManual();
                cout << endl;
            }
            else {
                cout << "VALOR DEL DADO: ";
                dado = tirarDado();
                cout << dado << endl;
            }
            casillaActual = casillaActual + dado;
            cout << "PASAS A LA CASILLA: " << casillaActual << endl;
            premio = esCasillaPremio(tablero, casillaActual);
            efectoTirada(tablero, casillaActual, penalizacion);
        }
    }
}





int partida(const tTablero tablero) {
    srand(time(NULL));
    char siguiente = '\n';
    bool premio;
    int casillaActual = 1;
    int penalizacionJ = 0;
    tJugadores casillasJ;
    tJugadores penalizacion;
    iniciaJugadores(casillasJ, penalizacion);
    //tTablero tablero;
    //tCasillas casillas;
    int dado;
    int jugador;
    //iniciaTablero(tablero);
    //cargaTablero(tablero);
    pintaTablero(tablero, casillasJ);
    cout << "\t**** LA OCA ****" << endl;
    cout << "SELECCIONE MODO DE JUEGO:" << endl;
    cout << "MODO NORMAL(0) ------- MODO DEBUG(1)" << endl;
    cin >> MODO_DEBUG;

    int i = 0;

    jugador = quienEmpieza();

    while (casillasJ[jugador - 2] < NUM_CASILLAS) { //si el ultimo jugador llega a el final, NO GANA, HAY QUE ARREGLARLO
        //pintaTablero(tablero, casillasJ);
        penalizacionJ = penalizacion[jugador - 1];
        while (penalizacionJ > 0) {
            cout << "El jugador " << jugador << " tiene " << penalizacion[jugador - 1] << " turnos sin jugar" << endl;
            penalizacion[jugador - 1]--;
            if (jugador < NUM_JUGADORES) {
                jugador++;
            }
            else {
                jugador = 1;
            }

            cout << "\t++TURNO DEL JUGADOR " << jugador << "++" << endl;
            penalizacionJ = penalizacion[jugador - 1];
        }
        //if (penalizacionJ > 0) {
          //  cout << "El jugador " << jugador << " tiene " << penalizacion[jugador - 1] << " turnos sin jugar" << endl;
            //penalizacion[jugador - 1]--;
            //if (jugador < NUM_JUGADORES) {
              //  jugador++;
            //}
            //else {
              //  jugador = 1;
            //}

            //cout << "\t++TURNO DEL JUGADOR " << jugador << "++" << endl;

        //}
        //penalizacionJ = penalizacion[jugador - 1];
        casillaActual = casillasJ[jugador - 1];

        cout << "CASILLA ACTUAL: " << casillaActual << endl;
        if (MODO_DEBUG == true) {
            cout << "VALOR DEL DADO: ";
            dado = tirardadoManual();
            cout << endl;
        }
        else {
            cout << "VALOR DEL DADO: ";
            dado = tirarDado();
            cout << dado << endl;
        }
        casillaActual = casillaActual + dado;
        cout << "PASAS A LA CASILLA: " << casillaActual << endl;
        premio = esCasillaPremio(tablero, casillaActual);
        efectoTirada(tablero, casillaActual, penalizacionJ);
        tirada(tablero, casillaActual, penalizacionJ, MODO_DEBUG);
        /*if (premio) {
            while (premio && casillaActual < NUM_CASILLAS) {
                cout << "VUELVES A TIRAR" << endl;
                cin.get(siguiente);
                if (MODO_DEBUG == true) {
                    cout << "VALOR DEL DADO: ";
                    dado = tirardadoManual();
                    cout << endl;
                }
                else {
                    cout << "VALOR DEL DADO: ";
                    dado = tirarDado();
                    cout << dado << endl;
                }
                casillaActual = casillaActual + dado;
                cout << "PASAS A LA CASILLA: " << casillaActual << endl;
                premio = esCasillaPremio(tablero, casillaActual);
                efectoTirada(tablero, casillaActual, penalizacionJ);
            }
        }*/
        penalizacion[jugador - 1] = penalizacionJ;
        casillasJ[jugador - 1] = casillaActual;


        if (jugador == NUM_JUGADORES && casillasJ[jugador - 1] < NUM_CASILLAS) {
            jugador = 1;
        }
        else {
            jugador++;
        }
        cout << "PULSE ENTER PARA CONTINUAR";
        pintaTablero(tablero, casillasJ);
        cin.get(siguiente);
        cout << endl;
        if (casillasJ[jugador - 2] < NUM_CASILLAS) {
            cout << "\t++TURNO DEL JUGADOR " << jugador << "++" << endl;
        }
        //cout << "\t++TURNO DEL JUGADOR " << jugador << "++" << endl;
    }



    cout << "\t **** GANA LA PARTIDA EL JUGADOR " << jugador - 1 << endl;
    return jugador - 1;
}
