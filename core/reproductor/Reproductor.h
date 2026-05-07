#pragma once

#include "structures/Cola.h"
#include "structures/Pila.h"

#include "catalogue/Multimedia.h"

namespace Reproductor {
    void iniciar(
        Cola<Multimedia*>& listaReproduccion
    );
}