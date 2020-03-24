///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.04.2019
///

#pragma once

#include <memory>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h> 
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QWheelEvent>
#include <QMouseEvent>


class IParticleRenderer : public QOpenGLWidget, protected QOpenGLFunctions
{

public:
	IParticleRenderer() { }
	virtual ~IParticleRenderer() { }

	virtual void render(QPainter* painter);
	virtual void render();

	virtual void initialize();

	void setAnimating(bool animating);

public slots:
	void renderLater();
	void renderNow();

};

class RendererFactory
{
public:
	static std::shared_ptr<IParticleRenderer> create(const char* name);
};
