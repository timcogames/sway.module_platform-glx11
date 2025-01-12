#ifndef SWAY_PLTF_MAC_DTPCONTEXT_HPP
#define SWAY_PLTF_MAC_DTPCONTEXT_HPP

#include <sway/pltf/_stdafx.hpp>
#include <sway/pltf/context.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>
#include <sway/pltf/mac/dtpwindow.hpp>
#include <sway/pltf/typedefs.hpp>

namespace sway::pltf {

/**
 * @brief \~english Context of surface canvas. \~russian Контекст поверхности холста.
 */
class DTPContext : public Context {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  /**
   * \~english
   * @brief Constructor class. Performs initialization of a new instance of the class.
   * @param[in] connection Screen connection to the server.
   * @param[in] window Graphics interface window.
   *
   * \~russian
   * @brief Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   * @param[in] connection Экранное соедининение с сервером.
   * @param[in] window Окно графического интерфейса.
   */
  DTPContext(typedefs::DTPScreenConnectionSharedPtr_t connection, DTPWindow *window);

  /**
   * @brief \~english Destructor. Destroys visualization context. \~russian Деструктор класса. Уничтожает контекст
   * визуализации.
   */
  virtual ~DTPContext();

  /** @} */
#pragma endregion

  /**
   * @brief \~english Creates visualization context. \~russian Создает контекст визуализации.
   */
  MTHD_OVERRIDE(void create(void *arg));

  MTHD_OVERRIDE(void destroy());

  /**
   * @brief \~english Attaches context to the window. \~russian Прикрепляет контекст к окну.
   * @sa doneCurrent()
   */
  MTHD_OVERRIDE(auto makeCurrent() -> bool);

  /**
   * @brief \~english Releases context. \~russian Освобождаем контекст.
   * @sa makeCurrent()
   */
  MTHD_OVERRIDE(auto doneCurrent() -> bool);

  /**
   * @brief \~english Exchanges buffers. \~russian Обмен буферов.
   */
  MTHD_OVERRIDE(void present());

private:
  GLXContext context_;
  GLXDrawable drawable_;
  typedefs::DTPScreenConnectionSharedPtr_t connection_; /*!< \~english Screen connection to the server.
    \~russian Экранное соедининение с сервером. */
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_MAC_DTPCONTEXT_HPP
