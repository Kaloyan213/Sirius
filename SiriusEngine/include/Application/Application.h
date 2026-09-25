/* 
 * Copyright (c) Kaloyan Badankov
 */

#pragma once

#include "Core/Core.h"

inline namespace SiriusAPI {

class SIRIUS_API Application {
  public:
    /**
     * @brief Construct a new Application object
     * 
     */
    Application();
    
    /**
     * @brief Destroy the Application object
     * 
     */
    virtual ~Application() = default;
    
    /**
     * @brief Initializes the engine subsystems, should be called before application run
     * 
     * @return int 0 on success, non-zero on failure 
     */
    int Initialize ();

    /**
     * @brief Starts the main engine loop
     * 
     * @return int 0 on success, non-zero on failure 
     */
    int Run ();

    /**
     * @brief Shutdowns the application gracefully
     * 
     */
    void Shutdown ();

protected:
    /**
     * @brief Gets called once all the modules are initialized
     * 
     */
    virtual void OnInit ();

    /**
     * @brief Gets called on every loop of the application
     * 
     */
    virtual void OnTick ();

private:
  void Deinit ();

private:
  bool exitRequested {false};
};
} // namespace SiriusAPI