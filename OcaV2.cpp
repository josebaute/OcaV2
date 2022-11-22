#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;


const int NUM_CASILLAS = 63;

const int TURNO_POSADA = 1;
const int TURNO_PRISION = 2;
const int TURNO_POZO = 3;

const int NUM_JUGADORES = 4;

typedef enum { NORMAL, OCA, PUENTE1, PUENTE2, POZO, POSADA, LABERINTO, DADO1, DADO2, CARCEL, CALAVERA } tCasillas;
typedef tCasillas tTablero[NUM_CASILLAS];
typedef int tJugadores[NUM_JUGADORES];





bool MODO_DEBUG;

int jugador;
int turnos;

char siguiente;

bool esOca(int casilla);
bool esPuente(int casilla);
bool esDados(int casilla);
bool esLaberinto(int casilla);
bool esMuerte(int casilla);
bool esPosada(int casilla);
bool esPrision(int casilla);
bool esPozo(int casilla);
bool esMeta(int casilla);

int siguienteOca(int casilla);
int siguientePuente(int casilla);
int siguienteDado(int casilla);
int siguienteLaberinto();
int siguienteMuerte();

int tirarDado();
int tirardadoManual();
int quienEmpieza();
int efectoPosicion(int casillaActual);
int efectoTiradas(int casillaActual, int numerodeTiradas);


int cambiodeJugador(int casillaActual);



void iniciaTablero(tTablero tablero);
void buscaCasillaAvanzando(const tTablero tablero, tCasillas tipo, int& posicion);

int main() {
    /*srand(time(NULL));
    int casilla;
    int casillaActual = 1;
    tJugadores posiciones;
    int dado;
    int tr;
    cout << "\t**** LA OCA ****" << endl;
    cout << "SELECCIONE MODO DE JUEGO:" << endl;
    cout << "MODO NORMAL(0) ------- MODO DEBUG(1)" << endl;
    cin >> MODO_DEBUG;
    turnoJ = quienEmpieza();
    while (posiciones[0] < NUM_CASILLAS && posiciones[2] < NUM_CASILLAS && posiciones[4] < NUM_CASILLAS && posiciones[6] < NUM_CASILLAS)�? {
        //JUGADOR 1
        if (jugador == 1) {
            posiciones[�?] = casillaActual;
            cout << "CASILLA ACTUAL: " << posiciones[�?] << endl;
            if (MODO_DEBUG == true) {
                cout << "VALOR DEL DADO: ";
                dado = tirardadoManual();
                cout << endl;
            }
            else {
                cout << "VALOR DEL DADO: ";
                dado = tirarDado();
                cout << endl;
            }
            posiciones[�?] = posiciones[�?] + dado;
            cout << "PASAS A LA CASILLA: " << posiciones[�?] << endl;
            posiciones[�?] = efectoPosicion(posiciones[�?]);
            casillaJ1 = posicion;
            cout << posicion << endl;
            tr = efectoTiradas(casillaJ1, tiradas);
            while (tr > 0) {
                cout << "\n\tPULSE ENTER PARA TIRAR";
                cin.get(siguiente);
                cout << endl;
                if (MODO_DEBUG == true) {
                    cout << "VALOR DEL DADO: ";
                    tirardadoManual();
                }
                else {
                    cout << "VALOR DEL DADO: " << tirarDado() << endl;
                }
                casillaJ1 = casillaJ1 + dado;
                cout << "PASAS A LA CASILLA: " << casillaJ1 << endl;
                posicion = efectoPosicion(casillaJ1);
                casillaJ1 = posicion;
                cout << posicion << endl;
                tr--;
            }
            while (tr < 0) {
                cout << "TIRA EL JUGADOR 2" << endl;
                cout << "\n\tPULSE ENTER PARA TIRAR";
                cin.get(siguiente);
                cout << endl;
                cout << "\tJUGADOR 2" << endl;
                if (MODO_DEBUG == true) {
                    cout << "VALOR DEL DADO: ";
                    tirardadoManual();
                }
                else {
                    cout << "VALOR DEL DADO: " << tirarDado() << endl;
                }
                casillaJ2 = casillaJ2 + dado;
                cout << "PASAS A LA CASILLA: " << casillaJ2 << endl;
                posicion = efectoPosicion(casillaJ2);
                casillaJ2 = posicion;
                cout << posicion << endl;
                tr++;
            }
            cout << "\tPULSE ENTER PARA CONTINUAR";
            cout << endl;
            cin.get(siguiente);
            cout << endl;
            if (casillaJ1 < Meta_casilla && casillaJ2 < Meta_casilla) {
                cout << cambiodeJugador(casillaJ1) << endl;
            }
        }
        //JUGADOR 2
        else {
            casillaActual = casillaJ2;
            cout << "CASILLA ACTUAL: " << casillaJ2 << endl;
            if (MODO_DEBUG == true) {
                cout << "VALOR DEL DADO: ";
                tirardadoManual();
            }
            else {
                cout << "VALOR DEL DADO: " << tirarDado() << endl;
            }
            casillaJ2 = casillaJ2 + dado;
            cout << "PASAS A LA CASILLA: " << casillaJ2 << endl;
            posicion = efectoPosicion(casillaJ2);
            casillaJ2 = posicion;
            cout << posicion << endl;
            tr = efectoTiradas(casillaJ2, tiradas);
            while (tr > 0) {
                cout << "\n\tPULSE ENTER PARA TIRAR";
                cin.get(siguiente);
                cout << endl;
                if (MODO_DEBUG == true) {
                    cout << "VALOR DEL DADO: ";
                    tirardadoManual();
                }
                else {
                    cout << "VALOR DEL DADO: " << tirarDado() << endl;
                }
                casillaJ2 = casillaJ2 + dado;
                cout << "PASAS A LA CASILLA: " << casillaJ2 << endl;
                posicion = efectoPosicion(casillaJ2);
                casillaJ2 = posicion;
                cout << posicion << endl;
                tr--;
            }
            while (tr < 0) {
                cout << "TIRA EL JUGADOR 1" << endl;
                cout << "\n\tPULSE ENTER PARA TIRAR";
                cin.get(siguiente);
                cout << endl;
                cout << "\tJUGADOR 1" << endl;
                if (MODO_DEBUG == true) {
                    cout << "VALOR DEL DADO: ";
                    tirardadoManual();
                }
                else {
                    cout << "VALOR DEL DADO: " << tirarDado() << endl;
                }
                casillaJ1 = casillaJ1 + dado;
                cout << "PASAS A LA CASILLA: " << casillaJ1 << endl;
                posicion = efectoPosicion(casillaJ1);
                casillaJ1 = posicion;
                cout << posicion << endl;
                tr++;
            }
            cout << "\tPULSE ENTER PARA CONTINUAR";
            cin.get(siguiente);
            cout << endl;
            if (casillaJ1 < Meta_casilla && casillaJ2 < Meta_casilla) {
                cout << cambiodeJugador(casillaJ2) << endl;
            }
        }
    }
    //GANADOR
    if (casillaJ1 < Meta_casilla) {
        cout << endl;
        cout << "\n\t--GANA EL JUGADOR 2--";
        cout << endl;
    }
    else {
        cout << endl;
        cout << "\n\t--GANA EL JUGADOR 1--";
        cout << endl;
    }
    cout << endl;
    cout << endl;
    cout << endl;
    */
    tTablero tablero;
    iniciaTablero(tablero);


    return 0;
}


void iniciaTablero(tTablero tablero) {
    for (int i = 0; i < NUM_CASILLAS - 1; i++) {
        tablero[i] = NORMAL;
    }
    tablero[NUM_CASILLAS - 1] = OCA;

}


bool cargaTablero(tTablero tablero) {
    ifstream archivo;
    int normal;
    tCasillas casillas;
    string nombres_normal;
    bool abre_fichero = false;

    archivo.open("tablero.txt");
    if (archivo.is_open()) {
        abre_fichero = true;
        archivo >> normal >> nombres_normal;
        while (normal != 0) {
            //cout << normal << " " << nombres_normal << endl;
            archivo >> normal >> nombres_normal;

            if (nombres_normal == "OCA") {
                casillas = OCA;
            }
            else if (nombres_normal == "PUENTE1") {
                casillas = PUENTE1;
            }
            else if (nombres_normal == "PUENTE2") {
                casillas = PUENTE2;
            }
            else if (nombres_normal == "POSADA") {
                casillas = POSADA;
            }
            else if (nombres_normal == "DADO1") {
                casillas = DADO1;
            }
            else if (nombres_normal == "POZO") {
                casillas = POZO;
            }
            else if (nombres_normal == "LABERINTO") {
                casillas = LABERINTO;
            }
            else if (nombres_normal == "CARCEL") {
                casillas = CARCEL;
            }
            else if (nombres_normal == "DADO2") {
                casillas = DADO2;
            }
            else if (nombres_normal == "CALAVERA") {
                casillas = CALAVERA;
            }







            archivo.close();

        }
    }
    else {
        cout << "No se ha podido abrir el archivo" << endl;

    }









    return abre_fichero;
}


bool esCasillaPremio(const tTablero tablero, int casilla) {
    bool premio = false;
    if (esOca || esPuente || esDados) {
        premio = true;
    }
    return premio;
}
void buscaCasillaAvanzando(const tTablero tablero, tCasillas tipo, int& posicion) {
    cin >> posicion;
    int i = posicion;

    while (i < NUM_CASILLAS && tablero[i] != tipo) {
        i++;

    }
    posicion = i;


}

void buscaCasillaRetrocediendo(const tTablero tablero, tCasillas tipo, int& posicion) {
    int i = posicion;
    while (i < NUM_CASILLAS) {
        if (tablero[i] != tipo) {
            i--;
        }

    }
    posicion = i;
}
int saltaACasilla(const tTablero tablero, int casillaActual) {
    int posicion;
    tTablero tablero;
    tCasillas tipo;
    if (casillaActual == OCA) {
        tipo = OCA;
    }

    posicion = casillaActual;
    buscaCasillaAvanzando(tablero, tipo, posicion);
    buscaCasillaRetrocediendo(tablero, tipo, posicion);

}




/*
bool esOca(int casilla) {
    bool esOca;
    if (casilla % 9 == 0 || casilla % 9 == 5) {
        esOca = true;
    }
    else {
        esOca = false;
    }
    return esOca;
}
bool esPuente(int casilla) {
    bool esPuente;
    if (casilla == Puentes_casillas_1 || casilla == Puentes_casillas_2) {
        esPuente = true;
    }
    else {
        esPuente = false;
    }
    return esPuente;
}
bool esDados(int casilla) {
    bool esDados;
    if (casilla == Dados_casillas_1 || casilla == Dados_casillas_2) {
        esDados = true;
    }
    else {
        esDados = false;
    }
    return esDados;
}
bool esLaberinto(int casilla) {
    bool esLaberinto;
    if (casilla == Laberinto_casilla) {
        esLaberinto = true;
    }
    else {
        esLaberinto = false;
    }
    return esLaberinto;
}
bool esMuerte(int casilla) {
    bool esMuerte;
    if (casilla == Muerte_casilla) {
        esMuerte = true;
    }
    else {
        esMuerte = false;
    }
    return esMuerte;
}
bool esPosada(int casilla) {
    bool esPosada;
    if (casilla == Posada_casilla) {
        esPosada = true;
    }
    else {
        esPosada = false;
    }
    return esPosada;
}
bool esPrision(int casilla) {
    bool esPrision;
    if (casilla == Prision_casilla) {
        esPrision = true;
    }
    else {
        esPrision = false;
    }
    return esPrision;
}
bool esPozo(int casilla) {
    bool esPozo;
    if (casilla == Pozo_casilla) {
        esPozo = true;
    }
    else {
        esPozo = false;
    }
    return esPozo;
}
bool esMeta(int casilla) {
    bool esMeta;
    if (casilla == Meta_casilla) {
        esMeta = true;
    }
    else {
        esMeta = false;
    }
    return esMeta;
}
int siguienteOca(int casilla) {
    int posicion = 0;
    if (esOca(casilla) == true && casilla % 9 == 5 && casilla < 63) {
        posicion = casilla + 4;
    }
    if (esOca(casilla) == true && casilla % 9 == 0 && casilla < 63) {
        posicion = casilla + 5;
    }
    return posicion;
}
int siguientePuente(int casilla) {
    int posicion = 0;
    if (casilla == Puentes_casillas_1) {
        posicion = Puentes_casillas_2;
    }
    if (casilla == Puentes_casillas_2) {
        posicion = Puentes_casillas_1;
    }
    return posicion;
}
int siguienteDado(int casilla) {
    int posicion = 0;
    if (casilla == Dados_casillas_1) {
        posicion = Dados_casillas_2;
    }
    if (casilla == Dados_casillas_2) {
        posicion = Dados_casillas_1;
    }
    return posicion;
}
int siguienteLaberinto() {
    int posicion = 0;
    if (Laberinto_casilla) {
        posicion = Laberinto_casilla - 12;
    }
    return posicion;
}
int siguienteMuerte() {
    int posicion = 0;
    if (Muerte_casilla) {
        posicion = Inicio_casilla;
    }
    return posicion;
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
    srand(time(0));
    jugador = rand() % NUM_JUGADORES + 1;
    cout << "\tCOMIENZA EL JUGADOR ";
    return jugador;
}
int efectoPosicion(int casillaActual) {
    if (esOca(casillaActual) == true) {
        casillaActual = siguienteOca(casillaActual);
        cout << "HAS CAIDO EN UNA OCA" << endl;
        cout << "PASAS A LA SIGUIENTE OCA: ";
    }
    else if (esDados(casillaActual) == true) {
        casillaActual = siguienteDado(casillaActual);
        cout << "HAS CAIDO EN UNOS DADOS" << endl;
        cout << "PASAS AL SIGUIENTE DADO: ";
    }
    else if (esLaberinto(casillaActual) == true) {
        casillaActual = siguienteLaberinto();
        cout << "HAS CAIDO EN UN LABERINTO" << endl;
        cout << "RETROCEDE 12 CASILLAS: ";
    }
    else if (esPuente(casillaActual) == true) {
        cout << "HAS CAIDO EN UN PUENTE" << endl;
        if (casillaActual == Puentes_casillas_1) {
            cout << "AVANZAS HASTA EL SIGUIENTE PUENTE: ";
            casillaActual = siguientePuente(casillaActual);
        }
        else {
            cout << "RETROCEDES AL PUENTE ANTERIOR: ";
            casillaActual = siguientePuente(casillaActual);
        }
    }
    else if (esPosada(casillaActual) == true) {
        cout << "HAS CAIDO EN LA POSADA" << endl;
        cout << "TE QUEDAS 1 TURNO SIN JUGAR" << endl;
        cout << "CASILLA ACTUAL: ";
    }
    else if (esPrision(casillaActual) == true) {
        cout << "HAS CAIDO EN LA PRISION" << endl;
        cout << "TE QUEDAS 2 TURNOS SIN JUGAR" << endl;
        cout << "CASILLA ACTUAL: ";
    }
    else if (esPozo(casillaActual) == true) {
        cout << "HAS CAIDO EN EL POZO" << endl;
        cout << "TE QUEDAS 3 TURNOS SIN JUGAR" << endl;
        cout << "CASILLA ACTUAL: ";
    }
    else if (esMuerte(casillaActual) == true) {
        cout << "HAS CAIDO EN LA MUERTE" << endl;
        cout << "VUELVES A LA PRIMERA CASILLA: ";
        casillaActual = siguienteMuerte();
    }
    else if (esOca(casillaActual) == false && esDados(casillaActual) == false && esLaberinto(casillaActual) == false && esMuerte(casillaActual) == false && esPosada(casillaActual) == false && esPozo(casillaActual) == false && esPrision(casillaActual) == false && esPuente(casillaActual) == false) {
        cout << "CASILLA ACTUAL: ";
        casillaActual = casillaActual;
    }
    return casillaActual;
}
int efectoTiradas(int casillaActual, int numerodeTiradas) {
    numerodeTiradas = 0;
    if (esOca(casillaActual) == true && casillaActual < Meta_casilla) {
        cout << "DE OCA EN OCA Y TIRO PORQUE ME TOCA" << endl;
        cout << "VUELVES A TIRAR";
        numerodeTiradas = numerodeTiradas + 1;
    }
    if (esPuente(casillaActual) == true) {
        cout << "DE PUENTE EN PUENTE Y TIRO PORQUE ME LLEVA LA CORRIENTE" << endl;
        cout << "VUELVES A TIRAR";
        numerodeTiradas = numerodeTiradas + 1;
    }
    if (esDados(casillaActual) == true) {
        cout << "DE DADO A DADO Y TIRO PORQUE ME HA TOCADO" << endl;
        cout << "VUELVES A TIRAR";
        numerodeTiradas = numerodeTiradas + 1;
    }
    if (esPosada(casillaActual) == true) {
        cout << "PIERDES UN TURNO " << endl;
        numerodeTiradas = numerodeTiradas - 1;
    }
    if (esPrision(casillaActual) == true) {
        cout << "PIERDES DOS TURNOS" << endl;
        numerodeTiradas = numerodeTiradas - 2;
    }
    if (esPozo(casillaActual) == true) {
        cout << "PIERDES TRES TURNOS: " << endl;
        numerodeTiradas = numerodeTiradas - 3;
    }
    if (esOca(casillaActual) == false && esDados(casillaActual) == false && esLaberinto(casillaActual) == false && esMuerte(casillaActual) == false && esPosada(casillaActual) == false && esPozo(casillaActual) == false && esPrision(casillaActual) == false && esPuente(casillaActual) == false) {
        numerodeTiradas = 0;
    }
    return numerodeTiradas;
}
int cambiodeJugador(int casillaActual) {
    if (jugador == 1) {
        jugador = 2;
        cout << "\tJUGADOR ";
    }
    else {
        jugador = 1;
        cout << "\tJUGADOR ";
    }
    return jugador;
}*/