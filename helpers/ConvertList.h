#pragma once

#include <vector>

#include "structures/ListaDoble.h"

#include "catalogue/Multimedia.h"

std::vector<Multimedia*> toVector(
    ListaDoble<Multimedia*>::Nodo* head
);