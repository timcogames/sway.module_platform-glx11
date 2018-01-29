#ifndef SWAY_GLX11_XSCREENCONNECTION_H
#define SWAY_GLX11_XSCREENCONNECTION_H

#include <sway/math.h>

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include <X11/Xlib.h>
#include <X11/Xutil.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class XScreenConnection : private boost::noncopyable {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 */
	XScreenConnection();

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Освобождает захваченные ресурсы.
	 */
	~XScreenConnection();

	/*!
	 * \brief
	 *    Получает указатель на структуру дисплея.
	 */
	Display * getDisplay() const;

	/*!
	 * \brief
	 *    Получает номер экрана.
	 */
	s32_t getScreenNumber() const;

	/*!
	 * \brief
	 *    Получает корневое окно.
	 */
	Window getRootWindow() const;

	/*!
	 * \brief
	 *    Получает размер дисплея.
	 */
	math::size2i_t getDisplaySize() const;

private:
	Display * _display; /*!< Указатель на структуру дисплея. */
	s32_t _screen; /*!< Номер экрана. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_XSCREENCONNECTION_H
