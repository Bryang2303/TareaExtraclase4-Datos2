#include <iostream>
using namespace std;

void printX() { // Print
    for (int i = 0; i < X.size(); i++) {
        printf("%02x", X[i]);
        if ((i + 1) % 4 == 0)
            printf(" ");
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
}
int S(unsigned int x, int n) {
    return x >> (32 - n) | (x << n);
}
void append(string m) { // Llenado de texto
    Turn = (m.size() + 8) / 64 + 1;
    X.resize(Turn * 64);
    int i = 0;
    for (; i < m.size(); i++) {
        X[i] = m[i];
    }
    X[i++] = 0x80;
    while (i < X.size() - 8) {
        X[i] = 0;
        i++;
    }
    long long int a = m.size() * 8;
    for (i = X.size() - 1; i >= X.size() - 8; i--) {
        X[i] = a % 256;
        a /= 256;
    }
}

void setW(vector<int> m, int n) { //Generar el array
    n *= 64;
    for (int i = 0; i < 16; i++) {
        W[i] = (m[n + 4 * i] << 24) + (m[n + 4 * i + 1] << 16)
            + (m[n + 4 * i + 2] << 8) + m[n + 4 * i + 3];
    }
    for (int i = 16; i < 80; i++) {
        W[i] = S(W[i - 16] ^ W[i - 14] ^ W[i - 8] ^ W[i - 3], 1);
    }
}
void sha1(string text) {
    A1 = parteA = 0x67452301;
    B1 = parteB = 0xefcdab89;
    C1 = parteC = 0x98badcfe;
    D1 = parteD = 0x10325476;
    E1 = parteE = 0xc3d2e1f0;
    append(text);
    printX();

    for (int i = 0; i < Turn; i++) {
        setW(X, i);
        for (int t = 0; t < 80; t++) {

            parteE = parteD;
            parteD = parteC;
            parteC = S(parteB, 30);
            parteB = parteA;
            parteA = temp;
        }
        A1 = parteA = parteA + A1;
        B1 = parteB = parteB + B1;
        C1 = parteC = parteC + C1;
        D1 = parteD = parteD + D1;
        E1 = parteE = parteE + E1;
    }
    printf("%08x%08x%08x%08x%08x\n\n", A1, B1, C1, D1, E1);
}

int main()
{
    vector<int> X;//8*64=512

    int parteA, parteB, parteC, parteD, parteE; //partes
    int A1, B1, C1, D1, E1; // buffer para el resultado final
    int turn;
    int W[80]; //grupo de 32 bits

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
            if (pruebaSH == 1){
                cout << "Usted acaba de ir a sacar una cuenta bancaria, el sistema bancario falla, \npor lo que le dicen que le asignaran un pin temporal mientras se arregla el sistema." << endl;
                cout << "Cuando llega a su casa, al poco tiempo recibe una notificacion sobre el \ncambio de contraseña, usted accede a un link que le solicita ingresar una nueva contraseña" << endl;
                cout << "(Sistema) Ingrese una nueva contraseña para su cuenta: " << endl;
                string password;
                cin >> password;
                cout << "El usuario sabe que su contraseña ingresada es " << password << " pero el sistema lo cifra" << endl;
                cout << "(Sistema) Se ha guardado su contraseña *********" << endl;
                cout << "El usuario envia la contraseña, y el banco utiliza un cifrado de tipo SHA1, por lo que este recibe: " << endl;


            } else {

            }
            break;

        case 2:

            break;

        case 3:

            break;

    }
    while (opcion != 3);
    return 0;
}
