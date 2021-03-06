/* ========================= eCAL LICENSE =================================
 *
 * Copyright (C) 2016 - 2019 Continental Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * ========================= eCAL LICENSE =================================
*/

/**
 * @brief  eCAL service server interface
**/

#include <ecal/ecal.h>

#include "ecal_service_server_impl.h"

namespace eCAL
{
  /**
   * @brief Service Server class. 
  **/

  /**
  * @brief Constructor. 
  **/
  CServiceServer::CServiceServer() :
                  m_service_server_impl(nullptr),
                  m_created(false)
  {
  }

  /**
   * @brief Constructor. 
   *
   * @param service_name_  Service name.
  **/
  CServiceServer::CServiceServer(const std::string& service_name_) :
                  m_service_server_impl(nullptr),
                  m_created(false)
  {
    Create(service_name_);
  }

  /**
   * @brief Destructor. 
  **/
  CServiceServer::~CServiceServer()
  {
    Destroy();
  }

  /**
   * @brief Creates this object. 
   *
   * @param service_name_  Service name.
   *
   * @return  True if successful. 
  **/
  bool CServiceServer::Create(const std::string& service_name_)
  {
    if(m_created) return(false);

    m_service_server_impl = new CServiceServerImpl(service_name_);

    m_created = true;
    return(true);
  }

  /**
   * @brief Destroys this object. 
   *
   * @return  True if successful. 
  **/
  bool CServiceServer::Destroy()
  {
    if(!m_created) return(false);

    m_service_server_impl->Destroy();
    delete m_service_server_impl;
    m_service_server_impl = nullptr;

    m_created = false;
    return(true);
  }

  /**
   * @brief Add client request callback.
   *
   * @param callback_  Callback function for server response.
   *
   * @return  True if successful.
  **/
  bool CServiceServer::AddMethodCallback(const std::string& method_, const std::string& req_type_, const std::string& resp_type_, const MethodCallbackT& callback_)
  {
    if (!m_created) return false;
    return m_service_server_impl->AddMethodCallback(method_, req_type_, resp_type_, callback_);
  }

  /**
   * @brief Remove client request callback.
   *
   * @return  True if successful.
  **/
  bool CServiceServer::RemMethodCallback(const std::string& method_)
  {
    if (!m_created) return false;
    return m_service_server_impl->RemMethodCallback(method_);
  }

  /**
   * @brief Retrieve service name.
   *
   * @return  The service name.
  **/
  std::string CServiceServer::GetServiceName()
  {
    if (!m_created) return "";
    return m_service_server_impl->GetServiceName();
  }
}
