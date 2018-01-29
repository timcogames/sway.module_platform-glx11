#ifndef SWAY_GLX11_GLXCONTEXT_H
#define SWAY_GLX11_GLXCONTEXT_H

#include <sway/glx11/xwindow.h>
#include <sway/glx11/xscreenconnection.h>
#include <sway/core/version.h>

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/make_shared.hpp> // boost::make_shared

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <GL/gl.h>
#include <GL/glx.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class Canvas;

/*!
 * \brief
 *    Контекст поверхности холста.
 */
class GlxContext : private boost::noncopyable {
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
	 * \param[in] window
	 *    Окно графического интерфейса.
	 */
	GlxContext(boost::shared_ptr<XScreenConnection> connection, XWindow * window);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Уничтожает контекст визуализации.
	 */
	~GlxContext();

	/*!
	 * \brief
	 *    Создает контекст визуализации.
	 */
	void createLegacy(GLXFBConfig fbconfig);

	/*!
	 * \brief
	 *    Прикрепляет контекст к окну.
	 *
	 * \sa
	 *    doneCurrent()
	 */
	bool makeCurrent();
	
	/*!
	 * \brief
	 *    Освобождаем контекст.
	 *
	 * \sa
	 *    makeCurrent()
	 */
	bool doneCurrent();

	/*!
	 * \brief
	 *    Обмен буферов.
	 */
	void present();

private:
	GLXContext _context;
	GLXDrawable _drawable;
	boost::shared_ptr<XScreenConnection> _connection; /*!< Экранное соедининение с сервером. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_GLXCONTEXT_H
