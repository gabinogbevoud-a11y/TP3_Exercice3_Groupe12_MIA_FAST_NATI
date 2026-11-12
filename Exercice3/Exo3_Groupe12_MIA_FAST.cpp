#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

// Classe mère abstraite
class Employe {
protected:
    string matricule;
    string nom;
    string prenom;
    double salaireBase;

public:
    Employe(const string& matricule,
            const string& nom,
            const string& prenom,
            double salaireBase)
        : matricule(matricule),
          nom(nom),
          prenom(prenom),
          salaireBase(salaireBase) {}

    // Méthode virtuelle pure : Employe est abstraite
    virtual double calculerSalaire() const = 0;

    virtual void afficherInformations() const {
        cout << "Matricule : " << matricule << endl;
        cout << "Nom       : " << nom << endl;
        cout << "Prénom    : " << prenom << endl;
        cout << "Salaire   : " << calculerSalaire() << endl;
    }

    virtual ~Employe() = default;
};

// Classe dérivée Enseignant
class Enseignant : public Employe {
private:
    double indemnite;

public:
    Enseignant(const string& matricule,
               const string& nom,
               const string& prenom,
               double salaireBase,
               double indemnite)
        : Employe(matricule, nom, prenom, salaireBase),
          indemnite(indemnite) {}

    double calculerSalaire() const override {
        return salaireBase + indemnite;
    }

    void afficherInformations() const override {
        cout << "\n--- Enseignant ---" << endl;
        Employe::afficherInformations();
        cout << "Indemnité : " << indemnite << endl;
    }
};

// Classe dérivée AgentAdministratif
class AgentAdministratif : public Employe {
private:
    double primeAdministration;

public:
    AgentAdministratif(const string& matricule,
                       const string& nom,
                       const string& prenom,
                       double salaireBase,
                       double primeAdministration)
        : Employe(matricule, nom, prenom, salaireBase),
          primeAdministration(primeAdministration) {}

    double calculerSalaire() const override {
        return salaireBase + primeAdministration;
    }

    void afficherInformations() const override {
        cout << "\n--- Agent administratif ---" << endl;
        Employe::afficherInformations();
        cout << "Prime administrative : " << primeAdministration << endl;
    }
};

// Classe dérivée Technicien
class Technicien : public Employe {
private:
    double primeTechnique;

public:
    Technicien(const string& matricule,
               const string& nom,
               const string& prenom,
               double salaireBase,
               double primeTechnique)
        : Employe(matricule, nom, prenom, salaireBase),
          primeTechnique(primeTechnique) {}

    double calculerSalaire() const override {
        return salaireBase + primeTechnique;
    }

    void afficherInformations() const override {
        cout << "\n--- Technicien ---" << endl;
        Employe::afficherInformations();
        cout << "Prime technique : " << primeTechnique << endl;
    }
};

int main() {
    // Collection polymorphe contenant plusieurs catégories d'employés
    vector<unique_ptr<Employe>> personnel;

    personnel.push_back(make_unique<Enseignant>(
        "ENS001", "EDAH", "Sdjinin", 400000, 75000));

    personnel.push_back(make_unique<AgentAdministratif>(
        "ADM002", "TCHOGBE", "Moussa", 300000, 50000));

    personnel.push_back(make_unique<Technicien>(
        "TEC003", "FANCHI", "Ibrahima", 350000, 60000));

    // Liaison dynamique : la bonne version est appelée automatiquement
    for (const auto& employe : personnel) {
        employe->afficherInformations();
    }

    return 0;
}
