#ifndef ODOMETRIC_H
#define ODOMETRIC_H

//on met class pour typer notre énum et éviter qu'elle soit castée en int par erreur
enum class Odometric
{
    Ras,
    EnemyDetected,
    EnemyDead
};

#endif