#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <functional>
using namespace std;

// Clase base: Cuenta
class Cuenta {
protected:
    string cliente;
    string tipo;
    float balance;

public:
    Cuenta(string cliente, string tipo, float balance)
        : cliente(cliente), tipo(tipo), balance(balance) {}

    virtual float CalcularInteres() = 0;
    virtual void MostrarDetalles() = 0;

    string GetTipo() { return tipo; }
    float GetBalance() { return balance; }
    void ActualizarBalance(float monto) { balance += monto; }

    virtual ~Cuenta() {}
};

// Subclases: Tipos de cuentas
class CuentaAhorro : public Cuenta {
public:
    CuentaAhorro(string cliente, float balance)
        : Cuenta(cliente, "Ahorro", balance) {}

    float CalcularInteres() override {
        return balance * 0.0045; // 0.45%
    }

    void MostrarDetalles() override {
        cout << "Cuenta Ahorro - Cliente: " << cliente
             << ", Balance: " << fixed << setprecision(2) << balance
             << ", Interés: " << CalcularInteres() << endl;
    }
};

class CuentaJoven : public Cuenta {
public:
    CuentaJoven(string cliente, float balance)
        : Cuenta(cliente, "Joven", balance) {}

    float CalcularInteres() override {
        return balance * 0.005; // 0.5%
    }

    void MostrarDetalles() override {
        cout << "Cuenta Joven - Cliente: " << cliente
             << ", Balance: " << fixed << setprecision(2) << balance
             << ", Interes: " << CalcularInteres() << endl;
    }
};

class CuentaEmpresarial : public Cuenta {
public:
    CuentaEmpresarial(string cliente, float balance)
        : Cuenta(cliente, "Empresarial", balance) {}

    float CalcularInteres() override {
        return balance * 0.0075; // 0.75%
    }

    void MostrarDetalles() override {
        cout << "Cuenta Empresarial - Cliente: " << cliente
             << ", Balance: " << fixed << setprecision(2) << balance
             << ", Interes: " << CalcularInteres() << endl;
    }
};

class TarjetaCredito : public Cuenta {
public:
    TarjetaCredito(string cliente, float balance)
        : Cuenta(cliente, "Tarjeta Credito", balance) {}

    float CalcularInteres() override {
        return balance * 0.2; // 20% promedio
    }

    void MostrarDetalles() override {
        cout << "Tarjeta Credito - Cliente: " << cliente
             << ", Deuda: " << fixed << setprecision(2) << balance
             << ", Interes: " << CalcularInteres() << endl;
    }
};

// Clase Builder: Creación de cuentas
class BuilderCuentas {
private:
    vector<Cuenta*> cuentas;

public:
    void AgregarCuenta(Cuenta* cuenta) {
        cuentas.push_back(cuenta);
    }

    vector<Cuenta*> GetCuentas() {
        return cuentas;
    }

    ~BuilderCuentas() {
        for (Cuenta* cuenta : cuentas)
            delete cuenta;
    }
};

// Cliente
class Cliente {
private:
    string nombre;
    vector<Cuenta*> cuentas;

public:
    Cliente(string nombre) : nombre(nombre) {}

    void AgregarCuenta(Cuenta* cuenta) {
        cuentas.push_back(cuenta);
    }

    void ConsultarEstadoCuenta() {
        cout << "Estado de cuenta para: " << nombre << endl;
        for (Cuenta* cuenta : cuentas) {
            cuenta->MostrarDetalles();
        }
    }

    void Transferir(Cuenta* origen, Cuenta* destino, float monto) {
        if (origen->GetBalance() >= monto) {
            origen->ActualizarBalance(-monto);
            destino->ActualizarBalance(monto);
            cout << "Transferencia realizada: " << monto << " desde " << origen->GetTipo()
                 << " hacia " << destino->GetTipo() << endl;
        } else {
            cout << "Fondos insuficientes para la transferencia." << endl;
        }
    }

    ~Cliente() {
        for (Cuenta* cuenta : cuentas)
            delete cuenta;
    }
};

// Main
int main() {
    BuilderCuentas builder;

    // Crear cuentas para el cliente
    builder.AgregarCuenta(new CuentaAhorro("Juan Perez", 1500.0));
    builder.AgregarCuenta(new CuentaJoven("Juan Perez", 1000.0));
    builder.AgregarCuenta(new TarjetaCredito("Juan Perez", 500.0));

    // Crear cliente
    Cliente cliente("Juan Perez");

    // Asignar cuentas al cliente
    for (Cuenta* cuenta : builder.GetCuentas()) {
        cliente.AgregarCuenta(cuenta);
    }

    // Consultar estado de cuenta
    cliente.ConsultarEstadoCuenta();

    // Operación: Transferencia
    cout << "\nOperacion: Transferencia\n";
    cliente.Transferir(builder.GetCuentas()[0], builder.GetCuentas()[1], 300.0);

    // Consultar estado de cuenta actualizado
    cliente.ConsultarEstadoCuenta();

    return 0;
}
