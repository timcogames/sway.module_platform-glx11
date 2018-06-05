#ifndef SWAY_GLX11_CANVAS_H
#define SWAY_GLX11_CANVAS_H

#include <sway/glx11/glxcontext.h>
#include <sway/glx11/glxvisualattributes.h>
#include <sway/glx11/xscreenconnection.h>
#include <sway/glx11/xwindow.h>

#include <sway/core.h>
#include <sway/math.h>

#include <boost/function.hpp> // boost::function
#include <boost/bind.hpp> // boost::bind
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/make_shared.hpp> // boost::make_shared

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <GL/gl.h>
#include <GL/glx.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class Canvas : public XWindow {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] connection
	 *    Экранное соедининение с сервером.
	 * 
	 * \param[in] params
	 *    Начальные параметры окна.
	 */
	Canvas(boost::shared_ptr<XScreenConnection> connection, const WindowInitialParams & params);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	~Canvas();

	/*!
	 * \brief
	 *    Получает контекст.
	 */
	boost::shared_ptr<GlxContext> getContext();

	virtual void handleCreateNotifyEvent(const XEvent & event) override;
	virtual void handleConfigureNotifyEvent(const XEvent & event) override;
	virtual void handleExposeEvent(const XEvent & event) override;
	virtual void handleFocusInEvent(const XEvent & event) override;
	virtual void handleFocusOutEvent(const XEvent & event) override;

private:
	GLXFBConfig _chooseBestSuitable(boost::shared_ptr<XScreenConnection> connection, GLXFBConfig * configs, s32_t numConfigs);

	GlxVisualAttributes _getMultisampleAttributes(boost::shared_ptr<XScreenConnection> connection, GLXFBConfig config);

private:
	boost::shared_ptr<GlxContext> _context; /*!< Контекст поверхности холста. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_CANVAS_H
