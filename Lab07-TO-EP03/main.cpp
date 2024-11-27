#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
using namespace std;

// Clase base: Pieza
class Pieza {
protected:
    string nombre;
    string color;

public:
    Pieza(string nombre, string color) : nombre(nombre), color(color) {}

    virtual void MostrarDetalles() {
        cout << nombre << " - Color: " << color << endl;
    }

    virtual ~Pieza() {}
};

// Subclases: Tipos de piezas
class Puerta : public Pieza {
public:
    Puerta(string color) : Pieza("Puerta", color) {}
};

class Llanta : public Pieza {
public:
    Llanta(string color) : Pieza("Llanta", color) {}
};

class Asiento : public Pieza {
public:
    Asiento(string color) : Pieza("Asiento", color) {}
};

class Motor : public Pieza {
public:
    Motor(string tipo) : Pieza("Motor", tipo) {}
};

// Clase que representa un automóvil personalizado
class Automovil {
private:
    string modelo;
    string pais;
    float precio;
    vector<unique_ptr<Pieza>> piezas;

public:
    Automovil(string modelo, string pais, float precio)
        : modelo(modelo), pais(pais), precio(precio) {}

    void AgregarPieza(Pieza* pieza) {
        piezas.emplace_back(pieza);
    }

    void MostrarDetalles() {
        cout << "Modelo: " << modelo << "\nPais: " << pais
             << "\nPrecio: $" << fixed << setprecision(2) << precio << "\nPiezas:\n";
        for (const auto& pieza : piezas) {
            pieza->MostrarDetalles();
        }
    }
};

// Clase Builder para construir el automóvil
class BuilderAutomovil {
private:
    Automovil* autoPersonalizado;

public:
    BuilderAutomovil(string modelo, string pais, float precio) {
        autoPersonalizado = new Automovil(modelo, pais, precio);
    }

    void AgregarPuerta(string color) {
        autoPersonalizado->AgregarPieza(new Puerta(color));
    }

    void AgregarLlanta(string color) {
        autoPersonalizado->AgregarPieza(new Llanta(color));
    }

    void AgregarAsiento(string color) {
        autoPersonalizado->AgregarPieza(new Asiento(color));
    }

    void AgregarMotor(string tipo) {
        autoPersonalizado->AgregarPieza(new Motor(tipo));
    }

    Automovil* GetAutomovil() {
        return autoPersonalizado;
    }
};

// Main
int main() {
    // Crear un automóvil con el Builder
    BuilderAutomovil builder("Deportivo X", "Alemania", 55000.0);

    // Personalizar el automóvil
    builder.AgregarPuerta("Negro");
    builder.AgregarPuerta("Negro");
    builder.AgregarLlanta("Plateado");
    builder.AgregarLlanta("Plateado");
    builder.AgregarAsiento("Cuero Cafe");
    builder.AgregarMotor("V8 Turbo");

    // Obtener el automóvil personalizado
    Automovil* autoPersonalizado = builder.GetAutomovil();

    // Mostrar detalles del automóvil
    cout << "Detalles del automovil personalizado:\n";
    autoPersonalizado->MostrarDetalles();

    // Liberar memoria
    delete autoPersonalizado;

    return 0;
}
