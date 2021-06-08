#include <iostream>
#include <vector>
#include <md5.h>

using namespace std;
vector<int> Xqd;//8*64=512
int bits[80];//32 bits
int parteA, parteB, parteC, parteD, parteE;
int A1, B1, C1, D1, E1; // buffer para producir el resultado
int Turn;
void printBits() {//output the filled text
    for (int i = 0; i < Xqd.size(); i++) {
        printf("%02x", Xqd[i]);

        if ((i + 1) % 4 == 0)
            printf(" ");
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
}
int S(unsigned int x, int n) {
    return x >> (32 - n) | (x << n);
}
void append(string m) {// Proceso de llenado del texto
    Turn = (m.size() + 8) / 64 + 1;
    Xqd.resize(Turn * 64);
    int i = 0;
    for (; i < m.size(); i++) {
        Xqd[i] = m[i];
    }
    Xqd[i++] = 0x80;
    while (i < Xqd.size() - 8) {
        Xqd[i] = 0;
        i++;
    }
    long long int a = m.size() * 8;
    for (i = Xqd.size() - 1; i >= Xqd.size() - 8; i--) {
        Xqd[i] = a % 256;
        a /= 256;
    }
}
void genArray(vector<int> m, int n) {//Genera array
    n *= 64;
    for (int i = 0; i < 16; i++) {
        bits[i] = (m[n + 4 * i] << 24) + (m[n + 4 * i + 1] << 16)
            + (m[n + 4 * i + 2] << 8) + m[n + 4 * i + 3];
    }
    for (int i = 16; i < 80; i++) {
        bits[i] = S(bits[i - 16] ^ bits[i - 14] ^ bits[i - 8] ^ bits[i - 3], 1);
    }
}
int ft(int t) {//ft(B,C,D) function
    if (t < 20)
        return (parteB & parteC) | ((~parteB) & parteD);
    else if (t < 40)
        return parteB ^ parteC ^ parteD;
    else if (t < 60)
        return (parteB & parteC) | (parteB & parteD) | (parteC & parteD);
    else
        return parteB ^ parteC ^ parteD;
}
int Kt(int t) {
    if (t < 20)
        return 0x5a827999;
    else if (t < 40)
        return 0x6ed9eba1;
    else if (t < 60)
        return 0x8f1bbcdc;
    else
        return 0xca62c1d6;
}
void sha1(string text, int ejm) {
    A1 = parteA = 0x67452301;
    B1 = parteB = 0xefcdab89;
    C1 = parteC = 0x98badcfe;
    D1 = parteD = 0x10325476;
    E1 = parteE = 0xc3d2e1f0;
    append(text);
    printBits();
    for (int i = 0; i < Turn; i++) {
        genArray(Xqd, i);
        for (int t = 0; t < 80; t++) {
            int temp = parteE + ft(t) + S(parteA, 5) + bits[t] + Kt(t);
            parteE = parteD;
            parteD = parteC;
            parteC = S(parteB, 30);
            parteB = parteA;
            parteA = temp;
        } // Partes del mensaje ya cifradas
        A1 = parteA = parteA + A1;
        B1 = parteB = parteB + B1;
        C1 = parteC = parteC + C1;
        D1 = parteD = parteD + D1;
        E1 = parteE = parteE + E1;
    }
    if (ejm   == 1) {
        cout << "Por lo que este recibe: " << endl;
        printf("%08x%08x%08x%08x%08x\n\n", A1, B1, C1, D1, E1);

    } else if (ejm == 2){
        cout << "Recibe, parte 1: " << endl;
        printf("%08x%08x%08x%08x%08x\n\n", A1, B1, C1, D1, E1);
    } else if (ejm == 3){
        cout << "Recibe, parte 2: " << endl;
        printf("%08x%08x%08x%08x%08x\n\n", A1, B1, C1, D1, E1);
    } else if (ejm == 4){
        cout << "Recibe, parte 3: " << endl;
        printf("%08x%08x%08x%08x%08x\n\n", A1, B1, C1, D1, E1);
    }
}

int main()
{
    vector<int> Xqd;//8*64=512
    int turn;
    int bits[80]; //grupo de 32 bits

    int opcion;
    do {
        cout << "" << endl;
        cout << "Seleccione cual de los dos algoritmos desea ejemplificar: " << endl;
        cout << "1) SHA1" << endl;
        cout << "2) MD5" << endl;
        cout << "3) Salir" << endl;
        cin >> opcion;
        switch (opcion) {
        case 1:
            cout << "SHA1 selecionado." << endl;
            cout << "Ahora, seleccione el caso de prueba" << endl;
            cout << "1) Contraseña de Banco. Emisor: Usuario, Receptor: Sistema bancario" << endl;
            cout << "2) Encriptado de seguridad. Emisor: NIST, Receptor: Hacker inexperto" << endl;
            int pruebaSH;
            cin >> pruebaSH;
            if (pruebaSH == 1){
                cout << "Usted acaba de ir a sacar una cuenta bancaria, el sistema bancario falla, \npor lo que le dicen que le asignaran un pin temporal mientras se arregla el sistema." << endl;
                cout << "Cuando llega a su casa, al poco tiempo recibe una notificacion sobre el \ncambio de contraseña, usted accede a un link que le solicita ingresar una nueva contraseña" << endl;
                cout << "(Sistema) Ingrese una nueva contraseña para su cuenta: " << endl;
                string password;
                cin >> password;
                cout << "El usuario sabe que su contraseña ingresada es " << password << " pero el sistema lo cifra" << endl;
                cout << "(Sistema) Se ha guardado su contraseña *********" << endl;
                cout << "El usuario envia la contraseña, pero banco utiliza un cifrado de tipo SHA1" << endl;
                sha1(password,1);
            } else {
                cout << "La NIST intenta enviar un mensaje de suma importancia a otra organizacion, \nel mensaje debe ser protegido, por lo que se cifra mediante el hash SHA1. " << endl;
                cout << "A su vez, un hacker conoce el momento en el que el mensaje sera enviado, pero\n este, a pesar de estar preparado, desconoce el tipo de cifrado del mismo." << endl;
                cout << "Como encargado de enviar el mensaje, se le asigna que lo divida en 3, es decir, \n que al final tenga que ingresar 3 mensajes." << endl;
                cout << "(Sistema) Escriba las tres partes del mensaje: " << endl;
                string p1;
                string p2;
                string p3;
                cin >> p1;
                cin >> p2;
                cin >> p3;
                cout << "(Sistema) Mensaje enviado con exito." << endl;
                cout << "Pero, de camino el mensaje es interceptado por el hacker, y aunque logra obtener \nlas 3 partes, para el es imposible decifrarlo y unicamente puede ver la encriptacion" << endl;
                sha1(p1,2);
                sha1(p2,3);
                sha1(p3,4);
            }
        case 2:
            cout << "MD5 selecionado." << endl;
            cout << "Ahora, el siguiente caso de prueba ejemplificara la comunicacion a traves de correo electronico." << endl;
            cout << "Una persona desea comprobar si sus correos estan sufiendo perdida o alteracion de informacion." << endl;
            cout << "Por lo que plantea utilizar como emisor su celurar, y como lado receptor su computadora en la\n que pretende recibir el contenido del mismo encriptado utilizando MD5" << endl;
            cout << "(Sistema) Redacte el contenido del correo electronico:              (SIN ESPACIOS)" << endl;
            string msg;
            cin >> msg;

            cout << "El usuario sabe que su mensaje fue: " << msg << ". Por lo que, introduce este mismo mensaje en \nuna calculadora de MD5, la calculadora le retorna: " << md5(msg) << endl;

            cout << "Inmediantamente, del lado receptor, pudo comprobar que su mensaje no ha sido alterado, ya que\n al codificar el mensaje recibido con MD5, la computadora muestra: " << md5(msg) << endl;
            break;
        }

    } while (opcion != 3);
    return 0;
}
