#pragma once

#include <memory>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class IParticleRenderer : public virtual QOpenGLWidget, protected QOpenGLFunctions
{
public:
	virtual void generate(ivhd::IParticleSystem* sys) = 0;
	virtual void destroy() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
};

class RendererFactory
{
public:
	static std::shared_ptr<IParticleRenderer> create(const char* name);
};
