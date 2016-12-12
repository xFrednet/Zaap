#include "Renderer3D.h"

zaap::graphics::Renderer3D* zaap::graphics::Renderer3D::Init()
{
}

zaap::graphics::Renderer3D::Renderer3D()
{
}

void zaap::graphics::Renderer3D::loadTransformationMatrix(const Mat4& transformationMatrix) const
{
}

void zaap::graphics::Renderer3D::loadLightSetup(const LightSetup& LightSetup) const
{
}

void zaap::graphics::Renderer3D::loadScene(const Scene* scene) const
{
}

void zaap::graphics::Renderer3D::startShader(ZA_SHADER_TYPE shader)
{
}

zaap::graphics::Shader* zaap::graphics::Renderer3D::getShader(ZA_SHADER_TYPE shader)
{
}

void zaap::graphics::Renderer3D::setAlphaTestingState(bool enabled)
{
}

void zaap::graphics::Renderer3D::enableAlphaTesting()
{
}

void zaap::graphics::Renderer3D::disableAlphaTesting()
{
}
