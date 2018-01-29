#ifndef SWAY_GLX11_XWINDOW_H
#define SWAY_GLX11_XWINDOW_H

#include <sway/glx11/xatom.h>
#include <sway/glx11/xscreenconnection.h>
#include <sway/glx11/windoweventlistener.h>
#include <sway/glx11/windowinitialparams.h>
#include <sway/glx11/windowmode.h>
#include <sway/core.h>
#include <sway/math.h>

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/make_shared.hpp> // boost::make_shared
#include <boost/function.hpp> // boost::function
#include <boost/bind.hpp> // boost::bind

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <GL/gl.h>
#include <GL/glx.h>

#include <map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class XScreenConnection;
class XWindow : public WindowEventListener, private boost::noncopyable {
public:
	/*!
	 * \brief
	 *    Конструктор класса.
	 *
	 *    Выполняет инициализацию нового экземпляра класса.
	 * 
	 * \param[in] connection
	 *    Экранное соедининение с сервером.
	 */
	XWindow(boost::shared_ptr<XScreenConnection> connection);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Уничтожает главное окно приложения.
	 */
	~XWindow();

	/*!
	 * \brief
	 *    Создает главное окно приложения.
	 *
	 * \param[in] visualInfo
	 *    Информация о дисплее.
	 * 
	 * \param[in] params
	 *    Начальные параметры окна.
	 * 
	 * \exception std::runtime_error Неудачное создание окна.
	 */
	void createDummy(XVisualInfo * visualInfo, const WindowInitialParams & params);

	/*!
	 * \brief
	 *    Обрабатывает события.
	 */
	bool eventLoop(bool keepgoing);

	/*!
	 * \brief
	 *    Устанавливает заголовок окна.
	 *
	 * \param[in] title
	 *    Заголовок окна.
	 */
	void setTitle(lpcstr_t title);

	/*!
	 * \brief
	 *    Устанавливает позицию окна.
	 *
	 * \param[in] x
	 *    Координата позиции окна по оси X.
	 * 
	 * \param[in] y
	 *    Координата позиции окна по оси Y.
	 */
	void setPosition(s32_t x, s32_t y);

	/*!
	 * \brief
	 *    Получает позицию окна.
	 */
	math::point2i_t getPosition() const;

	/*!
	 * \brief
	 *    Устанавливает размер окна.
	 *
	 * \param[in] w
	 *    Ширина окна.
	 * 
	 * \param[in] h
	 *    Высота окна.
	 */
	void setSize(s32_t w, s32_t h);

	/*!
	 * \brief
	 *    Получает размер окна.
	 */
	math::size2i_t getSize() const;

	/*!
	 * \brief
	 *    Устанавливает поведение при смене размера.
	 *
	 * \param[in] sizes
	 *    Размеры окна (Основной / Минимальный / Максимальный).
	 * 
	 * \param[in] resizable
	 *    Имеется возможность изменения размера?
	 */
	void setSizeHints(const math::size2i_t * sizes, bool resizable);

	/*!
	 * \brief
	 *    Показывает окно.
	 *
	 * \sa
	 *    hide()
	 *    visible()
	 */
	void show();

	/*!
	 * \brief
	 *    Скрывает окно.
	 *
	 * \sa
	 *    show()
	 *    visible()
	 */
	void hide();

	/*!
	 * \brief
	 *    Получает значение видимости окна.
	 *
	 * \sa
	 *    show()
	 *    hide()
	 */
	bool visible() const;

	/*!
	 * \brief
	 *    Переключает в полноэкранный / оконный режим.
	 *
	 * \param[in] fullscreen
	 *    Включить полноэкранный режим?
	 */
	void setFullscreen(bool fullscreen);

	/*!
	 * \brief
	 *    Устанавливает максимальный размер окна.
	 *
	 * \param[in] maximized
	 *    Растянуть окно до максимальных размеров?
	 */
	void setMaximize(bool maximized);

	/*!
	 * \brief
	 *    Получает идентификатор окна.
	 */
	Window getWindowHandle();

private:
	void _initializeAtoms();

	void _initializeEventBindings();

	/*!
	 * \brief
	 *    Устанавливает минимальный размер.
	 *
	 * \param[out] hints
	 *    Cтруктура рекомендаций.
	 * 
	 * \param[in] sizes
	 *    Размеры окна (Основной / Минимальный / Максимальный).
	 * 
	 * \param[in] resizable
	 *    Имеется возможность изменения размера?
	 */
	void _setMinSize(XSizeHints * hints, const math::size2i_t * sizes, bool resizable);
	
	/*!
	 * \brief
	 *    Устанавливает максимальный размер.
	 *
	 * \param[out] hints
	 *    Cтруктура рекомендаций.
	 * 
	 * \param[in] sizes
	 *    Размеры окна (Основной / Минимальный / Максимальный).
	 * 
	 * \param[in] resizable
	 *    Имеется возможность изменения размера?
	 */
	void _setMaxSize(XSizeHints * hints, const math::size2i_t * sizes, bool resizable);

private:
	boost::shared_ptr<XScreenConnection> _connection; /*!< Экранное соедининение с сервером. */
	Window _window; /*!< Идентификатор окна. */
	Atom _wmatom[kAtom_WMLast], _netatom[kAtom_NetLast];
	typedef boost::function<void (const XEvent & )> EventCallbackFunc_t;
	typedef std::map<s32_t, EventCallbackFunc_t> EventCallbackFuncMap_t;
	EventCallbackFuncMap_t _eventCallbacks;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_XWINDOW_H
