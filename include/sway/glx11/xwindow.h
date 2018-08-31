#ifndef SWAY_GLX11_XWINDOW_H
#define SWAY_GLX11_XWINDOW_H

#include <sway/glx11/typedefs.h>
#include <sway/glx11/xatom.h>
#include <sway/glx11/xscreenconnection.h>
#include <sway/glx11/windoweventlistener.h>
#include <sway/glx11/windowinitialinfo.h>
#include <sway/glx11/windowmodes.h>
#include <sway/glx11/prereqs.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

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
	XWindow(XScreenConnectionRef_t connection);

	/*!
	 * \brief
	 *    Деструктор класса.
	 *
	 *    Уничтожает главное окно приложения.
	 */
	~XWindow();

	/*!
	 * \brief
	 *    Добавляет привязку функции к оконному событию.
	 *
	 * \param[in] type
	 *    Тип события.
	 * 
	 * \param[in] callback
	 *    Функция вызываемая при возникновении события.
	 */
	void addEventBinding(s32_t type, EventCallbackFunc_t callback);

	/*!
	 * \brief
	 *    Создает главное окно приложения.
	 *
	 * \param[in] visualInfo
	 *    Информация о дисплее.
	 * 
	 * \param[in] windowInfo
	 *    Начальные параметры окна.
	 * 
	 * \exception std::runtime_error Неудачное создание окна.
	 */
	void createDummy(XVisualInfo * visualInfo, const WindowInitialInfo & windowInfo);

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
	 * \param[in] size
	 *    Размер окна.
	 * 
	 * \param[in] resizable
	 *    Имеется возможность изменения размера?
	 */
	void setSizeHints(const WindowSize & size, bool resizable);

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
	 * \param[in] size
	 *    Размер окна.
	 * 
	 * \param[in] resizable
	 *    Имеется возможность изменения размера?
	 */
	void _setMinSize(XSizeHints * hints, const WindowSize & size, bool resizable);
	
	/*!
	 * \brief
	 *    Устанавливает максимальный размер.
	 *
	 * \param[out] hints
	 *    Cтруктура рекомендаций.
	 * 
	 * \param[in] size
	 *    Размер окна.
	 * 
	 * \param[in] resizable
	 *    Имеется возможность изменения размера?
	 */
	void _setMaxSize(XSizeHints * hints, const WindowSize & size, bool resizable);

private:
	XScreenConnectionRef_t _connection; /*!< Экранное соедининение с сервером. */
	Window _window; /*!< Идентификатор окна. */
	Atom _wmatom[kAtom_WMLast], _netatom[kAtom_NetLast];
	EventCallbackFuncMap_t _eventCallbacks;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_XWINDOW_H
