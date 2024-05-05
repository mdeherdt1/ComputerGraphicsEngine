//
// Created by Mathis De Herdt on 24/04/2024.
//

#include "lightClass.h"

Light::Light(const Color1 &ambientLight, const Color1 &diffuseLight, const Color1 &specularLight) : ambientLight(
        ambientLight), diffuseLight(diffuseLight), specularLight(specularLight) {}
