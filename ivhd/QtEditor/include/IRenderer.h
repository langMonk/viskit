#pragma once

#include <memory>
#include <QKeyEvent>

class IRenderer 
{
public:
	virtual void destroy() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void onKeyPressedEvent(QKeyEvent* event) = 0;
};

