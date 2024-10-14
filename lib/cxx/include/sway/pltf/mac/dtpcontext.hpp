#ifndef SWAY_PLTF_MAC_DTPCONTEXT_HPP
#define SWAY_PLTF_MAC_DTPCONTEXT_HPP

#include <sway/pltf/context.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>
#include <sway/pltf/mac/dtpwindow.hpp>
#include <sway/pltf/prereqs.hpp>
#include <sway/pltf/typedefs.hpp>

// #include <GL/glx.h>  // GLXContext, GLXDrawable, GLXFBConfig

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

/**
 * @brief Контекст поверхности холста.
 */
class DTPContext : public Context {
  DECLARE_PTR_ALIASES(DTPContext)

public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] connection Экранное соедининение с сервером.
   * @param[in] window Окно графического интерфейса.
   */
  DTPContext(DTPScreenConnection::SharedPtr_t connection, DTPWindow *window);

  /**
   * @brief Деструктор класса. Уничтожает контекст визуализации.
   */
  virtual ~DTPContext();

  /**
   * @brief Создает контекст визуализации.
   */
  MTHD_OVERRIDE(void create(void *arg));

  MTHD_OVERRIDE(void destroy());

  /**
   * @brief Прикрепляет контекст к окну.
   *
   * @sa doneCurrent()
   */
  MTHD_OVERRIDE(auto makeCurrent() -> bool);

  /**
   * @brief Освобождаем контекст.
   *
   * @sa makeCurrent()
   */
  MTHD_OVERRIDE(auto doneCurrent() -> bool);

  /**
   * @brief Обмен буферов.
   */
  MTHD_OVERRIDE(void present());

private:
  GLXContext context_;
  GLXDrawable drawable_;
  DTPScreenConnection::SharedPtr_t connection_;  // Экранное соедининение с сервером.
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_MAC_DTPCONTEXT_HPP
