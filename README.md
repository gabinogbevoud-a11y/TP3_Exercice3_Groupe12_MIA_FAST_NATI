# TP 3 — Groupe 12

Ce dossier contient les travaux du groupe sur la gestion d’une résidence étudiante et un exercice de programmation orientée objet en C++.

## Contenu du projet

| Fichier | Description |
| --- | --- |
| `TP3_Groupe12_MIA_FAST.cpp` | Application en console de gestion d’une résidence : étudiants, chambres, demandes d’hébergement, attributions, départs et statistiques. |
| `TP3_Groupe3_MIA_FAST.puml` | Diagrammes PlantUML du système : cas d’utilisation, classes, séquence d’attribution d’une chambre et états-transitions d’une demande. |
| `Exercice3_Groupe12_MIA_FAST.cpp` | Exercice C++ sur l’héritage et le polymorphisme, avec les classes `Employe`, `Enseignant`, `AgentAdministratif` et `Technicien`. |
| `Exercice3_Groupe12_MIA_FAST.puml` | Diagramme de classes PlantUML de l’exercice sur les employés. |

Les deux fichiers `.cpp` contiennent chacun leur propre fonction `main()`. Il faut donc les compiler et les exécuter séparément.

## Prérequis

- Un compilateur C++ avec `g++` (par exemple MSYS2 UCRT64).
- VS Code avec l’extension PlantUML pour prévisualiser les diagrammes `.puml`.

Pour vérifier que le compilateur est disponible dans un terminal :

```powershell
g++ --version
```

## Compiler et lancer la gestion de résidence

Depuis ce dossier, dans le terminal PowerShell :

```powershell
g++ -std=c++11 TP3_Groupe12_MIA_FAST.cpp -o residence.exe
.\residence.exe
```

Le programme affiche un menu. Il permet notamment d’enregistrer et consulter les étudiants et les chambres, de créer une demande, d’attribuer une chambre, d’enregistrer un départ et d’afficher des statistiques.

## Compiler et lancer l’exercice sur les employés

```powershell
g++ -std=c++14 Exercice3_Groupe12_MIA_FAST.cpp -o employes.exe
.\employes.exe
```

L’option `-std=c++14` est nécessaire pour `std::make_unique`. Le programme crée un enseignant, un agent administratif et un technicien, puis affiche leurs informations et leurs salaires calculés.

## Prévisualiser les diagrammes PlantUML

1. Ouvre le dossier du projet dans VS Code.
2. Ouvre le fichier `.puml` voulu.
3. Affiche l’aperçu PlantUML avec `Alt + D`.

Dans `TP3_Groupe3_MIA_FAST.puml`, les quatre diagrammes sont écrits dans des blocs `@startuml` / `@enduml` distincts. L’aperçu peut les parcourir séparément.

## Limite actuelle

Les données de gestion de résidence sont conservées en mémoire pendant l’exécution. Elles ne sont pas sauvegardées dans un fichier ou une base de données ; elles disparaissent à la fermeture du programme.
